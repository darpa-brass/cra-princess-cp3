package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.state.ObjectDetectionListener;
import com.cra.princess.metron.remus.state.RemusObjectDetectionState;
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

public class ObjectDetectionMessageWriter extends MessageWriter implements ObjectDetectionListener {
    private static Logger LOG = Logger.getLogger(ObjectDetectionMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "object-detection-capture";

    public ObjectDetectionMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addObjectDetectionListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void objectDetected(RemusObjectDetectionState objectDetectionMessage) {
        String timestamp = Long.toString(objectDetectionMessage.getTimestamp());

        StringBuffer content = new StringBuffer();
        content.append(RemusObjectDetectionState.DATA_FIELD_RANGE);
        content.append(":=");
        content.append(objectDetectionMessage.getRange());
        content.append(",");
        content.append(RemusObjectDetectionState.DATA_FIELD_THETA);
        content.append(":=");
        content.append(objectDetectionMessage.getTheta());
        content.append(",");
        content.append(RemusObjectDetectionState.DATA_FIELD_PHI);
        content.append(":=");
        content.append(objectDetectionMessage.getPhi());

        writeTopicMessage(timestamp, content.toString(), RemusObjectDetectionState.OBJECT_DETECTION_TOPIC);
    }
}
