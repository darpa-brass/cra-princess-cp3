package com.cra.princess.metron.remus.control;

public class SimulationControlMessage {
    public static final String CONTROL_TOPIC = "princess.control";

    public static final String CONTROL_COMMAND_PLAY = "PLAY";
    public static final String CONTROL_COMMAND_PAUSE = "PAUSE";
    public static final String CONTROL_COMMAND_STOP = "STOP";

    public static final String DATA_FIELD_PLAY_CONTROL = "playControl";
    public static final String DATA_FIELD_SIM_SPEED = "simSpeed";

    private String playControl = CONTROL_COMMAND_PLAY;
    private Double simSpeed = -1.0;

    public SimulationControlMessage(String playControl) {
        this.playControl = playControl;
        this.simSpeed = -1.0;
    }

    public SimulationControlMessage(Double simSpeed) {
        this.playControl = null;
        if (simSpeed <= 0.0) {
            throw new IllegalArgumentException("Simulation speed value must be greater than 0.0");
        }
        this.simSpeed = simSpeed;
    }

    public com.cra.princess.messaging.SimulationControlMessage mapTo() {
        com.cra.princess.messaging.SimulationControlMessage message = null;

        if (this.playControl == null) {
            message = com.cra.princess.messaging.SimulationControlMessage.play(this.simSpeed);
        }
        else {
            if (this.playControl.equals(CONTROL_COMMAND_PAUSE)) {
                message = com.cra.princess.messaging.SimulationControlMessage.pause();
            } else if (this.playControl.equals(CONTROL_COMMAND_STOP)) {
                message = com.cra.princess.messaging.SimulationControlMessage.stop();
            }
            else {
                message = com.cra.princess.messaging.SimulationControlMessage.play();
            }
        }

        return message;
    }

    public String getPlayControl() {
        return playControl;
    }
    public Double getSimSpeed() {
        return simSpeed;
    }
}
