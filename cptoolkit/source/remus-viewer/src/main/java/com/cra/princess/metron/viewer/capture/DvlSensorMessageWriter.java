package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.state.DvlSensorUpdateListener;
import com.cra.princess.metron.remus.state.RemusDvlData;
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

public class DvlSensorMessageWriter extends MessageWriter implements DvlSensorUpdateListener {
    private static Logger LOG = Logger.getLogger(DvlSensorMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "dvl-sensor-capture";

    public DvlSensorMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addDvlSensorUpdateListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void dvlSensorUpdate(RemusDvlData dvlDataUpdateMessage) {
        String timestamp = Long.toString(dvlDataUpdateMessage.getTimestamp());

        StringBuffer content = new StringBuffer();
        content.append(RemusDvlData.DATA_FIELD_DEPTH);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getDepth());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_VE);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getvE());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_VN);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getvN());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_VU);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getvU());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_PITCH);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getPitch());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_ROLL);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getRoll());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_HEADING);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getHeading());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_SURGE);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getSurge());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_SWAY);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getSway());
        content.append(",");
        content.append(RemusDvlData.DATA_FIELD_HEAVE);
        content.append(":=");
        content.append(dvlDataUpdateMessage.getHeave());

        writeTopicMessage(timestamp, content.toString(), RemusDvlData.DVL_SENSOR_TOPIC);
    }
}
