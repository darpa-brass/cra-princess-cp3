package com.cra.princess.simulation;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import com.cra.princess.simulation.CliParser.Perturbation;


public class ScenarioGenerator {
    
    // JSONObject extends Map but is not type-parameterized.  This leads to compiler warnings in the following
    @SuppressWarnings("unchecked")
    static public void BuildScenario(CliParser param) throws IOException, ParseException {
        // Load the pieces
        JSONObject base = getJson(param.base);
        JSONObject vehicle = getJson(param.vehicle);
        JSONObject sensor = getJson(param.sensor);
        JSONObject world = getJson(param.world);
        
        // Snap together templates
        JSONObject scenario = (JSONObject) base.clone();
        if (vehicle != null) {            
            scenario.put("vehicle", vehicle);
        }
        if (sensor != null) {
            JSONObject vehicleSection = (JSONObject) scenario.get("vehicle");
            vehicleSection.put("sensor", sensor);            
        }
        if (world != null) {
            scenario.put("world", world);
        }
        
        // Apply origin perturbation
        vehicle = (JSONObject) scenario.get("vehicle");
        JSONObject config = (JSONObject) vehicle.get("config");
        JSONObject origin = (JSONObject) config.get("origin");        
        LtpGeodetics geo = new LtpGeodetics(asDouble(origin.get("lat")), asDouble(origin.get("lon")));
        double[] latlon = geo.getLatLon(param.offsetEnu[1], param.offsetEnu[0]);
        origin.put("lat", new Double(latlon[0]));
        origin.put("lon", new Double(latlon[1]));
        origin.put("depth", new Double(asDouble(origin.get("depth")) - param.offsetEnu[2]));
        
        // Apply current perturbation
        if (param.perturb != null) {
            world = (JSONObject) scenario.get("world");
            JSONObject current = (JSONObject) world.get("current");
            config = (JSONObject) current.get("config");
            JSONArray regions = (JSONArray) config.get("regions");
            for (Perturbation perturb : param.perturb) {
                boolean foundIt = false;
                for (int i=0; i<regions.size(); i++) { // This POS isn't iterable...
                    JSONObject region = (JSONObject) regions.get(i);
                    String tag = (String) region.get("tag");                    
                    if (tag != null && tag.equals(perturb.tag)) {
                        region.put("vN", new Double(perturb.currentEnu[1]));
                        region.put("vE", new Double(perturb.currentEnu[0]));
                        foundIt = true;
                    }
                }            
                if (!foundIt) {
                    System.err.format("Warning: Tag %s not found in world section.\n", perturb.tag);
                }
            }
        }
        
        // Write the file
        FileWriter file = new FileWriter(param.output);
        file.write(scenario.toJSONString());
        file.flush();
        file.close();
    }
    
    // Really nasty...
    static protected double asDouble(Object o) {
        if (o instanceof Double)
            return (Double) o;
        if (o instanceof Long)
            return (double) (Long) o;
        return Double.NaN;
    }
    
    static protected JSONObject getJson(String filename) throws IOException, ParseException {
        if (filename == null)
            return null;
        JSONParser parser = new JSONParser();
        JSONObject json = (JSONObject) parser.parse(new FileReader(filename));        
        return json;
    }
}
