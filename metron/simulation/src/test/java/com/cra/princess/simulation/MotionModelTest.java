package com.cra.princess.simulation;


import java.io.FileWriter;
import java.io.IOException;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.config.Configuration;
import com.cra.princess.simulation.events.VehicleCommandEvent;

public class MotionModelTest {

	static class StateLogger implements MessageHandler<GroundTruthMessage> {
		int count = 0;
		int decim = 10;
		@Override
		public void handleMessage(GroundTruthMessage message) {
			count++;
			if (count % decim == 0)
				System.out.println(message);
		}
	}

	public static void main(String[] args) {
		Configuration c;
		try {
			c = new Configuration("scenario.json");
			c.setVehicleSpeed(2.3);
			c.setVehicleHeading(0);
			VehicleCommand ic = new VehicleCommand();
			ic.depthTarget = c.getVehicleOrigin().getDepth();
			ic.headingTarget = 0;
			ic.speedTarget = c.getVehicleSpeed();
			c.setVehicleCommand(ic);
			VehicleCommandEvent command = new VehicleCommandEvent();
			command.setEventTime(10 * 1000);
			command.command = new VehicleCommand();
			command.command.depthTarget = c.getVehicleOrigin().getDepth();
			command.command.speedTarget = c.getVehicleSpeed();
			command.command.headingTarget = 180.0;
			c.addEvent(command);
			command = new VehicleCommandEvent();
			command.setEventTime(20 * 1000);
			command.command = new VehicleCommand();
			command.command.depthTarget = c.getVehicleOrigin().getDepth();
			command.command.speedTarget = c.getVehicleSpeed();
			command.command.headingTarget = 360.0;
			c.addEvent(command);
			
			// Save this to a file
			String jsonString = c.getJsonString();
			FileWriter f = new FileWriter("example.json");		
			f.write(jsonString);
			f.close();
			
			// Run the simulator
			Runner simulator = new Runner();		
			simulator.load(c.getJsonObject());
			JmsManager.addTruthHandler(new StateLogger());        
			simulator.run();
		} catch (IOException e) {	
			e.printStackTrace();
		}
	}

}
