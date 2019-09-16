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
