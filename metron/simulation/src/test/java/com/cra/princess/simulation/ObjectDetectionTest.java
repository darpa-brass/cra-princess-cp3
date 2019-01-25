package com.cra.princess.simulation;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.cra.princess.messaging.DvlMessage;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.ObjectDetectionMessage;
import com.cra.princess.simulation.config.BathymetryRegion;
import com.cra.princess.simulation.config.Configuration;


// Run with working directory ${workspace_loc:simulation/src/dist/bin}
public class ObjectDetectionTest {

	static class StateLogger implements MessageHandler<GroundTruthMessage> {
		static SimpleDateFormat fmt = new SimpleDateFormat("HH:mm:ss");
		@Override
		public void handleMessage(GroundTruthMessage message) {
			Date date = new Date();
			System.out.format("%s: %s\n", fmt.format(date), message);
		}
	}

	static class DvlLogger implements MessageHandler<DvlMessage> {
		@Override
		public void handleMessage(DvlMessage message) {
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
		c.setDefaultDepth(150.0);
		BathymetryRegion region = new BathymetryRegion();
		region.setDepth(100.0);		
		region.setwLon(-116.9996);
		region.setsLat(29.999);
		region.seteLon(-116.9994);
		region.setnLat(30.001);
		c.addBathymetryRegion(region);
		
		// Run the simulator
		Runner simulator = new Runner();		
		simulator.load(c.getJsonObject());
		JmsManager.addTruthHandler(new StateLogger());
		JmsManager.addDvlHandler(new DvlLogger());
		JmsManager.addObjectDetectionHandler(new ObjectLogger());
		simulator.run();
	}
}
