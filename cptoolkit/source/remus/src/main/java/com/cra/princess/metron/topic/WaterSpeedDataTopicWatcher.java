package com.cra.princess.metron.topic;

import com.cra.princess.metron.remus.state.RemusWaterSpeedData;
import com.cra.princess.metron.remus.state.WaterSpeedSensorUpdateListener;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Class for handling water speed data messages from the Metron REMUS simulator.
 * 
 */
public class WaterSpeedDataTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(WaterSpeedDataTopicWatcher.class.getName());

	private List<WaterSpeedSensorUpdateListener> waterSpeedSensorUpdateListeners = null;

    public WaterSpeedDataTopicWatcher(Session session) {
    	super(session, RemusWaterSpeedData.WATER_SPEED_SENSOR_TOPIC);

    	this.waterSpeedSensorUpdateListeners = new CopyOnWriteArrayList<WaterSpeedSensorUpdateListener>();
    }
    
    public void addWaterSpeedSensorUpdateListener(WaterSpeedSensorUpdateListener listener) {
    	this.waterSpeedSensorUpdateListeners.add(listener);
    }

    public void removeWaterSpeedSensorUpdateListener(WaterSpeedSensorUpdateListener listener) {
    	this.waterSpeedSensorUpdateListeners.remove(listener);
    }     

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// Water Speed Sensor Data Message

			LOG.debug("New REMUS Water Speed data update received");

			Long timestamp = mapMessage.getLong(RemusWaterSpeedData.DATA_FIELD_TIMESTAMP);
			Double speed = mapMessage.getDouble(RemusWaterSpeedData.DATA_FIELD_WATER_SPEED);

			RemusWaterSpeedData rwsd = new RemusWaterSpeedData(timestamp, speed);

			LOG.debug("Sending Water Speed data to listeners");

			for (WaterSpeedSensorUpdateListener listener : this.waterSpeedSensorUpdateListeners) {
				listener.waterSpeedSensorUpdate(rwsd);
			}

			LOG.debug("Water Speed listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
