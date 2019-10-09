package com.cra.princess.remusclient.sensortransformer

import java.io.File
import java.util.concurrent.atomic.AtomicBoolean

import com.cra.princess.core.{FaultData, SensorTransformer}
import com.cra.princess.evaluation.EvaluationMessenger
import com.cra.princess.metron.remus.state._
import com.cra.princess.remusclient.RemusClient
import com.cra.princess.util.Logs

class NativeSensorTransformer(modelPath: String = ".") extends RemusSensorTransformer with Logs {

  private val em = EvaluationMessenger.getInstance()
  private val componentName = "Sensor Transformer"
  private val DIMENSION = "surge"
  private val SURGE_IDX = 4
  private val dataModelSurge: Array[Double] = loadModel()
  private val doAdapt: AtomicBoolean = new AtomicBoolean(false)
  private val failureStatus: Array[Double] = Array.fill[Double](20)(0)
  private val FAILURE_THRESHOLD = 0.95
  private var latestRpmReading: Option[RemusRpmData] = None
  private var latestWaterspeedReading: Option[RemusWaterSpeedData] = None

  System.loadLibrary("octavebridge")

  @native
  private def init(path: String): Boolean

  {
    val success = init(modelPath)
    if (!success) throw new RuntimeException("Failed to initialize Octave")
  }

  @native
  private def cleanUp(): Unit

  @native
  private def detect(reading: Array[Array[Double]], train_adapt: Array[Double], sensor: Int, failure_status: Array[Double]): DetectionResult

  @native
  private def adapt(reading: Array[Array[Double]], train_adapt: Array[Double], sensor: Int): AdaptationResult

  override def finalize(): Unit = {
    this.cleanUp()
  }

  private def setAdaptationEnabled(enabled: Boolean): Unit = doAdapt.set(enabled)

  override def processSensorReadings(readings: RemusDvlData): TransformedRemusDvlData = {
    val dataList = readingsTo2DArray(readings)
    val detectionResult = detect(dataList, dataModelSurge, SURGE_IDX, failureStatus)
    log.info(s"Sensor transformer conf = ${detectionResult.fail_conf}")

    // Update failure_status array
    for (i <- detectionResult.fail_status.indices) {
      this.failureStatus(i) = detectionResult.fail_status(i)
    }

    if (detectionResult.fail_conf > FAILURE_THRESHOLD) {
      log.info(s"Sensor failure detected: $DIMENSION")
      em.sendPerturbationDetectedMessage(DIMENSION, detectionResult.fail_conf)
      val fault = new FaultData(DIMENSION, System.currentTimeMillis())
      this.fireFaultDetected(fault)
    }

    // if failure confidence is over some threshold (currently 0.5) and adaptation is enabled, then perform adaptation
    val newSurge = if (doAdapt.get()) {
      val adaptationResult = adapt(dataList, dataModelSurge, 4)
      // replace the surge value and the surge confidence accordingly
      adaptationResult.adapt_val
    } else readings.getSurge

    // Populate transformed DVL reading data
    copyToTransformedReading(readings, newSurge)
  }

  private def copyToTransformedReading(dvlData: RemusDvlData, surge: Double): TransformedRemusDvlData =
    new TransformedRemusDvlData(
      dvlData.getTimestamp, dvlData.getDepth, dvlData.getvE(), dvlData.getvN(), dvlData.getvU(), dvlData.getPitch,
      dvlData.getRoll, dvlData.getHeading, 1, 1, 1, 0, 0, 0,
      surge, dvlData.getSway, dvlData.getHeave, 1, 1, 1, 0, 0, 0)

  private def loadModel(): Array[Double] = {
    val filename = new File(modelPath, "model_surge.txt").getCanonicalPath
    val buffer = scala.io.Source.fromFile(filename)
    val lines = for (line <- buffer.getLines) yield line
    log.debug(s"sensor transformer model loaded from file: $filename")
    lines.map(_.toDouble).toArray
  }

  private def readingsTo2DArray(readings: RemusDvlData): Array[Array[Double]] = {
    val rpm = this.latestRpmReading match {
      case Some(reading) => reading.getRpm
      case _ => 0.0
    }

    val ws = this.latestWaterspeedReading match {
      case Some(reading) => reading.getSpeed
      case _ => 0.0
    }

    val data_list: Array[Array[Double]] = new Array[Array[Double]](1)
    data_list(0) = Array(
      readings.getvE, readings.getvN, readings.getvU,
      readings.getSurge, readings.getHeave, readings.getSway,
      readings.getPitch, readings.getRoll, readings.getDepth, readings.getHeading,
      rpm, ws)
    data_list
  }

  override def rpmSensorUpdate(rpmDataUpdateMessage: RemusRpmData): Unit =
    this.latestRpmReading = Some(rpmDataUpdateMessage)

  override def waterSpeedSensorUpdate(waterSpeedDataUpdateMessage: RemusWaterSpeedData): Unit =
    this.latestWaterspeedReading = Some(waterSpeedDataUpdateMessage)

  override def doTransform(dimension: String): Unit = {
    em.sendAdaptationStartedMessage(componentName)
    log.info(s"Invoking transformation on sensor dimension: $dimension")
    setAdaptationEnabled(true)
    em.sendAdaptationCompletedMessage(componentName)
  }
}

case class DetectionResult(fail_conf: Double, fail_type: Int, fail_status: Array[Double]) {
  override def toString: String = {
    val failureType =
      fail_type match {
        case 1 => "stuck-at"
        case 2 => "high noise"
        case 3 => "miscalibration"
        case 4 => "repeated outliers"
        case 5 => "repeated spikes"
        case _ => "unknown"
      }

    s"fail_conf: $fail_conf, fail_type: $failureType, fail_status: [${fail_status.mkString(",")}]"
  }
}

case class AdaptationResult(adapt_val: Double, adapt_err: Double);
