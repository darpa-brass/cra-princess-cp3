package com.cra.princess.simulation;


import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.BasicVehicleSim.BasicVehicleSimConfiguration;

public class BasicVehicleSimTest {

    static class StateLogger implements MessageHandler<GroundTruthMessage> {
        @Override
        public void handleMessage(GroundTruthMessage message) {
            System.out.println(message);
        }
    }
    
    public static void main(String[] args) {
        BasicVehicleSim sim = new BasicVehicleSim();
        BasicVehicleSimConfiguration config = new BasicVehicleSimConfiguration();
        config.originLat = 30;
        config.originLon = -117;
        config.originDepth = 10.0;
        sim.configure(config);
        JmsManager.addCommandHandler(sim);
        VehicleCommand cmd = new VehicleCommand();
        cmd.headingTarget = 45;
        cmd.speedTarget = 100; // pretty fast, so you can see lat/lon change
        sim.handleMessage(cmd);

        StateLogger stateLogger = new StateLogger();
        JmsManager.addTruthHandler(stateLogger);

        TimeManager.addStepper(sim);
        TimeManager.setTime(System.currentTimeMillis());
        TimeManager.initialize();

        TimeManager.runAndWait(10000, 1000);
        
        JmsManager.stop();
    }

}
