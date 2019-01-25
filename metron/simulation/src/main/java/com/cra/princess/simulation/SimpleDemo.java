package com.cra.princess.simulation;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;

import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.TimeManager.TimeStepped;

public class SimpleDemo {
    static class StateLogger implements MessageHandler<GroundTruthMessage> {
        @Override
        public void handleMessage(GroundTruthMessage message) {
            System.out.println(message);
        }
    }
    @SuppressWarnings("unchecked")
    public static void main(String[] args) throws FileNotFoundException, InstantiationException, IllegalAccessException, ClassNotFoundException {
        JsonReader reader = Json.createReader(new BufferedInputStream(new FileInputStream("scenario.json")));
        
        JsonObject config = reader.readObject();
        reader.close();
        
        JsonObject vehicleConfig = config.getJsonObject("vehicle");
        System.out.println(vehicleConfig.getString("type"));
        Object vehicle = Class.forName(vehicleConfig.getString("type")).newInstance();
        // TODO: vehicle class that has all these interfaces
        ((JsonConfigurable) vehicle).configure(vehicleConfig.getJsonObject("config"));
        
        JsonObject jsonCommand = vehicleConfig.getJsonObject("command");
        if (jsonCommand != null) {
            VehicleCommand command = new VehicleCommand();
            command.depthTarget = jsonCommand.getJsonNumber("depthTarget").doubleValue();
            command.headingTarget = jsonCommand.getJsonNumber("headingTarget").doubleValue();
            command.speedTarget = jsonCommand.getJsonNumber("speedTarget").doubleValue();
            ((MessageHandler<VehicleCommand>) vehicle).handleMessage(command);
        }
        JmsManager.addCommandHandler((MessageHandler<VehicleCommand>) vehicle);
        
        TimeManager.addStepper((TimeStepped) vehicle);

        JsonObject currentConfig = config.getJsonObject("world").getJsonObject("current");
        Object current = Class.forName(currentConfig.getString("type")).newInstance();
        ((JsonConfigurable) current).configure(currentConfig.getJsonObject("config"));
        World.currentSource = (CurrentSource) current;
        
        JmsManager.addTruthHandler(new StateLogger());

        TimeManager.setTime(System.currentTimeMillis());
        
        JsonObject timeConfig = config.getJsonObject("time");
        long duration = 10000;
        long step = 100;
        if (timeConfig != null) {
            duration = (long) (timeConfig.getJsonNumber("duration").doubleValue() * 1000);
            step = (long) (timeConfig.getJsonNumber("step").doubleValue() * 1000);
            TimeManager.setSpeedup(timeConfig.getJsonNumber("acceleration").doubleValue());
        }
        TimeManager.initialize();
        TimeManager.runAndWait(duration, step);
               
        JmsManager.stop();
    }

}

