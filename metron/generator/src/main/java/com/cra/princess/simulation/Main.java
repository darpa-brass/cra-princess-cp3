package com.cra.princess.simulation;

import java.io.IOException;

import org.json.simple.parser.ParseException;

public class Main {

    public final static String appName = "generator";
    
    public static void main(String[] args) {
        CliParser parser = new CliParser(args);
        try {
            ScenarioGenerator.BuildScenario(parser);
            ScenarioGenerator2.BuildScenario(parser);
        } catch (IOException e) {
            System.err.println("Could not find a referenced JSON template:");
            System.err.println(e.getMessage());        
        } catch (ParseException e) {            
            // Looks like a bug in the parse exception; the message isn't very helpful
            // so convert to string
            System.err.println("Trouble parsing JSON.\n" + e.toString());            
        }       
    }
    
 
}
