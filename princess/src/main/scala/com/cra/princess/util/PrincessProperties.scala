package com.cra.princess.util

import java.io.{File, FileReader, IOException}
import java.util.Properties

sealed trait RunMode
case object TEST extends RunMode
case object TRAINING extends RunMode

object PrincessProperties extends Logs {
  private val PROPERTY_FILE_NAME = "princess.properties"
  private val BASE_URL = "baseUrl"
  private val JMS_URL = "JMS_URL"
  private val PP_OPTIMIZER_FILE = "ppOptimizerFile"
  private val KF_OPTIMIZER_FILE = "kfOptimizerFile"
  private val TRUNCATE_PATH = "truncatePath"
  private val ACTOR_WEIGHTS_FILE = "actorWeightsFile"
  private val CRITIC_WEIGHTS_FILE = "criticWeightsFile"
  private val MODE = "mode"
  private val SENSOR_TRANSFORMER_THRESHOLD = "sensorTransformerThreshold"
  private val ENERGY_TO_DISTANCE_CONVERSION = "energyToDistanceConversion"
  private val ENERGY_RESERVE_INCREMENT = "energyReserveIncrement"
  private val SENSOR_FAILURE_COUNT_THRESHOLD = "sensorFailureCountThreshold"

  // DDPGTrainerOptimizer Properties
  private val MIXING_FACTOR = "mixingFactor"
  private val ACTOR_LR = "actorLR"
  private val CRITIC_LR = "criticLR"
  private val ACTOR_WEIGHT_MIN = "actorWeightMin"
  private val ACTOR_WEIGHT_MAX = "actorWeightMax"
  private val CRITIC_WEIGHT_MIN = "criticWeightMin"
  private val CRITIC_WEIGHT_MAX = "criticWeightMax"
  private val BATCH_SIZE = "batchSize"
  private val DISCOUNT_FACTOR = "discountFactor"
  private val DELTA = "delta"
  private val WINDOW_SIZE = "windowSize"

  // DDPG Experiment lines 16-24
  private val SAVE_FILE = "saveFile"
  private val NUM_FRAMES = "numFrames"
  private val FRAME_SIZE = "frameSize"
  private val STATE_DIM = "stateDim"
  private val ACTION_DIM = "actionDim"
  private val REWARD_DIM = "rewardDim"
  private val NUM_EPISODES = "numEpisodes"
  private val NODES_PER_HIDDEN_LAYER = "nodesPerHiddenLayer"
  private val MAX_STEPS_PER_EPISODE = "maxStepsPerEpisode"
  private val IDX = "idx"

  private var properties: Properties = {
    val p: Properties = new Properties
    try { // Try looking for the file in the file system
      val reader = new FileReader(new File(PROPERTY_FILE_NAME))
      p.load(reader)
      log.debug("Loaded properties from " + PROPERTY_FILE_NAME)
      p
    } catch {
      case _: IOException =>
        // The file does not exist in the current working directory - use the embedded resource
        log.warn("Cannot read file " + PROPERTY_FILE_NAME + " in current directory. Using default settings.")
        loadPropertiesAsResource(p)
    }
  }

  def baseUrl: String = properties.getProperty(BASE_URL)
  def jmsUrl: String = properties.getProperty(JMS_URL)
  def ppOptimizerFile: String = properties.getProperty(PP_OPTIMIZER_FILE)
  def kfOptimizerFile: String = properties.getProperty(KF_OPTIMIZER_FILE)
  def truncatePath: Boolean = properties.getProperty(TRUNCATE_PATH, "true").trim.toLowerCase.toBoolean
  def actorWeightsFile: String = properties.getProperty(ACTOR_WEIGHTS_FILE)
  def criticWeightsFile: String = properties.getProperty(CRITIC_WEIGHTS_FILE)
  def mode: RunMode = properties.getProperty(MODE, "test").trim.toLowerCase match {
    case "test" => TEST
    case "training" => TRAINING
    case s => {
      log.warn(s"Unknown mode: $s")
      TEST
    }
  }
  def sensorTransformerThreshold: Double = properties.getProperty(SENSOR_TRANSFORMER_THRESHOLD, "0.95").toDouble
  def energyToDistanceConversion: Double = properties.getProperty(ENERGY_TO_DISTANCE_CONVERSION, "0.00679567439").toDouble
  def energyReserveIncrement: Double = properties.getProperty(ENERGY_RESERVE_INCREMENT, "5000.0").toDouble
  def sensorFailureCountThreshold: Double = properties.getProperty(SENSOR_FAILURE_COUNT_THRESHOLD, "0").toInt
  def mixingFactor: Double = properties.getProperty(MIXING_FACTOR, "0.8").toDouble
  def actorLR: Double = properties.getProperty(ACTOR_LR, "0.00001").toDouble
  def criticLR: Double = properties.getProperty(CRITIC_LR, "0.0001").toDouble
  def actorWeightMin: Double = properties.getProperty(ACTOR_WEIGHT_MIN, "-0.000001").toDouble
  def actorWeightMax: Double = properties.getProperty(ACTOR_WEIGHT_MAX, "0.000001").toDouble
  def criticWeightMin: Double = properties.getProperty(CRITIC_WEIGHT_MIN, "-0.000001").toDouble
  def criticWeightMax: Double = properties.getProperty(CRITIC_WEIGHT_MAX, "0.000001").toDouble
  def batchSize: Int = properties.getProperty(BATCH_SIZE, "256").toInt
  def discountFactor: Double = properties.getProperty(DISCOUNT_FACTOR, "0.9").toDouble
  def delta: Double = properties.getProperty(DELTA, "0.001").toDouble
  def windowSize: Int = properties.getProperty(WINDOW_SIZE, "16").toInt
  def saveFile: String = properties.getProperty(SAVE_FILE, "ddpgKFActor.h5")
  def numFrames: Int = properties.getProperty(NUM_FRAMES, "16").toInt
  def frameSize: Int = properties.getProperty(FRAME_SIZE, "4").toInt
  def stateDim: Int = this.frameSize * this.numFrames
  def actionDim: Int = properties.getProperty(ACTION_DIM, "1").toInt
  def rewardDim: Int = properties.getProperty(REWARD_DIM, "1").toInt
  def numEpisodes: Int = properties.getProperty(NUM_EPISODES, "20000").toInt
  def nodesPerHiddenLayer: Int = properties.getProperty(NODES_PER_HIDDEN_LAYER, "128").toInt
  def maxStepsPerEpisode: Int = properties.getProperty(MAX_STEPS_PER_EPISODE, "5000").toInt
  def idx: Int = properties.getProperty(IDX, "0").toInt

  private def loadPropertiesAsResource(p: Properties): Properties = {
    try {
      val propertyFileUrl = this.getClass.getClassLoader.getResource(PROPERTY_FILE_NAME)
      if (null == propertyFileUrl) throw new IllegalStateException("Resource not found: " + PROPERTY_FILE_NAME)
      val propertyFile = propertyFileUrl.getFile
      p.load(new FileReader(new File(propertyFile)))
      p
    } catch {
      case _: IOException =>
        throw new IllegalStateException("Resource not found: " + PROPERTY_FILE_NAME)
    }
  }
}
