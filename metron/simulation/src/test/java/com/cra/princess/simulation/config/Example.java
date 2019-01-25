package com.cra.princess.simulation.config;

import java.io.ByteArrayInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;

import javax.json.Json;
import javax.json.JsonReader;

import com.cra.princess.messaging.DvlMessage;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.ObjectDetectionMessage;
import com.cra.princess.messaging.PowerMessage;
import com.cra.princess.simulation.Runner;
import com.cra.princess.simulation.events.SensorPerturbationEvent;
import com.cra.princess.simulation.events.TimedEvent;


// Run with working directory ${workspace_loc:simulation/src/dist/bin}
public class Example {

static class StateLogger implements MessageHandler<GroundTruthMessage> {
	static final SimpleDateFormat fmt = new SimpleDateFormat("HH:mm:ss.SSS");
    @Override
    public void handleMessage(GroundTruthMessage message) {
    	// System.out.format("wall=%s, sim=%s\n", fmt.format(new Date()), fmt.format(new Date(message.timestamp)));
        System.out.println(message);
    }
}

static class DvlLogger implements MessageHandler<DvlMessage> {
    @Override
    public void handleMessage(DvlMessage message) {
        System.out.println(message);
    }
}

static class PowerLogger implements MessageHandler<PowerMessage> {	
    @Override
    public void handleMessage(PowerMessage message) {    	
        System.out.println(message);
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
		TimedEvent[] orig = c.getEvents();
		TimedEvent[] changed = new TimedEvent[c.getEvents().length + 1];
		for (int i=0; i<orig.length; i++ )
			changed[i] = orig[i];		
		SensorPerturbationEvent e = new SensorPerturbationEvent();
		JsonReader p = Json.createReader(new ByteArrayInputStream("{ \"time\": 11, \"name\": \"dvl_roll\", \"bias\": 2.0, \"noiseDev\": 1, \"anchor\": 0, \"anchorProbability\": 0.05 }".getBytes()));
		e.configure(p.readObject());
		changed[orig.length] = e;
		c.setEvents(changed);		
		
		// Save this to a file
		String jsonString = c.getJsonString();
		FileWriter f = new FileWriter("example.json");		
		f.write(jsonString);
		f.close();

		// Run the simulator
		Runner simulator = new Runner();		
		simulator.load(c.getJsonObject());
        JmsManager.addTruthHandler(new StateLogger());
        JmsManager.addDvlHandler(new DvlLogger());
        JmsManager.addObjectDetectionHandler(new ObjectLogger());
        JmsManager.addPowerHandler(new PowerLogger());
		simulator.run();
	}
}
