package com.cra.princess.remusclient.util

import java.io.File
import java.nio.file.{Files, Paths}

import com.cra.princess.util.Logs
import com.fasterxml.jackson.databind.{JsonNode, ObjectMapper}

/**
  * Created by smarotta on 4/24/2017.
  */
object ScenarioParameters extends Logs {
  private val SCENARIO_FILE_PROPERTY_NAME = "scenario.file"
  val destination = init

  private def init: (Double, Double) = {
    val defaultDestination = (0.00, 0.01)
    val scenarioFileName: String = System.getProperty(SCENARIO_FILE_PROPERTY_NAME, "/test/data")
    log.debug(s"Reading scenario file from system property: $scenarioFileName")
    val scenarioPath = Paths.get(scenarioFileName)
    if (Files.exists(scenarioPath)) {
      if (Files.isDirectory(scenarioPath)) {
        log.error(s"$scenarioFileName found but was a directory. Using default default destination value of $defaultDestination")
        defaultDestination
      } else {
        val mapper = new ObjectMapper()
        val root = mapper.readValue(new File(scenarioFileName), classOf[JsonNode])
        val destination: (Double, Double) = {
          if (!root.has("destination")) {
            log.error("Scenario file does not contain 'destination' field.")
            log.debug(s"Using default destination value of $defaultDestination")
            defaultDestination
          } else {
            val destinationNode = root.get("destination")
            if (!destinationNode.has("lat") || !destinationNode.has("long")) {
              log.error("Scenario file destination field improperly formatted. Must contain 'lat' and 'long' fields.")
              log.debug(s"Using default destination value of $defaultDestination")
              defaultDestination
            } else {
              val lat = destinationNode.get("lat").asDouble()
              val lon = destinationNode.get("long").asDouble()
              log.debug(s"Destination read from scenario file: ($lat, $lon)")
              (lat, lon)
            }
          }
        }

        destination
      }
    } else {
      log.error(s"Scenario file ($scenarioFileName) not found. Using default destination value of $defaultDestination")
      defaultDestination
    }
  }
}
