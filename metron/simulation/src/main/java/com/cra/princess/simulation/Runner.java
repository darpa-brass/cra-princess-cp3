package com.cra.princess.simulation;

import java.io.BufferedInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonException;
import javax.json.JsonObject;
import javax.json.JsonReader;

import com.cra.princess.messaging.DvlMessage;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.SimulationControlMessage;
import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.config.Configuration;
import com.cra.princess.simulation.events.EventDispatcher;
import com.cra.princess.simulation.events.ScriptedEvents;
import com.cra.sim.sensor.SensorManager;

public class Runner implements Runnable {
	// private static final Logger LOGGER = Logger.getLogger(Runner.class.getName());
    private long duration = 10000;
    private long step = 100;
    private JsonConfigurableFactory fac = new JsonConfigurableFactory();
    
    public void load(InputStream jsonStream) throws JsonException {
        JsonReader reader = Json.createReader(new BufferedInputStream(jsonStream));
        JsonObject config = reader.readObject();
        reader.close();
        load(config);
    }

    @SuppressWarnings("unchecked")
    public void load(JsonObject config) {
        EventDispatcher.clearConsumers();
        JmsManager.clearHandlers();
        TimeManager.reset();
        
        ///////////////////////////////////////////////////////////////////////////////////
        // Construct vehicle itself
        JsonObject vehicleConfig = config.getJsonObject("vehicle");
        MessageHandler<VehicleCommand> vehicle = (MessageHandler<VehicleCommand>) fac.construct(vehicleConfig);        
        // register to get VehicleCommands from JMS
        JmsManager.addCommandHandler(vehicle);
        
        // Power model
        JsonObject powerConfig = vehicleConfig.getJsonObject("powerModel");
        if (powerConfig != null) {
        	fac.construct(powerConfig);
        } 
        
        // sensors
        JsonArray sensorConfig = vehicleConfig.getJsonArray("sensors");
        if (sensorConfig != null) {
        	// TODO use the Json factory for this class
        	SensorManager sensors = new SensorManager();
        	sensors.configure(sensorConfig); 
        	// register to handle SensorPerturbations from JMS
        	JmsManager.addSensorPerturbationHandler(sensors);
        }
        
        ///////////////////////////////////////////////////////////////////////////////////
        // Give vehicle initial command, if supplied
//        JsonObject jsonCommand = vehicleConfig.getJsonObject("config");
//        if (jsonCommand != null) {
//        	jsonCommand = jsonCommand.getJsonObject("command");
//        	if (jsonCommand != null) {
//        		VehicleCommand command = new VehicleCommand();
//        		command.depthTarget = jsonCommand.getJsonNumber("depthTarget").doubleValue();
//        		command.headingTarget = jsonCommand.getJsonNumber("headingTarget").doubleValue();
//        		command.speedTarget = jsonCommand.getJsonNumber("speedTarget").doubleValue();
//        		vehicle.handleMessage(command);
//        	}
//        }
        
        ///////////////////////////////////////////////////////////////////////////////////
        // Set up scripted events
        JsonArray jsonEvent = config.getJsonArray("events");
        if (jsonEvent != null) {
        	@SuppressWarnings("unused") // Note this is added to the TimeManager's stepper list
			ScriptedEvents events = new ScriptedEvents(jsonEvent);         	
        }
        

        ///////////////////////////////////////////////////////////////////////////////////
        // Set up the world regions
        JsonObject currentConfig = config.getJsonObject("world").getJsonObject("current");        
        World.currentSource = (CurrentSource) fac.construct(currentConfig);        
        JsonObject bathymetryConfig = config.getJsonObject("world").getJsonObject("bathymetry");
        World.bathymetrySource = (BathymetrySource) fac.construct(bathymetryConfig);
        // The fact that this is happening is an argument for a better World class...
        JsonObject objectConfig = config.getJsonObject("world").getJsonObject("object");
        if (objectConfig != null) {
            World.bottomObjectStore = (BottomObjectStore) fac.construct(objectConfig);
        }
        JsonObject originConfig = config.getJsonObject("vehicle").getJsonObject("config").getJsonObject("origin");
        World.bottomObjectStore.setOrigin(originConfig);
        

        ///////////////////////////////////////////////////////////////////////////////////
        // Set up the initial time, duration, step and speed        
        JsonObject timeConfig = config.getJsonObject("time");
        if (timeConfig != null) {
            duration = (long) (timeConfig.getJsonNumber("duration").doubleValue() * 1000);
            step = (long) (timeConfig.getJsonNumber("step").doubleValue() * 1000);
            TimeManager.setSpeedup(timeConfig.getJsonNumber("acceleration").doubleValue());
            if (timeConfig.containsKey("startTime"))
            	TimeManager.setTime((long) timeConfig.getJsonNumber("startTime").doubleValue()*1000);
            else
            	TimeManager.setTime(System.currentTimeMillis());
            // System.out.format("Got dur=%d, step=%d, speed=%g\n", duration, step, TimeManager.getSpeedup());
        }
        JmsManager.addControlHandler(new MessageHandler<SimulationControlMessage>() {
            @Override
            public void handleMessage(SimulationControlMessage message) {
            	if (message.simSpeed > 0) {
            		TimeManager.setSpeedup(message.simSpeed);            		
            	}
            	switch (message.playControl) {
            	case PLAY :            		
            		TimeManager.resume();
            		break;
            	case PAUSE :            		
            		TimeManager.pause();
            		break;
            	case STOP :            		
            		TimeManager.stop();
            	}                
            }
        });
        TimeManager.initialize();
    }
    
    public void runStepperMode() {    	
    	TimeManager.runStepControlled();
    }
    
    public void run() {
        TimeManager.run(duration, step);
    }

    public void addTimeStepped(TimeStepped stepped) {
        TimeManager.addStepper(stepped);
    }

    public static void main(String[] args) {

    	String jsonFilename = "scenario.json";
    	if (args.length > 0)    		
    		jsonFilename = args[0];
    	Configuration c;
    	try {
    		c = new Configuration(jsonFilename);		
    		Runner simulator = new Runner();		
    		simulator.load(c.getJsonObject());
    		JmsManager.addTruthHandler(new MessageHandler<GroundTruthMessage>() {             
    			@Override
    			public void handleMessage(GroundTruthMessage message) {
    				System.out.println(message);
    			}} );
    		JmsManager.addDvlHandler(new MessageHandler<DvlMessage>() {
    			@Override
    			public void handleMessage(DvlMessage message) {
    				System.out.println(message);
    			}        	
    		});
    		simulator.run();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
    }
}
