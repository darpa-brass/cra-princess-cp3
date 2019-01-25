package com.cra.princess.simulation;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;

import com.cra.princess.messaging.DvlMessage;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.events.EventDispatcher;
import com.metsci.dynamic.simple.MotionModel;
import com.metsci.numerics.ode.TimestepException;

public class SensorTest {
    public static void main(String[] args) throws TimestepException, IOException {
        JsonReader reader = Json.createReader(new BufferedInputStream(new FileInputStream(new File("scenario.json"))));        
        JsonObject json = reader.readObject();
        reader.close();
        
        MotionModel mm = new MotionModel();
        mm.configure(json);
        VehicleCommand cmd = new VehicleCommand();
        cmd.depthTarget = 5.0;
        cmd.headingTarget = Math.PI*0.5;
        cmd.speedTarget = 3.0;              
        mm.handleMessage(cmd);
        
        JsonObject config = json.getJsonObject("vehicle").getJsonObject("sensor");
        // The sensor will register itself with TimeManager and EventDispatcher; no need to keep a reference here
        new JsonConfigurableFactory().construct(config);
        
        final FileWriter gtf = new FileWriter("sensorTestGt.dat");
        final FileWriter mf = new FileWriter("sensorTestMeas.dat");
        
        EventDispatcher.registerConsumer(GroundTruthMessage.class, new MessageHandler<GroundTruthMessage>() {
            @Override
            public void handleMessage(GroundTruthMessage gt) {         
                try {
                    gtf.write(String.format("%d %g %g %g %g %g %g\n", TimeManager.now(), 
                            gt.vE, gt.vN, gt.vU, gt.roll, gt.pitch, gt.heading));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        
        EventDispatcher.registerConsumer(DvlMessage.class, new MessageHandler<DvlMessage>() {
            @Override
            public void handleMessage(DvlMessage meas) {
                System.out.println(meas);
                try {
                    mf.write(String.format("%d %g %g %g %g %g %g\n", TimeManager.now(), 
                            meas.vE, meas.vN, meas.vU, meas.roll, meas.pitch, meas.heading));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        
        TimeManager.setSpeedup(1000);
        TimeManager.setTime(System.currentTimeMillis());
        TimeManager.initialize();
        TimeManager.runAndWait(1000000, 100);
        TimeManager.stop();
        JmsManager.stop();

        gtf.close();
        mf.close();
        
    }
}
