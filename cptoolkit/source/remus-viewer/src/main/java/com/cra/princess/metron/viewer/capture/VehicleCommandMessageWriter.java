package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.command.RemusVehicleCommand;
import com.cra.princess.metron.remus.command.VehicleCommandListener;
import com.cra.princess.metron.viewer.controller.RemusViewerController;
import org.apache.log4j.Logger;

import java.util.Date;

/**
 * Class for writing incoming messages on a specific JMS topic to a JMS Test Harness map message data file<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Dec 18, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class VehicleCommandMessageWriter extends MessageWriter implements VehicleCommandListener {
    private static Logger LOG = Logger.getLogger(VehicleCommandMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "vehicle-command-capture";

    public VehicleCommandMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addVehicleCommandUpdateListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void vehicleCommandUpdate(RemusVehicleCommand vehicleCommand) {
        Date now = new Date();
        String timestamp = Long.toString(now.getTime());

        StringBuffer content = new StringBuffer();
        content.append(RemusVehicleCommand.DATA_FIELD_DEPTH_TARGET);
        content.append(":=");
        content.append(vehicleCommand.getDepthTarget());
        content.append(",");
        content.append(RemusVehicleCommand.DATA_FIELD_SPEED_TARGET);
        content.append(":=");
        content.append(vehicleCommand.getSpeedTarget());
        content.append(",");
        content.append(RemusVehicleCommand.DATA_FIELD_HEADING_TARGET);
        content.append(":=");
        content.append(vehicleCommand.getHeadingTarget());

        writeTopicMessage(timestamp, content.toString(), RemusVehicleCommand.VEHICLE_COMMAND_TOPIC);
    }
}
