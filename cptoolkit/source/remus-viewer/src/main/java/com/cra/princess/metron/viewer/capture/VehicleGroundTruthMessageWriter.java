package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.state.RemusVehicleState;
import com.cra.princess.metron.remus.state.VehicleGroundTruthUpdateListener;
import com.cra.princess.metron.viewer.controller.RemusViewerController;
import org.apache.log4j.Logger;

/**
 * Class for writing incoming messages on a specific JMS topic to a JMS Test Harness map message data file<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Dec 17, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class VehicleGroundTruthMessageWriter extends MessageWriter implements VehicleGroundTruthUpdateListener {
    private static Logger LOG = Logger.getLogger(VehicleGroundTruthMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "ground-truth-capture";

    public VehicleGroundTruthMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addVehicleGroundTruthUpdateListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void vehicleGroundTruthUpdate(RemusVehicleState vehicleStateUpdateMessage) {
        String timestamp = Long.toString(vehicleStateUpdateMessage.getTimestamp());

        StringBuffer content = new StringBuffer();
        content.append(RemusVehicleState.DATA_FIELD_TRUELAT);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getTrueLatitude());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_TRUELON);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getTrueLongitude());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_TRUEDEPTH);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getTrueDepth());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_VE);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getvE());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_VN);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getvN());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_VU);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getvU());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_PITCH);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getPitch());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_ROLL);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getRoll());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_HEADING);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getHeading());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_SURGE);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getSurge());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_SWAY);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getSway());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_HEAVE);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getHeave());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_CURRENT_VE);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getWaterCurrentE());
        content.append(",");
        content.append(RemusVehicleState.DATA_FIELD_CURRENT_VN);
        content.append(":=");
        content.append(vehicleStateUpdateMessage.getWaterCurrentN());

        writeTopicMessage(timestamp, content.toString(), RemusVehicleState.TRUTH_TOPIC);
    }
}
