package com.cra.princess.simulation;

import java.awt.geom.Point2D;

import javax.json.JsonObject;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.events.EventDispatcher;

public class BasicVehicleSim implements TimeStepped, MessageHandler<VehicleCommand>, JsonConfigurable {
    private double vE = 0;
    private double vN = 0;
    private double vU = 0;
    
    private double posE = 0;
    private double posN = 0;
    private double posU = 0;
        
    private double originDepth = 0;

    private double pitch = 0;
    private double roll = 0;
    private double heading = 0;
    
    private BasicVehicleSimConfiguration config = new BasicVehicleSimConfiguration();
    private LtpGeodetics geoCalc;
    private double[] latLon;
    
    public static class BasicVehicleSimConfiguration{
        public double originLat;
        public double originLon;
        public double originDepth;
    }
    
    @Override
    public void configure(JsonObject o) {
        if (o.containsKey("origin")) {
            JsonObject origin = o.getJsonObject("origin");
            config.originLat = origin.getJsonNumber("lat").doubleValue();
            config.originLon = origin.getJsonNumber("lon").doubleValue();
            config.originDepth = origin.getJsonNumber("depth").doubleValue();
        } else {
            config.originLat = 0;
            config.originLon = 0;
            config.originDepth = 0;
        }
            
    }
    
    public void configure(BasicVehicleSimConfiguration config) {
        this.config = config;
    }
    
    @Override
    public void initialize() {
        geoCalc = new LtpGeodetics(config.originLat, config.originLon);        
        originDepth = config.originDepth;
        reset();
        lastUpdate = TimeManager.now();
    }

    private long lastUpdate = 0;

    @Override
    public void update() {
        long elapsed = TimeManager.now() - lastUpdate;
        lastUpdate = TimeManager.now();
        latLon = geoCalc.getLatLon(posN, posE);
        Point2D current = World.currentSource.current(latLon[0], latLon[1], -posU);
        posE += (vE + current.getX()) * elapsed / 1000;
        posN += (vN + current.getY()) * elapsed / 1000;
        posU += (vU                 ) * elapsed / 1000;

        GroundTruthMessage state = makeStateMessage();
        JmsManager.sendGroundTruth(state);
        EventDispatcher.publishEvent(state);     
    }

    @Override
    public void reset() {
        vE = 0;
        vN = 0;
        vU = 0;
        posE = 0;
        posN = 0;
        posU = 0;
        pitch = 0;
        roll = 0;
        heading = 0;
    }

    private GroundTruthMessage makeStateMessage() {
        // Could have the message as a member variable, but I'd be nervous about its
        // mutability.
        GroundTruthMessage m = new GroundTruthMessage();
        m.heading = heading;
        m.pitch = pitch;
        m.roll = roll;
        m.timestamp = TimeManager.now();
        latLon = geoCalc.getLatLon(posN, posE);
        m.trueLatitude = latLon[0];
        m.trueLongitude = latLon[1];
        m.trueDepth = originDepth -posU;
        Point2D current = World.currentSource.current(latLon[0], latLon[1], -posU);
        m.vE = vE + current.getX();
        m.vN = vN + current.getY();
        m.vU = vU;
        return m;
    }

    @Override
    public void handleMessage(VehicleCommand message) {
        double newHeading = Math.toRadians(90 - message.headingTarget);
        double newVelocity = message.speedTarget;
        vE = newVelocity * Math.cos(newHeading);
        vN = newVelocity * Math.sin(newHeading);
        heading = newHeading;
    }

    @Override
    public void stop() {
    }

}
