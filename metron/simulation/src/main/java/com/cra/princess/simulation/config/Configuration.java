package com.cra.princess.simulation.config;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonException;
import javax.json.JsonNumber;
import javax.json.JsonObject;
import javax.json.JsonReader;
import javax.json.JsonValue;
import javax.json.JsonWriterFactory;
import javax.json.stream.JsonGenerator;

import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.ConfigurationException;
import com.cra.princess.simulation.JsonConfigurableFactory;
import com.cra.princess.simulation.events.TimedEvent;
import com.cra.sim.sensor.ObjectDetectionModel;

/**
 * Convenience class for reading simulator config file values.
 * <p>
 * 
 * BACKGROUND: Unstructured (no schema) JSON was chosen for simulator development to support rapid, flexible
 * development. Different components' configurations are decoupled in that each only needs to read its own chunk of a
 * JSON tree. As of this writing, it is intended that we will continue using a very dynamic structure for configuration.
 * <p>
 * 
 * This class will provide functionality to access / mutate sections of the configuration file as required by the 
 * evaluator. 
 * 
 * @author chagnon
 *
 */
public class Configuration {
    private JsonObject config;
    private JsonWriterFactory writerFactory;

    public Configuration() throws FileNotFoundException {
        this("scenario.json");
    }
    
    public Configuration(String fileName) throws FileNotFoundException {
        this(new BufferedInputStream(new FileInputStream(fileName)));
    }

    public Configuration(InputStream configStream) {
        JsonReader reader = Json.createReader(configStream);
    
        config = reader.readObject();

        Map<String, Object> printerConfig = new HashMap<String, Object>();
        printerConfig.put(JsonGenerator.PRETTY_PRINTING, true);
        writerFactory = Json.createWriterFactory(printerConfig);
    }
    
    public JsonObject getJsonObject() {
    	return config;
    }
    
    public String getJsonString() {
        StringWriter w = new StringWriter();
        writerFactory.createWriter(w).write(config);
        return w.toString();
    }
    
    public long getSeed() {
        return config.getJsonNumber("seed").longValue();
    }
    
    public void setSeed(long seed) {
        setLong("/seed", seed);
    }
    
    public ConfigLocation getDestination() {
        return parseLocation(getJsonObject("/mission/destination", config));
    }
    
    public void setDestination(ConfigLocation destination) {
        setDestination(destination.getLatitude(), destination.getLongitude(), destination.getDepth());
    }
    
    public void setDestination(double latitude, double longitude, double depth) {
        setDouble("/mission/destination/lat", latitude);
        setDouble("/mission/destination/lon", longitude);
        setDouble("/mission/destination/depth", depth);
    }

    public Region getSearchRegion() {
        Region r = new Region();
        r.configure(getJsonObject("/mission/searcharea", config));
        return r;
    }
    
    public void setSearchRegion(Region r) {
        setJsonObject("/mission/searcharea", r.getJsonObject());
    }
    
    public ConfigLocation getVehicleOrigin() {
        return parseLocation(getJsonObject("/vehicle/config/origin", config));
    }
    
    public void setVehicleOrigin(ConfigLocation origin) {
        setVehicleOrigin(origin.getLatitude(), origin.getLongitude(), origin.getDepth());
    }
    
    public void setVehicleOrigin(double latitude, double longitude, double depth) {
        setDouble("/vehicle/config/origin/lat", latitude);
        setDouble("/vehicle/config/origin/lon", longitude);
        setDouble("/vehicle/config/origin/depth", depth);
    }

    public double getVehicleHeading() {
        return getJsonNumber("/vehicle/config/ic/heading", config).doubleValue();
    }
    public void setVehicleHeading(double headingDegrees) {
        setDouble("/vehicle/config/ic/heading", headingDegrees);
    }

    public double getVehiclePitch() {
        return getJsonNumber("/vehicle/config/ic/pitch", config).doubleValue();
    }
    public void setVehiclePitch(double pitchDegrees) {
        setDouble("/vehicle/config/ic/pitch", pitchDegrees);
    }

