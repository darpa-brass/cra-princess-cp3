package com.cra.princess.metron.topic;

import com.cra.princess.evaluation.messages.SerializationException;
import com.cra.princess.evaluation.messages.TransformedDvlReading;
import com.cra.princess.evaluation.messages.TransformedDvlReading$;
import com.cra.princess.metron.remus.state.TransformedDvlSensorUpdateListener;
import com.cra.princess.metron.remus.state.TransformedRemusDvlData;
import org.apache.log4j.Logger;

import javax.jms.*;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class TransformedDvlDataTopicWatcher extends JmsTopicWatcher {
  private static final Logger LOG = Logger.getLogger(TransformedDvlDataTopicWatcher.class.getName());

  private List<TransformedDvlSensorUpdateListener> transformedDvlSensorUpdateListeners;

  public void addTransformedDvlSensorUpdateListener(TransformedDvlSensorUpdateListener listener) {
    this.transformedDvlSensorUpdateListeners.add(listener);
  }

  public void removeTransformedDvlSensorUpdateListener(TransformedDvlSensorUpdateListener listener) {
    this.transformedDvlSensorUpdateListeners.remove(listener);
  }

  public TransformedDvlDataTopicWatcher(Session session) {
    super(session, TransformedRemusDvlData.TRANSFORMED_DVL_SENSOR_TOPIC);
    this.transformedDvlSensorUpdateListeners = new CopyOnWriteArrayList<>();
  }

  @Override
  protected void processMapMessage(MapMessage mapMessage) {
    try {
      LOG.debug("New Transformed DVL data update received");

      long timestamp = mapMessage.getLong(TransformedRemusDvlData.DATA_FIELD_TIMESTAMP);
      double depth = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_DEPTH);
      double pitch = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_PITCH);
      double roll = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_ROLL);
      double heading = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_HEADING);
      double vE = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VE);
      double vN = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VN);
      double vU = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VU);
      double vEConf = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VE_CONF);
      double vNConf = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VN_CONF);
      double vUConf = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VU_CONF);
      double vEStdDev = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VE_STDDEV);
      double vNStdDev = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VN_STDDEV);
      double vUStdDev = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_VU_STDDEV);
      double surge = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_SURGE);
      double sway = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_SWAY);
      double heave = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_HEAVE);
      double surgeConf = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_SURGE_CONF);
      double swayConf = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_SWAY_CONF);
      double heaveConf = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_HEAVE_CONF);
      double surgeStdDev = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_SURGE_STDDEV);
      double swayStdDev = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_SWAY_STDDEV);
      double heaveStdDev = mapMessage.getDouble(TransformedRemusDvlData.DATA_FIELD_HEAVE_STDDEV);


      TransformedRemusDvlData trdd = new TransformedRemusDvlData(timestamp, depth,
              vE, vN, vU,
              pitch, roll, heading,
              vEConf, vNConf, vUConf,
              vEStdDev, vNStdDev, vUStdDev,
              surge, sway, heave,
              surgeConf, swayConf, heaveConf,
              surgeStdDev, swayStdDev, heaveStdDev);

      LOG.debug("Sending Transformed DVL data to listeners");

      for (TransformedDvlSensorUpdateListener listener : this.transformedDvlSensorUpdateListeners) {
        listener.transformedDvlSensorUpdate(trdd);
      }
    } catch (JMSException e) {
      LOG.error(e.getMessage());
    }
  }

}
