package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.remus.perturbation.BatteryPerturbationListener;
import com.cra.princess.messaging.RemusBatteryPerturbation;
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

public class BatteryPerturbationMessageWriter extends MessageWriter implements BatteryPerturbationListener {
    private static Logger LOG = Logger.getLogger(BatteryPerturbationMessageWriter.class.getName());

    public static final String CAPTURE_FILENAME = "battery-perturbations-capture";

    public BatteryPerturbationMessageWriter(RemusViewerController controller) {
        super(controller);

        this.controller.addBatteryPerturbationListener(this);
        setCaptureFile(CAPTURE_FILENAME);
    }

    @Override
    public void batteryPerturbationUpdate(RemusBatteryPerturbation perturbation) {
        Date now = new Date();
        String timestamp = Long.toString(now.getTime());

        StringBuffer content = new StringBuffer();
        content.append("energyReduction");
        content.append(":=");
        content.append(perturbation.getEnergyReduction());
        content.append(",");
        content.append("sensorPower");
        content.append(":=");
        content.append(perturbation.getSensorPower());
        content.append(",");
        content.append("timepoint");
        content.append(":=");
        content.append(timestamp);

        writeTopicMessage(timestamp, content.toString(), RemusBatteryPerturbation.BATTERY_PERTURBATION_TOPIC);
    }
}