    public double getVehicleSpeed() {
        return getJsonNumber("/vehicle/config/ic/speed", config).doubleValue();
    }
    public void setVehicleSpeed(double speedMetersPerSecond) {
        setDouble("/vehicle/config/ic/speed", speedMetersPerSecond);
    }
    
    public VehicleCommand getVehicleCommand() {
        VehicleCommand vc = new VehicleCommand();
        vc.speedTarget = getJsonNumber("/vehicle/config/command/speedTarget", config).doubleValue();
        vc.headingTarget = getJsonNumber("/vehicle/config/command/headingTarget", config).doubleValue();
        vc.depthTarget = getJsonNumber("/vehicle/config/command/depthTarget", config).doubleValue();
        return vc;
    }
    public void setVehicleCommand(VehicleCommand vc) {
        setDouble("/vehicle/config/command/speedTarget", vc.speedTarget);
        setDouble("/vehicle/config/command/headingTarget", vc.headingTarget);
        setDouble("/vehicle/config/command/depthTarget", vc.depthTarget);
    }

    public TimedEvent[] getEvents() {
        JsonArray event = getJsonArray("/events", config);
        TimedEvent[] ans = new TimedEvent[event.size()];
        JsonConfigurableFactory factory = new JsonConfigurableFactory();
        for (int i = 0; i < event.size(); ++i) {
            JsonObject p = (JsonObject) event.get(i);
            TimedEvent e = (TimedEvent) factory.construct(event.getJsonObject(i));
            e.configure(p.getJsonObject("config"));
            ans[i] = e;
        }
        return ans;
    }
    
    public void setEvents(TimedEvent[] events) {
        JsonArrayBuilder builder = Json.createArrayBuilder();
        for (TimedEvent event: events) {
            JsonObject o = event.getJsonObject();
            builder.add(o);
        }
        config = Json.createPatchBuilder().replace("/events", builder.build()).build().apply(config);
    }
    
    public void addEvent(TimedEvent event) {
        JsonArray events = getJsonArray("/events", config);
        JsonArrayBuilder builder = Json.createArrayBuilder(events);
//        for (int i = 0; i < events.size(); ++i) {
//            if (events.getJsonObject(i).getJsonObject("config").getString("name").equals(((TimedEvent) event.getPayload()).name)) {
//                events = builder.set(i, event.getJsonObject()).build();
//                config = Json.createPatchBuilder().add("/events", events).build().apply(config);
//                return;
//            }
//        }
        events = builder.add(event.getJsonObject()).build();
        config = Json.createPatchBuilder().add("/events", events).build().apply(config);
    }
    
    public void clearEvents() {
    	config = Json.createPatchBuilder().add("/events", Json.createArrayBuilder().build()).build().apply(config);
    }

    public List<CurrentRegion> getCurrentRegions() {
        JsonArray regions = getJsonArray("/world/current/config/regions", config);
        List<CurrentRegion> ans = new ArrayList<CurrentRegion>();
        for (JsonValue region : regions) {
            CurrentRegion cr = new CurrentRegion();
            cr.configure((JsonObject) region);
            ans.add(cr);
        }
        return ans;
    }
    
    public void clearCurrentRegions() {
        config = Json.createPatchBuilder().add("/world/current/config/regions", Json.createArrayBuilder().build()).build().apply(config);
    }
    
    public void addCurrentRegion(CurrentRegion region) {
        JsonArrayBuilder builder = Json.createArrayBuilder(getJsonArray("/world/current/config/regions", config));
        builder.add(region.getJsonObject());
        config = Json.createPatchBuilder().add("/world/current/config/regions", builder.build()).build().apply(config);
    }
    
    public void clearBathymetryRegions() {
        config = Json.createPatchBuilder().add("/world/bathymetry/config/regions", Json.createArrayBuilder().build()).build().apply(config);
    }
    
