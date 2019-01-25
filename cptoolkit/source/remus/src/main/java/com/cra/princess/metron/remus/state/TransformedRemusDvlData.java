package com.cra.princess.metron.remus.state;

import com.cra.princess.evaluation.messages.TransformedDvlReading;
import org.apache.activemq.command.ActiveMQMapMessage;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;

public class TransformedRemusDvlData {
  private static final Logger LOG = Logger.getLogger(TransformedRemusDvlData.class.getName());

  public static final String TRANSFORMED_DVL_SENSOR_TOPIC = "princess.dvl.transformed";

  public static final String DATA_FIELD_TIMESTAMP = "timestamp";
  public static final String DATA_FIELD_DEPTH = "depth";
  public static final String DATA_FIELD_VE = "vE";
  public static final String DATA_FIELD_VN = "vN";
  public static final String DATA_FIELD_VU = "vU";
  public static final String DATA_FIELD_PITCH = "pitch";
  public static final String DATA_FIELD_ROLL = "roll";
  public static final String DATA_FIELD_HEADING = "heading";
  public static final String DATA_FIELD_SURGE = "surge";
  public static final String DATA_FIELD_SWAY = "sway";
  public static final String DATA_FIELD_HEAVE = "heave";

  public static final String DATA_FIELD_VE_CONF = "vEConf";
  public static final String DATA_FIELD_VN_CONF = "vNConf";
  public static final String DATA_FIELD_VU_CONF = "vUConf";

  public static final String DATA_FIELD_VE_STDDEV = "vEStdDev";
  public static final String DATA_FIELD_VN_STDDEV = "vNStdDev";
  public static final String DATA_FIELD_VU_STDDEV = "vUStdDev";

  public static final String DATA_FIELD_SURGE_CONF = "surgeConf";
  public static final String DATA_FIELD_SWAY_CONF = "swayConf";
  public static final String DATA_FIELD_HEAVE_CONF = "heaveConf";

  public static final String DATA_FIELD_SURGE_STDDEV = "surgeStdDev";
  public static final String DATA_FIELD_SWAY_STDDEV = "swayStdDev";
  public static final String DATA_FIELD_HEAVE_STDDEV = "heaveStdDev";

  private long timestamp;
  private double depth;
  private double vE;
  private double vN;
  private double vU;
  private double pitch;
  private double roll;
  private double heading;

  private double vEConf, vNConf, vUConf;
  private double vEStdDev, vNStdDev, vUStdDev;

  private double surge, sway, heave;
  private double surgeConf, swayConf, heaveConf;
  private double surgeStdDev, swayStdDev, heaveStdDev;

  public TransformedRemusDvlData(long timestamp, double depth, double vE, double vN, double vU, double pitch, double roll, double heading,
                                 double vEConf, double vNConf, double vUConf, double vEStdDev, double vNStdDev, double vUStdDev, double surge, double sway, double heave,
                                 double surgeConf, double swayConf, double heaveConf, double surgeStdDev, double swayStdDev, double heaveStdDev) {
    this.timestamp = timestamp;
    this.depth = depth;
    this.vE = vE;
    this.vN = vN;
    this.vU = vU;
    this.pitch = pitch;
    this.roll = roll;
    this.heading = heading;

    this.vEConf = vEConf;
    this.vNConf = vNConf;
    this.vUConf = vUConf;

    this.vEStdDev = vEStdDev;
    this.vNStdDev = vNStdDev;
    this.vUStdDev = vUStdDev;

    this.surge = surge;
    this.sway = sway;
    this.heave = heave;

    this.surgeConf = surgeConf;
    this.swayConf = swayConf;
    this.heaveConf = heaveConf;

    this.surgeStdDev = surgeStdDev;
    this.swayStdDev = swayStdDev;
    this.heaveStdDev = heaveStdDev;
  }

  public MapMessage toMapMessage() {
    MapMessage msg = new ActiveMQMapMessage();
    try {
      msg.setLong(TransformedRemusDvlData.DATA_FIELD_TIMESTAMP, timestamp);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_DEPTH, depth);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_PITCH, pitch);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_ROLL, roll);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_HEADING, heading);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VE, vE);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VN, vN);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VU, vU);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VE_CONF, vEConf);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VN_CONF, vNConf);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VU_CONF, vUConf);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VE_STDDEV, vEStdDev);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VN_STDDEV, vNStdDev);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_VU_STDDEV, vUStdDev);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_SURGE, surge);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_SWAY, sway);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_HEAVE, heave);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_SURGE_CONF, surgeConf);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_SWAY_CONF, swayConf);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_HEAVE_CONF, heaveConf);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_SURGE_STDDEV, surgeStdDev);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_SWAY_STDDEV, swayStdDev);
      msg.setDouble(TransformedRemusDvlData.DATA_FIELD_HEAVE_STDDEV, heaveStdDev);
    } catch (JMSException e) {
      LOG.error(e.getMessage());
    }
    return msg;
  }

  public long getTimestamp() {
    return timestamp;
  }

  public double getDepth() {
    return depth;
  }

  public double getvE() {
    return vE;
  }

  public double getvN() {
    return vN;
  }

  public double getvU() {
    return vU;
  }

  public double getPitch() {
    return pitch;
  }

  public double getRoll() {
    return roll;
  }

  public double getHeading() {
    return heading;
  }

  public double getSurge() { return surge; }

  public double getSway() { return sway; }

  public double getHeave() { return heave; }

  public double getVEConf() { return vEConf; }

  public double getVNConf() { return vNConf; }

  public double getVUConf() { return vUConf; }

  public double getVEStdDev() { return vEStdDev; }

  public double getVNStdDev() { return vNStdDev; }

  public double getVUStdDev() { return vUStdDev; }

  public double getSurgeConf() { return surgeConf; }

  public double getSwayConf() { return swayConf; }

  public double getHeaveConf() { return heaveConf; }

  public double getSurgeStdDev() { return surgeStdDev; }

  public double getSwayStdDev() { return swayStdDev; }

  public double getHeaveStdDev() { return heaveStdDev; }
}
