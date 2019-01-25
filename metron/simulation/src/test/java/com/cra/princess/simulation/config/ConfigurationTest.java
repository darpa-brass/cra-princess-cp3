package com.cra.princess.simulation.config;

import java.io.ByteArrayInputStream;
import java.io.FileNotFoundException;

import javax.json.Json;
import javax.json.JsonReader;

import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.ConfigurationException;
import com.cra.princess.simulation.events.SensorPerturbationEvent;
import com.cra.princess.simulation.events.TimedEvent;
import com.cra.sim.sensor.ObjectDetectionModel;
import com.cra.sim.sensor.RangeDependentObjectDetectionModel;

public class ConfigurationTest {
    public static void main(String[] args) throws FileNotFoundException {
        Configuration c = new Configuration("scenario.json");
        System.out.println(c.getVehicleCommand());
        TimedEvent[] orig = c.getEvents();
        TimedEvent[] changed = new TimedEvent[2];
        changed[0] = orig[0];
        SensorPerturbationEvent e = new SensorPerturbationEvent();
        JsonReader p = Json.createReader(new ByteArrayInputStream("{ \"time\": 11, \"name\": \"invalid\", \"bias\": 2.0, \"noiseDev\": 1, \"anchor\": 0, \"anchorProbability\": 0.5 }".getBytes()));
        e.configure(p.readObject());
        changed[1] = e;
        c.setEvents(changed);
        
        e = new SensorPerturbationEvent();
        p = Json.createReader(new ByteArrayInputStream("{ \"time\": 12, \"name\": \"invalid\", \"bias\": 2.0, \"noiseDev\": 1, \"anchor\": 0, \"anchorProbability\": 0.5 }".getBytes()));
        e.configure(p.readObject());
        c.addEvent(e);
        
        e = new SensorPerturbationEvent();
        p = Json.createReader(new ByteArrayInputStream("{ \"time\": 13, \"name\": \"also invalid\", \"bias\": 2.0, \"noiseDev\": 1, \"anchor\": 0, \"anchorProbability\": 0.5 }".getBytes()));
        e.configure(p.readObject());
        c.addEvent(e);
        
        System.out.println(c.getCurrentRegions());
        CurrentRegion region = c.getCurrentRegions().get(0);
        c.clearCurrentRegions();
        System.out.println(c.getCurrentRegions());
        c.addCurrentRegion(region);
        System.out.println(c.getCurrentRegions());
        
        System.out.println(c.getBathymetryRegions());
        BathymetryRegion bregion = new BathymetryRegion();
        bregion.setwLon(0).setsLat(0).seteLon(1).setnLat(1).setDepth(10.0);
        c.addBathymetryRegion(bregion);
        System.out.println(c.getBathymetryRegions());
        c.clearBathymetryRegions();
        System.out.println(c.getBathymetryRegions());
        
        System.out.println(c.getDetectableObjects());
        c.clearDetectableObjects();
        System.out.println(c.getDetectableObjects());
        DetectableObject dobj = new DetectableObject();
        dobj.setLat(0.34).setLon(0.12);
        c.addDetectableObject(dobj);
        System.out.println(c.getDetectableObjects());        
        
        System.out.println(c.getSensorModels());
        SensorModel m = new SensorModel();
        m.setAnchor(3.14);
        m.setAnchorProbability(.11);
        m.setBias(2.72);
        m.setName("dvl_roll");
        m.setNoiseDev(1.62);
        c.setSensorModel(m);
        m.setAnchor(12);
        m.setAnchorProbability(.34);
        m.setBias(56);
        m.setName("dvl_surge");
        m.setNoiseDev(78);
        c.setSensorModel(m);
        try {
            m.setName("bogus name");
            c.setSensorModel(m);
            throw new RuntimeException("Should have thrown error on bad sensor name");
        } catch (ConfigurationException expected) {
            // this was supposed to be thrown
        }
        System.out.println(c.getSensorModels());
        
        ObjectDetectionModel m2;
        
        try {
            m2 = c.getDetectionModel("bogus name");
            throw new RuntimeException("Should have thrown error on bad sensor name");
        } catch (ConfigurationException expected) {
            // this was supposed to be thrown
        }
        m2 = c.getDetectionModel("ObjectSensor");
        System.out.println(m2);
        RangeDependentObjectDetectionModel m3 = new RangeDependentObjectDetectionModel();
        m3.setPd0(.8);
        m3.setPd1(.2);
        m3.setRange0(10);
        m3.setRange1(150);
        c.setDetectionModel("ObjectSensor", m3);

        Region r = new Region();
        r.setwLon(12);
        r.seteLon(13);
        r.setsLat(34);
        r.setnLat(35);
        c.setSearchRegion(r);
        
        c.setSeed(23);
        c.setVehicleOrigin(23, -45, 67);
        c.setDestination(23.1, -44.9, 22);
        c.setVehicleHeading(33);
        c.setVehiclePitch(3);
        c.setVehicleSpeed(2);
        
        VehicleCommand vc = new VehicleCommand();
        vc.depthTarget = 12;
        vc.headingTarget = 34;
        vc.speedTarget = 5.6;
        c.setVehicleCommand(vc);
        
        
        
        System.out.println(c.getJsonString());
    }
}
