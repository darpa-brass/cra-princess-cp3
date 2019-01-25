package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.control.SimulationControlListener;
import com.cra.princess.metron.remus.control.SimulationControlMessage;
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

public class SimulationControlMessageWriter extends MessageWriter implements SimulationControlListener {
    private static Logger LOG = Logger.getLogger(SimulationControlMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "simulation-control-capture";

    public SimulationControlMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addControlListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void controlUpdate(SimulationControlMessage controlMessage) {
        Date now = new Date();
        String timestamp = Long.toString(now.getTime());

        StringBuffer content = new StringBuffer();
        if (controlMessage.getPlayControl() != null) {
            content.append("detail:=N/A");
            content.append(",");
            content.append(SimulationControlMessage.DATA_FIELD_PLAY_CONTROL);
            content.append(":=");
            content.append(controlMessage.getPlayControl());
            content.append(",");
            content.append(SimulationControlMessage.DATA_FIELD_SIM_SPEED);
            content.append(":=");
            content.append(controlMessage.getSimSpeed());
        }
        else {
            content.append("detail:=N/A");
            content.append(",");
            content.append(SimulationControlMessage.DATA_FIELD_PLAY_CONTROL);
            content.append(":=");
            content.append(SimulationControlMessage.CONTROL_COMMAND_PLAY);
            content.append(",");
            content.append(SimulationControlMessage.DATA_FIELD_SIM_SPEED);
            content.append(":=");
            content.append(controlMessage.getSimSpeed());
        }

        writeTopicMessage(timestamp, content.toString(), SimulationControlMessage.CONTROL_TOPIC);
    }
}
