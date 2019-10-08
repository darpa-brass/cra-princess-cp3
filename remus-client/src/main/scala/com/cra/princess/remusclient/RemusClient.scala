package com.cra.princess.remusclient

import java.io.IOException
import java.nio.file.{Files, Paths}
import java.util.concurrent.atomic.AtomicReference

import com.cra.princess.componentmodel.{ComponentModel, ControlGenerator}
import com.cra.princess.core._
import com.cra.princess.evaluation._
import com.cra.princess.evaluation.messages.{DvlSensorPerturbationType, LatLon}
import com.cra.princess.kalmanfilter.{KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper}
import com.cra.princess.metron.remus.control.{SimulationControlListener, SimulationControlMessage}
import com.cra.princess.metron.remus.state._
import com.cra.princess.metron.{MetronRemusManager, RemusManagerException}
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorVector
import com.cra.princess.monitor.SystemMonitor
import com.cra.princess.optimizer.{ComponentOptimizer, DefaultSensorTransformerPolicy}
import com.cra.princess.pathplanner.alt.SingleDestinationPathPlannerComponentImpl
import com.cra.princess.pathplanner.component._
import com.cra.princess.pathplanner.util.LatLonConverter
import com.cra.princess.pathplanner.{SingleFunctionPathPlanner, Waypoint}
import com.cra.princess.remusclient.navigation.PathFollower.DESTINATION_REACHED
import com.cra.princess.remusclient.navigation._
import com.cra.princess.remusclient.navigation.DDPGTrainerOptimizerFactory
import com.cra.princess.remusclient.sensortransformer.{EmptyRemusSensorTransformer, NativeSensorTransformer, NoAdaptationSensorTransformerPolicy, RemusSensorTransformer}
import com.cra.princess.remusclient.util.RemusUtils
import com.cra.princess.remusclient.verifier.PrismVerifier
import com.cra.princess.util._
import com.cra.princess.{ComponentControls, InputModel, Threshold}
import org.nd4j.linalg.factory.Nd4j

import scala.collection.JavaConverters._
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.Future

