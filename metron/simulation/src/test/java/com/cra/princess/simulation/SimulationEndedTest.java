package com.cra.princess.simulation;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Date;

import javax.json.JsonException;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.SimulationControlMessage;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.events.EventDispatcher;

/**
 * Test system shutdown on unexpected (from PRINCESS) SimulationEnded message
 * 
 * @author chagnon
 *
 */
public class SimulationEndedTest {
    public static void main(String[] args) {
        // Provide visual feedback that the sim is running
        EventDispatcher.registerConsumer(GroundTruthMessage.class, new MessageHandler<GroundTruthMessage>() {
            @Override
            public void handleMessage(GroundTruthMessage gt) {         
                    System.out.println(String.format("%s %g %g %g %g %g %g %g %g %g", new Date(TimeManager.now()), gt.trueLatitude, gt.trueLongitude, gt.trueDepth,
                            gt.vE, gt.vN, gt.vU, gt.roll, gt.pitch, gt.heading));
            }
        });
        
        String scenarioName = "scenario.json"; 
        Runner runner = new Runner();
        try {
            InputStream is = new FileInputStream(new File(scenarioName));
            runner.load(is);            
            runner.run();
        } catch (FileNotFoundException e1) {
            System.err.println("File not found:\n" + e1.getLocalizedMessage());
        } catch (JsonException e1) {
            System.err.println("JSON failed to parse:\n" + e1.getLocalizedMessage());
        }        

        // Cleanly shut down JmsManager when sim is over.
        TimeManager.addStepper(new TimeStepped() {
            @Override
            public void initialize() { }
            @Override
            public void update() { }
            @Override
            public void reset() { }
            @Override
            public void stop() {
                // Leaving this here because I anticipate a redundant SimulationEnded will be sent in actual practice
                JmsManager.sendSimulationControlMessage(new SimulationControlMessage());
                JmsManager.stop();
            }
        });
        
        // Wait a little bit, then have 'PRINCESS' call off the scenario
        try {
            Thread.sleep(2000);
            JmsManager.sendSimulationControlMessage(new SimulationControlMessage());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
