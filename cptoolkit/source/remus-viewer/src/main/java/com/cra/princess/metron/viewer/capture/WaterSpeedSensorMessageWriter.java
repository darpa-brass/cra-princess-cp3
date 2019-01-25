package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.state.RemusWaterSpeedData;
import com.cra.princess.metron.remus.state.WaterSpeedSensorUpdateListener;
import com.cra.princess.metron.viewer.controller.RemusViewerController;
import org.apache.log4j.Logger;

/**
 * Class for writing incoming messages on a specific JMS topic to a JMS Test Harness map message data file<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Dec 18, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class WaterSpeedSensorMessageWriter extends MessageWriter implements WaterSpeedSensorUpdateListener {
    private static Logger LOG = Logger.getLogger(WaterSpeedSensorMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "waterspeed-sensor-capture";

    public WaterSpeedSensorMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addWaterSpeedSensorUpdateListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void waterSpeedSensorUpdate(RemusWaterSpeedData waterSpeedDataUpdateMessage) {
        String timestamp = Long.toString(waterSpeedDataUpdateMessage.getTimestamp());

        StringBuffer content = new StringBuffer();
        content.append(RemusWaterSpeedData.DATA_FIELD_WATER_SPEED);
        content.append(":=");
        content.append(waterSpeedDataUpdateMessage.getSpeed());

        writeTopicMessage(timestamp, content.toString(), RemusWaterSpeedData.WATER_SPEED_SENSOR_TOPIC);
    }
}
