package com.cra.princess.metron.topic;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;

import org.apache.log4j.Logger;

import com.cra.princess.metron.remus.control.SimulationControlListener;
import com.cra.princess.metron.remus.control.SimulationControlMessage;

/**
 * Class for handling simulation control messages from the Metron REMUS simulator.
 * 
 */
public class SimulationControlTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(SimulationControlTopicWatcher.class.getName());

	private List<SimulationControlListener> simulationControlListeners = null;
    
    public SimulationControlTopicWatcher(Session session) {
    	super(session, SimulationControlMessage.CONTROL_TOPIC);

    	this.simulationControlListeners = new CopyOnWriteArrayList<SimulationControlListener>();
    }
    
    public void addSimulationControlListener(SimulationControlListener listener) {
    	this.simulationControlListeners.add(listener);
    }

    public void removeSimulationControlListener(SimulationControlListener listener) {
    	this.simulationControlListeners.remove(listener);
    }     

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// Simulation Control Message

			LOG.debug("New REMUS simulation control message received");

			// We should only get STOP messages (when the simulator finishes playing a scenario)
			String controlMessage = mapMessage.getString(SimulationControlMessage.DATA_FIELD_PLAY_CONTROL);

			SimulationControlMessage scm = new SimulationControlMessage(controlMessage);

			LOG.debug("Sending " + controlMessage + " control message to listeners");

			for (SimulationControlListener listener : this.simulationControlListeners) {
				listener.controlUpdate(scm);
			}

			LOG.debug("Control listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