    public void addBathymetryRegion(BathymetryRegion region) {
    	JsonArrayBuilder builder;
    	try {
    		builder = Json.createArrayBuilder(getJsonArray("/world/bathymetry/config/regions", config));
    	} catch (JsonException e) {
    		builder = Json.createArrayBuilder();
    	}
        builder.add(region.getJsonObject());
        config = Json.createPatchBuilder().add("/world/bathymetry/config/regions", builder.build()).build().apply(config);
    }
    
    public List<BathymetryRegion> getBathymetryRegions() {
    	List<BathymetryRegion> ans = new ArrayList<BathymetryRegion>();    
    	try {
    		JsonArray regions = getJsonArray("/world/bathymetry/config/regions", config);    		
            for (JsonValue region : regions) {
            	BathymetryRegion cr = new BathymetryRegion();
                cr.configure((JsonObject) region);
                ans.add(cr);
            }            
    	} catch (JsonException e) {
    		// Empty
    	}
    	return ans;
        
    }

    public void setDefaultDepth(double depth) {
    	setDouble("/world/bathymetry/config/defaultDepth", depth);
    }
    
    public double getDefaultDepth() {
    	return getJsonNumber("/world/bathymetry/config/defaultDepth", config).doubleValue();
    }
    
    public void clearDetectableObjects() {
        config = Json.createPatchBuilder().add("/world/object/config/objects", Json.createArrayBuilder().build()).build().apply(config);
    }
    
    public void addDetectableObject(DetectableObject object) {
        JsonArrayBuilder builder = Json.createArrayBuilder(getJsonArray("/world/object/config/objects", config));
        builder.add(object.getJsonObject());
        config = Json.createPatchBuilder().add("/world/object/config/objects", builder.build()).build().apply(config);
    }
    
    public List<DetectableObject> getDetectableObjects() {
        JsonArray regions = getJsonArray("/world/object/config/objects", config);
        List<DetectableObject> ans = new ArrayList<DetectableObject>();
        for (JsonValue region : regions) {
        	DetectableObject cr = new DetectableObject();
            cr.configure((JsonObject) region);
            ans.add(cr);
        }
        return ans;
    }

    
    
    public List<SensorModel> getSensorModels() {
        List<SensorModel> ans = new ArrayList<SensorModel>();
        
        findSensors(config, ans);
        
        return ans;
    }
    
    public void setSensorModel(SensorModel model) {
        if (!setSensorModel(config, model, "")) {
            throw new ConfigurationException("No sensor found with name '" + model.getName() + ".  Could not apply sensor model " + model.toString() + ".");
        }
    }

    public static ConfigLocation parseLocation(JsonObject location) {
        double lat = location.getJsonNumber("lat").doubleValue();
        double lon = location.getJsonNumber("lon").doubleValue();
        double depth = location.getJsonNumber("depth").doubleValue();
        return new ConfigLocation(lat, lon, depth);
    }

    public ObjectDetectionModel getDetectionModel(String sensor) {
        String sensorPtr = findSensorByName(sensor);
        if (sensorPtr == null) {
            throw new ConfigurationException("Couldn't find sensor '" + sensor +".");
        }
        return (ObjectDetectionModel) new JsonConfigurableFactory().construct(getJsonObject(sensorPtr + "/config/detection", config));
    }

    public void setDetectionModel(String sensor, ObjectDetectionModel model) {
        String sensorPtr = findSensorByName(sensor);
        if (sensorPtr == null) {
            throw new ConfigurationException("Couldn't find sensor '" + sensor +".");
        }
        config = Json.createPatchBuilder().add(sensorPtr + "/config/detection", model.getJsonObject()).build().apply(config);
    }

    // Heuristic.  Hope it doesn't break easily.
    private boolean isASensor(JsonObject o) {
        return o.containsKey("bias") && o.containsKey("noiseDev") && o.containsKey("name") && !o.containsKey("time");
    }
    
