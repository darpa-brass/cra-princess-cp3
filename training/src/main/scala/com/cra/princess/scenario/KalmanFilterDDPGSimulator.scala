package com.cra.princess.scenario

import java.io.{File, FileWriter}

import com.cra.princess.localizationalgorithm.components.ComponentState
import com.cra.princess.models.TransformedSingleFunctionKalmanFilter
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterOutput
import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}
import org.apache.commons.math3.linear._

import scala.util.Random

class KalmanFilterDDPGSimulator(val resultsFileName: String,
                                val maxSteps: Int,
                                seed: Int = 1234) extends Simulator {

  override val rand = new Random(seed)
  val rand2 = new Random(12345)

  val kf = new TransformedSingleFunctionKalmanFilter
  private var gtLocation = (0.0, 0.0)
  private var estLocation = (0.0, 0.0)
  private var gtVelocity = (0.0, 0.0)
  private var estVelocity = (0.0, 0.0)
  private var destination = (0.0, 0.0)
  private var cumulativeReward = 0.0

  private val uuvSpeed = 3.2
  private var sensorNoiseStdev = 8.0/*4.0*/ //GFRY
  private var wcRegionY1 = 0.0
  private var wcRegionY2 = 0.0
  private val defaultControls = Array(
    1.0, 0.0, 0.0, 1.0,
    0.3, 0.0, 0.0, 0.3,
    0.1, 0.0, 0.0, 0.2,
    0.0, 0.0, 0.0, 0.0)
  private var waterCurrentVector = (0.0, 0.0)
  private val threshold = 10
  private var initialDist = 0.0

  private val numStateFrames = 16
  private var stateWindow: List[Array[Double]] = Array.fill(numStateFrames)(Array(0.0, 3.2, 0.0, 3.2)).toList

  // KF input
  private var P = MatrixUtils.createRealIdentityMatrix(2)

  override def getCurrentState: TrainingState =
    stateWindow.foldLeft(Array[Double]()){ (acc, i) => acc ++ i}

  override def reset(): TrainingState = {
    steps = 0
    cumulativeReward = 0.0
    gtLocation = (0.0, 0.0)
    estLocation = gtLocation
    sensorNoiseStdev = rand.nextDouble() * 10.0
    destination = (500, 500) // TODO: Constant destination for now
    // destination = (1000 * (rand.nextDouble() - 0.5), 500 * rand.nextDouble() + 500)
    wcRegionY2 = 250 + 250 * rand.nextDouble()
    wcRegionY1 = 250 * rand.nextDouble()
    val (x,y) = destination
    val hypot = Math.hypot(x, y)
    gtVelocity = (uuvSpeed * x/hypot, uuvSpeed * y/hypot)
    estVelocity = gtVelocity
    waterCurrentVector = ((rand.nextDouble() - 0.5) * 4.0/*2.0*/, (rand.nextDouble() - 0.5) * 4.0/*2.0*/) //GFRY // try dramatically increase
    P = MatrixUtils.createRealIdentityMatrix(2)

    // Reset sliding window of state frames
    stateWindow = Array.fill(numStateFrames)(Array(estVelocity._1, estVelocity._2, gtVelocity._1, gtVelocity._2)).toList //GFRY
    state = Array(estVelocity._1, estVelocity._2, gtVelocity._1, gtVelocity._2) //GFRY
    state = stateWindow.foldLeft(Array[Double]()){ (acc, i) => acc ++ i}

    //    println(destination, state.toList)
    initialDist = Math.hypot(destination._1, destination._2)
    state
  }
  override def step(exploreExploitAction: List[TrainingControls]): (TrainingControls, TrainingState, TrainingMetric, Boolean) = {
    val (estLocX, estLocY) = estLocation
    val (destX, destY) = destination
    val inWaterCurrentRegion = estLocY >= wcRegionY1 && estLocY <= wcRegionY2
    val (cX, cY) = if(inWaterCurrentRegion) waterCurrentVector else (0.0,0.0)
    val biasAndNoise = sensorNoiseStdev * rand2.nextGaussian()

    // update GROUND TRUTH vehicle velocity by pointing heading towards destination from ESTIMATED location
    // simulates navigation via dead reckoning
    // controls updates UUV heading
    val controls = exploreExploitAction.head
    val heading = Math.atan2(destY - estLocY, destX - estLocX) + controls(0)
    val (vX, vY) = (uuvSpeed*Math.cos(heading), uuvSpeed*Math.sin(heading))
    gtVelocity = (vX + cX, vY + cY)
    val sensorVx = vX + cX + biasAndNoise
    val sensorVy = vY + cY + biasAndNoise

    val Zn = new ArrayRealVector(Array(sensorVx, sensorVy))
    val Un = new ArrayRealVector(Array(0.0, 0.0))
    val xPrev = new ArrayRealVector(Array(estVelocity._1, estVelocity._2))
    val pPrev = P

//    println(s"controls: ${controls.toList}")
    val kfOutput: KalmanFilterOutput =
        generateDataPoint(pPrev, xPrev, Zn, Un,
          defaultControls(0), defaultControls(1), defaultControls(2), defaultControls(3),
          defaultControls(4), defaultControls(5), defaultControls(6), defaultControls(7),
          defaultControls(8), defaultControls(9), defaultControls(10), defaultControls(11),
          defaultControls(12), defaultControls(13), defaultControls(14), defaultControls(15), destination)

    val pNext = kfOutput.getCovariance
    //if(steps < 20) println(s"covariance: ${pNext}")
    val velocityVector = kfOutput.getState.getDeltaComponents.toArray
    estVelocity = (velocityVector(0), velocityVector(1))
    estLocation = (estLocation._1 + estVelocity._1, estLocation._2 + estVelocity._2)
    gtLocation = (gtLocation._1 + gtVelocity._1, gtLocation._2 + gtVelocity._2)
    P = pNext
    state = Array(estVelocity._1, estVelocity._2, sensorVx, sensorVy) // P.getEntry(0,0), P.getEntry(0,1),P.getEntry(1,0), P.getEntry(1,1))
    steps += 1
    val estDist = Math.hypot(estLocation._1 - destination._1, estLocation._2 - destination._2)
    val gtDist = Math.hypot(gtLocation._1 - destination._1, gtLocation._2 - destination._2)

    val isTerminated = steps >= maxSteps || estDist <= threshold
    val reward = if(isTerminated) -Math.pow(gtDist,2) else -1.0
    cumulativeReward += reward

    //println(s"estLocation: $estLocation, gtLocation: $gtLocation, estVelocity: $estVelocity, " +
    //  s"gtVelocity: $gtVelocity, dest: $destination, gtDist: $gtDist, cumulReward: $cumulativeReward")
//    fw.append(s"${estLocation._1},${estLocation._2},${gtLocation._1},${gtLocation._2},${destination._1},${destination._2}\n")
    if(isTerminated) {
      val fw = new FileWriter(new File(resultsFileName), true)
      fw.append(s"$gtDist,")
      fw.close()
      //println(s"gtDist: $gtDist, initialgtGist: $initialDist")
      println(s"$gtDist, ${controls.toList}")
//      println(s"$gtDist")
      //println("**************************************************************************************")
    }

    // Add this state to state window
    stateWindow = stateWindow.tail :+ state
    val newState = stateWindow.foldLeft(Array[Double]()){ (acc, i) => acc ++ i}
    (controls, newState, reward, isTerminated)
  }

  @throws(classOf[SingularMatrixException])
  private def generateDataPoint(pPrev: RealMatrix, xPrev: RealVector, Zn: RealVector, Un: RealVector,
                                ctrlVar0: Double, ctrlVar1: Double, ctrlVar2: Double, ctrlVar3: Double,
                                ctrlVar4: Double, ctrlVar5: Double, ctrlVar6: Double, ctrlVar7: Double,
                                ctrlVar8: Double, ctrlVar9: Double, ctrlVar10: Double, ctrlVar11: Double,
                                ctrlVar12: Double, ctrlVar13: Double, ctrlVar14: Double, ctrlVar15: Double,
                                destination: (Double, Double)): KalmanFilterOutput = {
    // FIXED CONTROLS
    val H: RealMatrix = MatrixUtils.createRealIdentityMatrix(2) // observation matrix (no controls)
    val output: Array[AnyRef] = kf.autoTransformedrunAlgorithm(xPrev, Zn, Un, pPrev,
      ctrlVar0, ctrlVar1, ctrlVar2, ctrlVar3,
      ctrlVar4, ctrlVar5, ctrlVar6, ctrlVar7,
      H.getEntry(0,0), 0, 0, H.getEntry(1,1),
      ctrlVar8, ctrlVar9, ctrlVar10, ctrlVar11,
      ctrlVar12, ctrlVar13, ctrlVar14, ctrlVar15)

    val stateVec = output(0).asInstanceOf[RealVector]
    val covariance = output(1).asInstanceOf[RealMatrix]
    val residual = output(2).asInstanceOf[RealVector]
    val componentState = new ComponentState(new ArrayRealVector(Array.empty[Double]), stateVec)
    new KalmanFilterOutput(componentState, covariance, residual)
  }
}