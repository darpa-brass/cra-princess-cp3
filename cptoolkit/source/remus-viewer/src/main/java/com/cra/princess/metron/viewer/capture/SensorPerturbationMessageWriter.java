package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.command.RemusVehicleCommand;
import com.cra.princess.metron.remus.perturbation.RemusSensorPerturbation;
import com.cra.princess.metron.remus.perturbation.SensorPerturbationListener;
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

public class SensorPerturbationMessageWriter extends MessageWriter implements SensorPerturbationListener {
    private static Logger LOG = Logger.getLogger(SensorPerturbationMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "sensor-perturbations-capture";

    public SensorPerturbationMessageWriter(RemusViewerController controller) {
        super(controller);

        // this.controller.addSensorPerturbationListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void sensorPerturbationUpdate(RemusSensorPerturbation perturbation) {
        Date now = new Date();
        String timestamp = Long.toString(now.getTime());

        StringBuffer content = new StringBuffer();
        content.append(RemusSensorPerturbation.DATA_FIELD_NAME);
        content.append(":=");
        content.append(perturbation.getName());
        content.append(",");
        content.append(RemusSensorPerturbation.DATA_FIELD_BIAS);
        content.append(":=");
        content.append(perturbation.getBias());
        content.append(",");
        content.append(RemusSensorPerturbation.DATA_FIELD_NOISE_DEV);
        content.append(":=");
        content.append(perturbation.getNoiseDeviation());
        content.append(",");
        content.append(RemusSensorPerturbation.DATA_FIELD_ANCHOR);
        content.append(":=");
        content.append(perturbation.getAnchor());
        content.append(",");
        content.append(RemusSensorPerturbation.DATA_FIELD_ANCHOR_PROB);
        content.append(":=");
        content.append(perturbation.getAnchorProbability());

        writeTopicMessage(timestamp, content.toString(), RemusSensorPerturbation.SENSOR_PERTURBATION_TOPIC);
    }
}
