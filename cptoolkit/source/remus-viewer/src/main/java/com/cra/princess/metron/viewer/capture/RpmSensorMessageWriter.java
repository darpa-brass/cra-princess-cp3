package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.state.RemusRpmData;
import com.cra.princess.metron.remus.state.RpmSensorUpdateListener;
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

public class RpmSensorMessageWriter extends MessageWriter implements RpmSensorUpdateListener {
    private static Logger LOG = Logger.getLogger(RpmSensorMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "rpm-sensor-capture";

    public RpmSensorMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addRpmSensorUpdateListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void rpmSensorUpdate(RemusRpmData rpmDataUpdateMessage) {
        String timestamp = Long.toString(rpmDataUpdateMessage.getTimestamp());

        StringBuffer content = new StringBuffer();
        content.append(RemusRpmData.DATA_FIELD_RPM);
        content.append(":=");
        content.append(rpmDataUpdateMessage.getRpm());

        writeTopicMessage(timestamp, content.toString(), RemusRpmData.RPM_TOPIC);
    }
}
