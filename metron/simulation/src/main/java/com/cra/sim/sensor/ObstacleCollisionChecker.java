package com.cra.sim.sensor;

import java.util.logging.Logger;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.simulation.World;
import com.cra.princess.simulation.events.EventDispatcher;

public class ObstacleCollisionChecker  implements MessageHandler<GroundTruthMessage> {
	private static final Logger LOGGER = Logger.getLogger(ObstacleCollisionChecker.class.getName());
	
	public ObstacleCollisionChecker() {
        EventDispatcher.registerConsumer(GroundTruthMessage.class, this);        
	}

	@Override
	public void handleMessage(GroundTruthMessage message) {
		if (!World.obstacleRegionStore.isCollisionFree(message.trueLatitude, message.trueLongitude)) {
			LOGGER.warning("Collided with obstacle at " + message.timestamp);
			// TODO emit collision message on jms
		}
		
	}
	
}