    private boolean setSensorModel(JsonValue v, SensorModel model, String path) {
        if (v instanceof JsonObject) {
            JsonObject o = (JsonObject) v;
            if (isASensor(o) && o.getString("name").equals(model.getName()))  {
                config = Json.createPatchBuilder().add(path, model.getJsonObject()).build().apply(config);
                return true;
            }
            for (Entry<String, JsonValue> entry : o.entrySet()) {
                if(setSensorModel(entry.getValue(), model, path + "/" + entry.getKey())) {
                    return true;
                };
            }
        }
        if (v instanceof JsonArray) {
            JsonArray arr = (JsonArray) v;
            for (int i = 0; i < arr.size(); ++i) {
                JsonValue item = arr.get(i);
                if (item instanceof JsonObject) {
                    JsonObject o = (JsonObject) item;
                    if (isASensor(o) && o.getString("name").equals(model.getName()))  {
                        arr = Json.createArrayBuilder((JsonArray) v).set(i, model.getJsonObject()).build();
                        config = Json.createPatchBuilder().add(path, arr).build().apply(config);
                        return true;
                    }
                    if (setSensorModel(o, model, path + "/" + i)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    private void findSensors(JsonObject o, List<SensorModel> sensors) {
        if (isASensor(o)) {
            SensorModel s = new SensorModel();
            s.configure(o);
            sensors.add(s);
        } else {
            for (JsonValue item : o.values()) {
                if (item instanceof JsonObject) {
                    findSensors((JsonObject) item, sensors);
                }
                if (item instanceof JsonArray) {
                    findSensors((JsonArray) item, sensors);
                }
            }
        }
    }

    private String findSensorByName(String name) {
        JsonArray sensors = getJsonArray("/vehicle/sensors", config);
        for (int i = 0; i < sensors.size(); ++i) {
            if (sensors.getJsonObject(i).getString("name").equals(name)) {
                return "/vehicle/sensors/" + i;
            }
        }
        return null;
    }
    
    private void findSensors(JsonArray array, List<SensorModel> sensors) {
        for (JsonValue item : array) {
            if (item instanceof JsonObject) {
                findSensors((JsonObject) item, sensors);
            }
            if (item instanceof JsonArray) {
                findSensors((JsonArray) item, sensors);
            }
        }
    }
    
    private JsonConfigurableFactory fac = new JsonConfigurableFactory();
    private void build(JsonArray array) {
        for (JsonValue item : array) {
            if (item instanceof JsonObject) {
                build((JsonObject) item);
            }
            if (item instanceof JsonArray) {
                build((JsonArray) item);
            }
        }
    }
    
    private void build(JsonObject what) {
        if (what.containsKey("type") && what.containsKey("config")) {
            fac.construct(what);
        }
        for (JsonValue item : what.values()) {
            if (item instanceof JsonObject) {
                build((JsonObject) item);
            }
            if (item instanceof JsonArray) {
                build((JsonArray) item);
            }
        }
    }
    
    private void build() {
        build(config);
    }
    
    private void setDouble(String where, double what) {
        config = Json.createPatchBuilder().add(where, Json.createValue(what)).build().apply(config);
        build();
    }

    private void setLong(String where, long what) {
        config = Json.createPatchBuilder().add(where, Json.createValue(what)).build().apply(config);
        build();
    }

    private void setJsonObject(String where, JsonObject what) {
        config = Json.createPatchBuilder().add(where, what).build().apply(config);
        build();
    }
    
    private JsonObject getJsonObject(String where, JsonObject who) {
        return who.getValue(where).asJsonObject();
    }
    
    private JsonNumber getJsonNumber(String where, JsonObject who) {
        return (JsonNumber) who.getValue(where);
    }
    
    private JsonArray getJsonArray(String where, JsonObject who) {
        return who.getValue(where).asJsonArray();
    }
}
