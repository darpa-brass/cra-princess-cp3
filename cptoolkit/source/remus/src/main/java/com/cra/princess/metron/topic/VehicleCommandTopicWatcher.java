package com.cra.princess.metron.topic;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;

import org.apache.log4j.Logger;

import com.cra.princess.metron.remus.command.RemusVehicleCommand;
import com.cra.princess.metron.remus.command.VehicleCommandListener;

/**
 * Class for capturing Vehicle Command data messages sent to the Metron REMUS simulator.
 * 
 */
public class VehicleCommandTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(VehicleCommandTopicWatcher.class.getName());

	private List<VehicleCommandListener> vehicleCommandListeners = null;
    
    public VehicleCommandTopicWatcher(Session session) {
    	super(session, RemusVehicleCommand.VEHICLE_COMMAND_TOPIC);

    	this.vehicleCommandListeners = new CopyOnWriteArrayList<VehicleCommandListener>();
    }
    
    public void addVehicleCommandListener(VehicleCommandListener listener) {
    	this.vehicleCommandListeners.add(listener);
    }

    public void removeVehicleCommandListener(VehicleCommandListener listener) {
    	this.vehicleCommandListeners.remove(listener);
    }     

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// Vehicle Command Message

			LOG.debug("New Vehicle Command received");
			
			Double depth = mapMessage.getDouble(RemusVehicleCommand.DATA_FIELD_DEPTH_TARGET);
			Double speed = mapMessage.getDouble(RemusVehicleCommand.DATA_FIELD_SPEED_TARGET);
			Double heading = mapMessage.getDouble(RemusVehicleCommand.DATA_FIELD_HEADING_TARGET);

			RemusVehicleCommand rvc = new RemusVehicleCommand(heading, depth, speed);

			LOG.debug("Sending Vehicle Command data to listeners");

			for (VehicleCommandListener listener : this.vehicleCommandListeners) {
				listener.vehicleCommandUpdate(rvc);
			}

			LOG.debug("Vehicle Command listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
