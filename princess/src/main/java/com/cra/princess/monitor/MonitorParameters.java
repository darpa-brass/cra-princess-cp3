//////////////////////////////////////////////////////////////////
// Charles River Analytics, Inc., Cambridge, Massachusetts
//
// Copyright (C) 2016. All Rights Reserved.
// See http://www.cra.com or email info@cra.com for information. 
//////////////////////////////////////////////////////////////////
// Custom project or class-specific comments can go here. 
//////////////////////////////////////////////////////////////////

package com.cra.princess.monitor;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.apache.log4j.Logger;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

public class MonitorParameters
{
  private static final String SCENARIO_FILE_PROPERTY_NAME = "scenario.file";
  private static boolean adaptationOn;
  private static final Logger log = Logger.getLogger(MonitorParameters.class);
  
  static
  {
      boolean defaultAdaptationOn = true;
      String scenarioFileName = System.getProperty(SCENARIO_FILE_PROPERTY_NAME, "/test/data");
      try
      {
        log.debug("Reading scenario file from system property: " + scenarioFileName);
        if (Files.exists(Paths.get(scenarioFileName))) {
        ObjectMapper mapper = new ObjectMapper();
        JsonNode root = mapper.readValue(new File(scenarioFileName), JsonNode.class);
        if (!root.has("adaptation_on")) {
          log.error("Scenario file does not contain 'adaptation_on' field.");
          log.debug("Using default adaptation_on value of " + defaultAdaptationOn);
          adaptationOn = defaultAdaptationOn;
        } else {
          JsonNode adapNode = root.get("adaptation_on");
          if (!adapNode.isBoolean()) {
            log.error("Invalid value for field 'adaptation_on' in scenario file. Using default value of "+ defaultAdaptationOn);
            adaptationOn = defaultAdaptationOn;
          }
          adaptationOn = adapNode.asBoolean();
          log.debug("Found adaptation_on value = " + adaptationOn);
        }
      } else {
        log.debug("Scenario file (" + scenarioFileName + ") not found. Using default adaptation_on value of " + defaultAdaptationOn);
        adaptationOn = defaultAdaptationOn;
      }
    }
    catch (IOException e)
    {
      log.error("Exception caught reading scenario file " + scenarioFileName + " - " + e.getMessage());
      adaptationOn = defaultAdaptationOn;
    }
  }
  
  public static boolean isAdaptationOn()
  {
    return adaptationOn;
  }
}
