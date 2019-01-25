package com.cra.princess.metron.topic;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;

import org.apache.log4j.Logger;

import com.cra.princess.metron.remus.state.RemusVehicleState;
import com.cra.princess.metron.remus.state.VehicleGroundTruthUpdateListener;

/**
 * Class for handling ground truth data messages from the Metron REMUS simulator.
 * 
 */
public class GroundTruthTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(GroundTruthTopicWatcher.class.getName());

    private List<VehicleGroundTruthUpdateListener> vehicleGroundTruthUpdateListeners = null;
    
    public GroundTruthTopicWatcher(Session session) {
    	super(session, RemusVehicleState.TRUTH_TOPIC);

    	this.vehicleGroundTruthUpdateListeners = new CopyOnWriteArrayList<VehicleGroundTruthUpdateListener>();
    }
    
    public void addVehicleGroundTruthUpdateListener(VehicleGroundTruthUpdateListener listener) {
    	this.vehicleGroundTruthUpdateListeners.add(listener);
    }

    public void removeVehicleGroundTruthUpdateListener(VehicleGroundTruthUpdateListener listener) {
    	this.vehicleGroundTruthUpdateListeners.remove(listener);
    }    

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// Ground Truth Message

			LOG.debug("New REMUS ground truth update received");

			Long timestamp = mapMessage.getLong(RemusVehicleState.DATA_FIELD_TIMESTAMP);
			Double trueLongitude = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_TRUELON);
			Double trueLatitude = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_TRUELAT);
			Double trueDepth = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_TRUEDEPTH);
			Double vE = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_VE);
			Double vN = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_VN);
			Double vU = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_VU);
			Double pitch = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_PITCH);
			Double roll = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_ROLL);
			Double heading = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_HEADING);
			Double surge = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_SURGE);
			Double sway = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_SWAY);
			Double heave = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_HEAVE);
			Double waterCurrentN = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_CURRENT_VN);
			Double waterCurrentE = mapMessage.getDouble(RemusVehicleState.DATA_FIELD_CURRENT_VE);

			RemusVehicleState rvs = new RemusVehicleState(timestamp, trueLatitude, trueLongitude, trueDepth, vE, vN, vU, pitch, roll, heading, surge, sway, heave, waterCurrentN, waterCurrentE);

			LOG.debug("Sending ground truth update to listeners");

			for (VehicleGroundTruthUpdateListener listener : this.vehicleGroundTruthUpdateListeners) {
				listener.vehicleGroundTruthUpdate(rvs);
			}

			LOG.debug("Ground truth listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
