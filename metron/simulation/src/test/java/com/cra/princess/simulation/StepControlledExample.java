package com.cra.princess.simulation;

import java.io.IOException;
import java.text.SimpleDateFormat;

import com.cra.princess.messaging.DvlMessage;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.ObjectDetectionMessage;
import com.cra.princess.simulation.config.Configuration;


// Run with working directory ${workspace_loc:simulation/src/dist/bin}
public class StepControlledExample {

static class StateLogger implements MessageHandler<GroundTruthMessage> {
	static final SimpleDateFormat fmt = new SimpleDateFormat("HH:mm:ss.SSS");
    @Override
    public void handleMessage(GroundTruthMessage message) {
    	// System.out.format("wall=%s, sim=%s\n", fmt.format(new Date()), fmt.format(new Date(message.timestamp)));
        System.out.format("%d: %s\n", message.timestamp, message);
    }
}

static class DvlLogger implements MessageHandler<DvlMessage> {
    @Override
    public void handleMessage(DvlMessage message) {
    	System.out.format("%d: %s\n", message.timestamp, message);
    }
}

static class ObjectLogger implements MessageHandler<ObjectDetectionMessage> {
    @Override
    public void handleMessage(ObjectDetectionMessage message) {
        System.out.println(message);
    }
}

	public static void main(String[] args) throws IOException {
		Configuration c = new Configuration("scenario.json");
		// Run the simulator
		Runner simulator = new Runner();		
		simulator.load(c.getJsonObject());
        JmsManager.addTruthHandler(new StateLogger());
        JmsManager.addDvlHandler(new DvlLogger());
        JmsManager.addObjectDetectionHandler(new ObjectLogger());
		simulator.runStepperMode(); // This returns right away, spawning a thread to handle stepper messages
	}
}
