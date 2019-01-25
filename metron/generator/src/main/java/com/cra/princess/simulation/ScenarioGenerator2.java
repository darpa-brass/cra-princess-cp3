package com.cra.princess.simulation;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonReader;
import javax.json.JsonWriter;
import javax.json.JsonWriterFactory;
import javax.json.stream.JsonGenerator;

import org.json.simple.parser.ParseException;

import com.cra.princess.simulation.CliParser.Perturbation;


public class ScenarioGenerator2 {
    
    // JSONObject extends Map but is not type-parameterized.  This leads to compiler warnings in the following
    static public void BuildScenario(CliParser param) throws IOException, ParseException {
        // Load the pieces
        JsonObject base = getJson2(param.base);
        JsonObject vehicle = getJson2(param.vehicle);
        JsonObject sensor = getJson2(param.sensor);
        JsonObject world = getJson2(param.world);
        
        // Snap together templates
        base = Json.createPatchBuilder()
                .add("/vehicle", vehicle)
                .add("/sensor", sensor)
                .add("/world", world)
                .build()
                .apply(base);
        
        // Apply origin perturbation
        double lat = vehicle.getJsonObject("config").getJsonObject("origin").getJsonNumber("lat").doubleValue();
        double lon = vehicle.getJsonObject("config").getJsonObject("origin").getJsonNumber("lon").doubleValue();
        double depth = vehicle.getJsonObject("config").getJsonObject("origin").getJsonNumber("depth").doubleValue();
        
        LtpGeodetics geo = new LtpGeodetics(lat, lon);
        double[] latlon = geo.getLatLon(param.offsetEnu[1], param.offsetEnu[0]);
        base = Json.createPatchBuilder()
                .add("/vehicle/config/origin/lat", Json.createValue(latlon[0]))
                .add("/vehicle/config/origin/lon", Json.createValue(latlon[1]))
                .add("/vehicle/config/origin/depth", Json.createValue(depth - param.offsetEnu[2]))
                .build()
                .apply(base);
        
        // Apply current perturbation
        if (param.perturb != null) {
            JsonArray regions = base.getJsonObject("world").getJsonObject("current").getJsonObject("config").getJsonArray("regions");
            JsonArrayBuilder builder = Json.createArrayBuilder(regions);
            for (Perturbation perturb : param.perturb) {
                boolean foundIt = false;
                for (int i = 0; i < regions.size(); ++i) {
                    JsonObject region = (JsonObject) regions.get(i);
                    String tag = region.getString("tag");
                    if (tag != null && tag.equalsIgnoreCase(perturb.tag)) {
                        builder.set(i, 
                                Json.createPatchBuilder()
                                    .add("/vN", Json.createValue(perturb.currentEnu[1]))
                                    .add("/vE", Json.createValue(perturb.currentEnu[0]))
                                    .build()
                                    .apply(region));

                        foundIt = true;
                    }
                }            
                if (!foundIt) {
                    System.err.format("Warning: Tag %s not found in world section.\n", perturb.tag);
                }
            }
            base = Json.createPatchBuilder().add("/world/current/config/regions", builder.build()).build().apply(base);
        }
        
        Map<String, Object> config = new HashMap<String, Object>();
        config.put(JsonGenerator.PRETTY_PRINTING, true);
        JsonWriterFactory writerfactory = Json.createWriterFactory(config);
        FileWriter fw = new FileWriter(param.output + "2");
        JsonWriter writer = writerfactory.createWriter(fw);
        writer.write(base);
        fw.flush();
        fw.close();
    }
    
    static protected JsonObject getJson2(String filename) throws FileNotFoundException {
        if (filename == null)
            return null;
        JsonReader reader = Json.createReader(new BufferedInputStream(new FileInputStream(filename)));
        JsonObject json = reader.readObject();
        return json;
    }
}
