package com.cra.princess.messaging;

import com.cra.princess.messaging.JmsManager.MessageHandler;

/**
 * The simplest possible round-trip test of message send/receive.
 * @author chagnon
 *
 */
public class JmsManagerTest {
    public static void main(String[] args) {
        GroundTruthMessage state = new GroundTruthMessage();
        VehicleCommand command = new VehicleCommand();
        
        JmsManager.addTruthHandler(new MessageHandler<GroundTruthMessage>() {
            @Override
            public void handleMessage(GroundTruthMessage message) {
                System.out.println("Received a StateMessage: " + message);
            }
        });
        JmsManager.addCommandHandler(new MessageHandler<VehicleCommand>() {
            @Override
            public void handleMessage(VehicleCommand message) {
                System.out.println("Received a VehicleCommand: " + message);
            }
        });
        
        JmsManager.sendGroundTruth(state);
        JmsManager.sendVehicleCommand(command);
    }
}