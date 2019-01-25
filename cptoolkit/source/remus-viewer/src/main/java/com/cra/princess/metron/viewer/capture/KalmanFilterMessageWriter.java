package com.cra.princess.metron.viewer.capture;

import com.cra.princess.messaging.types.Location;
import com.cra.princess.metron.remus.state.KalmanFilterOutputListener;
import com.cra.princess.metron.topic.KalmanFilterOutputTopicWatcher;
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

public class KalmanFilterMessageWriter extends MessageWriter implements KalmanFilterOutputListener {
    private static Logger LOG = Logger.getLogger(KalmanFilterMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "kalman-filter-capture";

    public KalmanFilterMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addKalmanFilterOutputListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void kalmanFilterOutputUpdate(Location location) {
        Date now = new Date();
        String timestamp = Long.toString(now.getTime());

        StringBuffer content = new StringBuffer();
        content.append(location.toJson());

        writeTopicMessage(timestamp, content.toString(), KalmanFilterOutputTopicWatcher.KF_OUTPUT_TOPIC);
    }
}
