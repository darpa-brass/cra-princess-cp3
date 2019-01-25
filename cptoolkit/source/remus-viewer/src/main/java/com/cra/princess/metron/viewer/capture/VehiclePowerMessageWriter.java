package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.state.RemusPowerState;
import com.cra.princess.metron.remus.state.VehiclePowerUpdateListener;
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

public class VehiclePowerMessageWriter extends MessageWriter implements VehiclePowerUpdateListener {
    private static Logger LOG = Logger.getLogger(VehiclePowerMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "vehicle-power-capture";

    public VehiclePowerMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addPowerListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void vehiclePowerUpdate(RemusPowerState vehiclePowerUpdateMessage) {
        String timestamp = Long.toString(vehiclePowerUpdateMessage.getTimestamp());

        StringBuffer content = new StringBuffer();
        content.append(RemusPowerState.DATA_FIELD_POWER);
        content.append(":=");
        content.append(vehiclePowerUpdateMessage.getPower());

        writeTopicMessage(timestamp, content.toString(), RemusPowerState.POWER_TOPIC);
    }
}