class RemusClient() extends DvlSensorUpdateListener with VehicleGroundTruthUpdateListener with Logs
  with SimulationControlListener with ObjectDetectionListener with VehiclePowerUpdateListener
  with RpmSensorUpdateListener with WaterSpeedSensorUpdateListener {

  private val em = EvaluationMessenger.getInstance()

  private val evaluationStatusManager: EvaluationStatusManager = new EvaluationStatusManager
  private val evaluationCommunicationManager: EvaluationCommunicationManager = new EvaluationCommunicationManager
  private val evaluationErrorManager: EvaluationErrorManager = new EvaluationErrorManager

  private val evalConfig = {
    evaluationStatusManager.start()
    evaluationErrorManager.start()
    evaluationCommunicationManager.start()
  }

  private val config = {
    val json = em.sendReadyMessage()
    log.debug(json)
    val factory: RemusClientConfigFactory = new RemusClientConfigFactory
    factory.createRemusClientConfig(json)
  }

  if (config.doAdaptation)
    log.info("Running RemusClient in CHALLENGE configuration - adaptation enabled")
  else
    log.info("Running RemusClient in BASELINE configuration - adaptation disabled")

  private val stateEstimator = new RemusStateEstimator
  private val controller = {
    val stp = if (config.doAdaptation) new DefaultSensorTransformerPolicy else new NoAdaptationSensorTransformerPolicy
    new ScenarioController(stateEstimator, stp, config.doAdaptation)
  }

  private var isRunning: Boolean = false

  private val llConv = new LatLonConverter(config.origin.Lat, config.origin.Lon)

  private val pathPlanner = buildPathPlannerComponent(new SingleFunctionPathPlanner)

  controller.registerOptimizationHandler(pathPlanner, handlePathPlannerOptimization)
  controller.registerAdaptationEventHandler(pathPlanner, RemusUtils.generateAdaptationEventHandler("Path Planner"))
  controller.registerVerificationEventHandler(pathPlanner, handleVerificationResult)

  private val path = {
    val path = {
      // convert path waypoints from meters to Lat/Lon
      val pathInMeters = pathPlanner.component(new PathPlannerEnvironment, config.ppInput, null) // TODO make control variables non-null
      this.xyPathToLatLonPath(pathInMeters)
    }

    val bp = em.sendPathMessage(path.asScala.map(wp => LatLon(wp.getNorth, wp.getEast)).asJava, 2.0)

    // Add battery perturbations as events to the simulation
    val factory: RemusClientConfigFactory = new RemusClientConfigFactory
    factory.addBatteryPerturbations(bp)

    path.asScala.toList
  }

  private val sensorTransformer: RemusSensorTransformer = new NativeSensorTransformer(System.getProperty(RemusClient.SENSOR_TRANSFORMER_PATH_PROPERTY, "."))
//  private val sensorTransformer: RemusSensorTransformer = new EmptyRemusSensorTransformer
  if (config.doAdaptation) this.controller.addSensorTransformer(this.sensorTransformer)

  private val systemMonitor = new SystemMonitor(List("power"), new SystemIntent)
  if (config.doAdaptation) controller.attachSystemMonitor(systemMonitor)
  systemMonitor.addListener(ir => if (!ir.pass) em.sendIntentViolationDetectedMessage("Battery"))

  private val ddpgTrainerOptimizer: DDPGTrainerOptimizer = DDPGTrainerOptimizerFactory.getDDPGTrainerOptimizer()
  private val localization = new Localization(controller, config.origin.Lat, config.origin.Lon)
  private val navigation = buildPathFollowerComponent(new Waypoint(0.0, 0.0), path)
  private val actuator = new ActuatorModuleProxy
  private var actuatorState: KalmanFilterActuatorVector = _
  private var currentLocation: LatLon = LatLon(0.0, 0.0)
  private var previousEnergyLevel: Double = -1.0
  private var objectDetected = false
  private var gotHome = false
  private var stepSize: Option[Double] = None
  private var duration: Option[Long] = None
  private var stepCount = 0
  private val finishedSignaller =
    if (PrincessProperties.mode == TRAINING)
      new FinishedSignaller(this.resumeSimulatorOneStep _)
    else new FinishedSignaller(this.incrementStepCount _)

  // add handler for when the KF is finished processing
  if (PrincessProperties.mode == TRAINING) localization.registerAdaptationHandler(this.handleKfAdaptationEvent)

  // add event handler to navigation
  navigation.addListener(this.handleNavigationEvent)

  private val trueVel = new AtomicReference[(Double, Double)]((Double.NaN, Double.NaN))
  private val trueLoc = new AtomicReference[(Double, Double)]((Double.NaN, Double.NaN))

  def start(): Unit = {
    log.debug("Starting RemusClient")
    try {
      if (!isRunning) {
        log.debug("Starting MetronRemusManager")
        val mrm = MetronRemusManager.getInstance()
        mrm.addVehicleGroundTruthUpdateListener(this)
        mrm.addDvlSensorUpdateListener(this)
        mrm.addRpmSensorUpdateListener(this)
        mrm.addWaterSpeedSensorUpdateListener(this)
        mrm.addSimulationControlListener(this)
        mrm.addObjectDetectionListener(this)
        mrm.addVehiclePowerUpdateListener(this)
        mrm.addObjectDetectionListener(this.navigation)

        mrm.start()

        // Start the generated scenario file
        Future[Unit] {
          Thread.sleep(1000) // Wait 1 sec before launching RemusViewer
          log.debug("Starting " + EvaluationScenarioManager.SCENARIO_FILENAME)
          this.controller.initScenario()

          val runStepped = PrincessProperties.mode.equals(TRAINING)
          EvaluationScenarioManager.runScenario(runStepped)
          this.stepSize = Some(EvaluationScenarioManager.getStepSize)
          this.duration = Some(EvaluationScenarioManager.getDuration)
          if (PrincessProperties.mode.equals(TRAINING)) EvaluationScenarioManager.sendStepMessage((1000.0 / this.stepSize.get).toLong)
        }

        isRunning = true
      }
    } catch {
      case e: RemusManagerException =>
        log.error(s"Cannot connect to ActiveMQ broker: ${e.getMessage}")
        em.sendInitializationFailureError("Cannot connect to ActiveMQ broker")
      case e: IOException =>
        log.error(s"${e.getMessage}")
        em.sendScenarioFailureError(e.getMessage)
    }
  }

  def stop(): Unit = {
    evaluationStatusManager.stopWork()

    if (isRunning) {
      val mrm = MetronRemusManager.getInstance

      // Stop the current scenario
      mrm.sendSimulationEnded()

      // Tell the Test Harness the scenario has finished
      this.em.sendScenarioCompletedMessage()

      // Compute distanceFromDestination value
      // Comes from https://stackoverflow.com/questions/3694380/calculating-distance-between-two-points-using-latitude-longitude-what-am-i-doi
      val R = 6371.01 // Radius of the earth
      val destination = config.destination
      val latDistance = Math.toRadians(destination.Lat - currentLocation.Lat)
      val lonDistance = Math.toRadians(destination.Lon - currentLocation.Lon)
      val a = Math.sin(latDistance / 2) * Math.sin(latDistance / 2) + Math.cos(Math.toRadians(currentLocation.Lat)) * Math.cos(Math.toRadians(destination.Lat)) * Math.sin(lonDistance / 2) * Math.sin(lonDistance / 2)
      val c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a))
      var distance = R * c * 1000 // convert to meters
      distance = Math.pow(distance, 2)
      val distanceFromDestination =  Math.sqrt(distance)

      // Tell the Test Harness we are done
      this.em.sendCp3DoneMessage(this.gotHome, this.objectDetected, currentLocation.Lat, currentLocation.Lon, distanceFromDestination)

      mrm.removeSimulationControlListener(this)
      mrm.removeVehicleGroundTruthUpdateListener(this)
      mrm.removeDvlSensorUpdateListener(this)
      mrm.removeRpmSensorUpdateListener(this)
      mrm.removeWaterSpeedSensorUpdateListener(this)
      mrm.removeObjectDetectionListener(this)
      mrm.removeVehiclePowerUpdateListener(this)
      mrm.removeObjectDetectionListener(this.navigation)

      Thread.sleep(2000)

      mrm.stop()

      isRunning = false
    }

    evaluationCommunicationManager.stopWork()
    evaluationErrorManager.stopWork()

    System.exit(0)
  }

  override def dvlSensorUpdate(rawMsg: RemusDvlData): Unit = {
    // handle remus sensor data
    // get transformed data from sensor transformer
    log.info(s"DVL raw - ${rawMsg.toString}")
    val tMsg = this.sensorTransformer.processSensorReadings(rawMsg)

    // Send the transformed reading to any listeners (e.g., the RemusViewer)
    val mrm = MetronRemusManager.getInstance
    mrm.sendTransformedDvlData(tMsg)
    ddpgTrainerOptimizer.setRemusDVLData(tMsg)

    // Update the StateEstimator
    this.stateEstimator.transformedDvlSensorUpdate(tMsg)

    // Construct a DVL object for now
    val msg = new RemusDvlData(tMsg.getTimestamp, tMsg.getDepth, tMsg.getvE(), tMsg.getvN(), tMsg.getvU(), tMsg.getPitch, tMsg.getRoll, tMsg.getHeading, tMsg.getSurge, tMsg.getSway, tMsg.getHeave)
    log.info(s"${msg.getTimestamp}: Depth(${msg.getDepth}), SSH(${msg.getSurge}, ${msg.getSway}, ${msg.getHeave}), Heading = ${msg.getHeading}")
    val latLon = this.localization.updateLocation(msg, actuatorState)
    actuatorState = this.navigation.component(new PathFollowerEnvironment(), new PathFollowerInput(latLon), null)
    this.currentLocation = latLon

    // Send vehicle command via ActiveMQ
    val cmd = actuator.generateRemusCommand(actuatorState, msg.getDepth)
    log.info("sending vehicle command: heading = " + cmd.getHeadingTarget + ", speed = " + cmd.getSpeedTarget)
    mrm.sendVehicleCommand(cmd)
    finishedSignaller.setRunFinished()
  }

  override def rpmSensorUpdate(msg: RemusRpmData): Unit = {
    log.info(s"RPM raw - ${msg.getTimestamp}: RPM(${msg.getRpm})")
    this.sensorTransformer.rpmSensorUpdate(msg)
  }

  override def waterSpeedSensorUpdate(msg: RemusWaterSpeedData): Unit = {
    log.info(s"Water speed raw - ${msg.getTimestamp}: Speed(${msg.getSpeed})")
    this.sensorTransformer.waterSpeedSensorUpdate(msg)
  }

  override def vehicleGroundTruthUpdate(msg: RemusVehicleState): Unit = {
    log.info(s"Ground truth raw - ${msg.toString}")
    trueVel.set((msg.getvE, msg.getvN))
    trueLoc.set((msg.getTrueLatitude, msg.getTrueLongitude))
    ddpgTrainerOptimizer.setRemusVehicleState(msg)
  }

  override def controlUpdate(controlMessage: SimulationControlMessage): Unit = {
    log.info("Control message received: " + controlMessage.getPlayControl)
    if (controlMessage.getPlayControl.equalsIgnoreCase(SimulationControlMessage.CONTROL_COMMAND_STOP)) {
      log.info("Simulation complete. Stopping...")
      stop()
    }
  }

  override def objectDetected(objectDetectionMessage: RemusObjectDetectionState): Unit = {
    log.info("Object detection message received")
    this.objectDetected = true
    this.em.sendObjectLocatedMessage(this.currentLocation.Lat, this.currentLocation.Lon)
    // TODO The "current location" seems like an inexact value for this. We might be far away from the object still
  }

  def vehiclePowerUpdate(msg: RemusPowerState): Unit = {
    log.info("Power update message received")
    val energyRemaining = msg.getEnergyRemaining
    this.stateEstimator.vehiclePowerUpdate(msg)
    if (this.previousEnergyLevel != -1.0) {
      val powerConsumed = this.previousEnergyLevel - energyRemaining
      this.systemMonitor.updateMetric("power", powerConsumed)
    }
    this.previousEnergyLevel = energyRemaining

    // If power reaches zero, stop the scenario
    if (energyRemaining <= 1) { // give it a range in case the power simulator never gets down to zero
      this.gotHome = false
      stop()
    }

  }

  private def handleNavigationEvent(e: PathEvent): Unit = {
    e.eventType match {
      case DESTINATION_REACHED =>
        log.info("Destination reached. Scenario complete. Stopping...")
        val mrm = MetronRemusManager.getInstance()
        mrm.sendVehicleCommand(actuator.generateRemusStopCommand)
        this.gotHome = true
        stop()
      case _ =>
    }
  }

  private def handlePathPlannerOptimization(newControls: ComponentControls): Unit = {
    log.info("RemusClient re-generating path after optimization")
    val newInput = this.generateCurrentPPInput()
    newInput match {
      case Some(in) =>
        log.debug(s"NEW PPINPUT = $in")
        val newPath = this.pathPlanner.component(new PathPlannerEnvironment, in, newControls)
        log.debug(s"new path = $newPath")
        val newPathInLatLon = this.xyPathToLatLonPath(newPath)
        this.navigation.updatePath(newPathInLatLon)
      case None =>
        log.debug("New path not generated - current path has one or fewer waypoints")
    }
  }

  private def handleVerificationResult(r: VerificationResult): Unit = {
    if (r.pass) {
      log.debug("Setting path follower to resume path")
      this.navigation.resumePath()
    } else {
      log.debug(s"Setting path follower to hold at $currentLocation")
      if(currentLocation != null) {
        this.navigation.holdAtLocation(new Waypoint(this.currentLocation.Lat, this.currentLocation.Lon))
      } else {
        this.navigation.holdAtLocation(new Waypoint(0.0, 0.0))
      }
      EvaluationMessenger.getInstance().sendAdaptationFailureMessage("Path failed verification")
    }
  }

  private def handleKfAdaptationEvent(a: AdaptationState): Unit = {
    log.debug("KF adaptation event received")
    a match {
      case ANALYSIS_COMPLETE => finishedSignaller.setAnalysisFinished()
      case _ => Unit
    }
  }

  private def incrementStepCount: Unit = {
    this.stepCount += 1
    log.debug(s"stepCount = ${this.stepCount} of ${this.duration.get}")
    this.duration match {
      case Some(d) =>
        if (this.stepCount >= d) {
          log.info("Scenario time limit reached. Stopping...")
          stop()
        }
      case _ => ()
    }
  }

  private def resumeSimulatorOneStep: Unit = {
    log.debug("resuming simulator...")
    stepSize match {
      case Some(s) =>
        val ms = (1000.0 / s).toLong
        EvaluationScenarioManager.sendStepMessage(ms)
      case _ => throw new IllegalStateException("KF event received when stepSize was not set")
    }
    this.incrementStepCount
  }

  def buildSingleDestinationPathPlannerComponent(): PathPlannerComponent = {
    controller.buildWrappedComponent[PathPlannerEnvironment, PPInput, java.util.List[Waypoint], PathPlannerComponent](
      new SingleDestinationPathPlannerComponentImpl(), new PathPlannerOptimizer(""), None)
  }

  def buildPathPlannerComponent(p: SingleFunctionPathPlanner): PathPlannerComponent = {
    val model = new String(Files.readAllBytes(Paths.get("prism/plan.prism")))
    val properties = new String(Files.readAllBytes(Paths.get("prism/plan.props")))
    val verifier = new PrismVerifier(model, properties, this.stateEstimator)
    val optimizer = new PathPlannerNNOptimizer(netFile=PrincessProperties.ppOptimizerFile)

    controller.buildWrappedComponent[PathPlannerEnvironment, PPInput, java.util.List[Waypoint], PathPlannerComponent](
      new PathPlannerComponentImpl(p, ppInitialControls()), optimizer, Some(verifier), Some(this.generateCurrentPPInput _))
  }

  def buildPathFollowerComponent(home: Waypoint, path: List[Waypoint]): PathFollowerComponent = {
    val pathFollower = new PathFollowerComponentImpl(home, path)
    val optimizer = if (TRAINING.equals(PrincessProperties.mode)) ddpgTrainerOptimizer else new PathFollowerOptimizer
    controller.buildWrappedComponent[PathFollowerEnvironment, PathFollowerInput, KalmanFilterActuatorVector, PathFollowerComponent](pathFollower, optimizer)
  }

  private def xyPathToLatLonPath(xyPath: java.util.List[Waypoint]): java.util.List[Waypoint] = {
    val pathInLatLon = xyPath.asScala.map(wp => {
      val wpLatLon = llConv.getLatLon(wp.getNorth, wp.getEast)
      new Waypoint(wpLatLon(0), wpLatLon(1))
    })
    pathInLatLon.asJava
  }

  private def currentBoundingBox: Option[BoundingBox] = {
    if (navigation.numRemainingWaypoints > 1) {
      // Everything coming out of the path follower (navigation) is in LAT/LON
      // Everything coming out of the PPInput is in METERS
      // The bounding box needs to be in LAT/LON
      // MAKE SURE TO CONVERT UNITS PROPERLY FOR CONSISTENCY
      val minLat = currentLocation.Lat //+ llConv.getLatLon(config.ppInput.altitude * Math.tan(config.ppInput.fovRadians / 2.0), 0.0)(0)// already in lat/lon
      val minLon = {
        val lowerLeft = config.ppInput.searchAreaLowerLeft
        val lowerLeftLatLon = llConv.getLatLon(lowerLeft._2, lowerLeft._1)
        lowerLeftLatLon(1)
      }
      val (maxLat, maxLon) = {
        val upperRight = config.ppInput.searchAreaUpperRight
        val upperRightLatLon = llConv.getLatLon(upperRight._2, upperRight._1)
        (upperRightLatLon(0), upperRightLatLon(1))
      }
      Some(BoundingBox(minLat, minLon, maxLat, maxLon))
    } else None
  }

  private def generateCurrentPPInput(): Option[PPInput] = {
    val newSearchArea = this.currentBoundingBox
    newSearchArea match {
      case Some(bb) =>
        val factory = new RemusClientConfigFactory
        val startingLocation = {
          val wp = navigation.currentWaypoint.get
          LatLon(wp.getNorth, wp.getEast)
        }
        Some(factory.buildPPInput(LatLon(0.0, 0.0), currentLocation/*startingLocation*/, LatLon(0.0, 0.0), LatLon(bb.minLat, bb.minLon), LatLon(bb.maxLat, bb.maxLon), config.ppInput.altitude, config.ppInput.fovRadians))
      case _ => None
    }
  }
}

object RemusClient {

  val SENSOR_TRANSFORMER_PATH_PROPERTY = "sensor.transformer.path"

  def main(args: Array[String]): Unit = {
    Nd4j.backend
    val rc = new RemusClient()
    rc.start()
  }

}

case class RemusClientConfig(ppInput: PPInput, origin: LatLon, destination: LatLon, sensorPerturbations: List[DvlSensorPerturbationType], doAdaptation: Boolean)

class KalmanFilterEmptyOptimizer extends ComponentOptimizer[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper] {
  def thresholds(): List[Threshold] = List.empty
  def apply(v1: ComponentModel[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper], v2: InputModel[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper], v3: ControlGenerator): ComponentControls = Map.empty
  override def apply(v1: KalmanFilterEnvironmentWrapper, v2: KalmanFilterInputWrapper): ComponentControls = Map.empty
}