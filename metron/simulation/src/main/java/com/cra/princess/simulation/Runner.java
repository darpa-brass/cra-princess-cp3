package com.cra.princess.simulation;

import java.io.BufferedInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.logging.Logger;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonException;
import javax.json.JsonObject;
import javax.json.JsonReader;

import com.cra.princess.messaging.DvlMessage;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.RemusBatteryPerturbation;
import com.cra.princess.messaging.SimulationControlMessage;
import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.config.Configuration;
import com.cra.princess.simulation.events.EventDispatcher;
import com.cra.princess.simulation.events.PowerPerturbationEvent;
import com.cra.princess.simulation.events.ScriptedEvents;
import com.cra.sim.sensor.ObstacleCollisionChecker;
import com.cra.sim.sensor.SensorManager;

public class Runner implements Runnable {
	private static final Logger LOGGER = Logger.getLogger(Runner.class.getName());
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
        // Set up scripted events
        JsonArray jsonEvent = config.getJsonArray("events");
        // Note this handles jsonEvent == null
        final ScriptedEvents eventDispatcher = new ScriptedEvents(jsonEvent);        
        
        ///////////////////////////////////////////////////////////////////////////////////
        // Construct vehicle itself
        JsonObject vehicleConfig = config.getJsonObject("vehicle");
        MessageHandler<VehicleCommand> vehicle = (MessageHandler<VehicleCommand>) fac.construct(vehicleConfig, "vehicle");        
        // register to get VehicleCommands from JMS
        JmsManager.addCommandHandler(vehicle);
        
        // Power model
        JsonObject powerConfig = vehicleConfig.getJsonObject("powerModel");        
        fac.construct(powerConfig, "power model");            	
        MessageHandler<RemusBatteryPerturbation> enqueuePowerPerturb = new MessageHandler<RemusBatteryPerturbation>() {
        	@Override
        	public void handleMessage(RemusBatteryPerturbation message) {
        		eventDispatcher.add(new PowerPerturbationEvent(message));
        	}        		
        };
        JmsManager.addRemusBatteryPerturbationHandler(enqueuePowerPerturb);     
        
        // sensors
        JsonObject sensorConfig = vehicleConfig.getJsonObject("sensorModel");
        SensorManager sensors = (SensorManager) fac.construct(sensorConfig, "sensorModel"); 
        // register to handle SensorPerturbations from JMS
        JmsManager.addSensorPerturbationHandler(sensors);        
        
        // Obstacle collision checking (self-registering)        
        @SuppressWarnings("unused")
		ObstacleCollisionChecker obstacleCollisionChecker = new ObstacleCollisionChecker();

        ///////////////////////////////////////////////////////////////////////////////////
        // Set up the world regions
        try {
        JsonObject currentConfig = config.getJsonObject("world").getJsonObject("current");        
        World.currentSource = (CurrentSource) fac.construct(currentConfig, "current");    
        } catch (ConfigurationException e) {
        	LOGGER.info("Missing water current configuration. No water currents will be used");
        }
        try {
        	JsonObject bathymetryConfig = config.getJsonObject("world").getJsonObject("bathymetry");        
        	World.bathymetrySource = (BathymetrySource) fac.construct(bathymetryConfig, "bathymetry");
        } catch (ConfigurationException e) {
        	LOGGER.info("Missing bathymetry information. No bathymetry will be used");
        }
        // The fact that this is happening is an argument for a better World class...
        try {
        	JsonObject objectConfig = config.getJsonObject("world").getJsonObject("object");        
        	World.bottomObjectStore = (BottomObjectStore) fac.construct(objectConfig, "detectable objects");
        } catch (ConfigurationException e) {
        	LOGGER.info("Missing bottom object information");
        }
        try {
        	JsonObject obstacleConfig = config.getJsonObject("world").getJsonObject("obstacles");        
        	World.obstacleRegionStore = (ObstacleRegionStore) fac.construct(obstacleConfig, "obstacles");
        } catch (ConfigurationException e) {
        	LOGGER.info("Missing obstacle information.");
        }
        /* Not worth it...
        	JsonObject originConfig = config.getJsonObject("vehicle").getJsonObject("config").getJsonObject("origin");
        	World.bottomObjectStore.setOrigin(originConfig);
        */

        ///////////////////////////////////////////////////////////////////////////////////
        // Set up the initial time, duration, step and speed
        try {
        	JsonObject timeConfig = config.getJsonObject("time");
        	if (timeConfig == null) {
        		throw new ConfigurationException("no time config data");
        	}
        	duration = (long) (JsonConfigurableFactory.getDouble(timeConfig, "duration")* 1000);
            step = (long) (JsonConfigurableFactory.getDouble(timeConfig, "step", 0.2) * 1000);
            TimeManager.setSpeedup(JsonConfigurableFactory.getDouble(timeConfig, "acceleration", 1.0));            
            TimeManager.setTime((long) JsonConfigurableFactory.getDouble(timeConfig, "startTime", 0)*1000);             
        } catch (ConfigurationException e) {
        	LOGGER.warning("Missing or malformed time configuration: " + e.getLocalizedMessage() + "... Using defaults.");
        	duration = 10 * 1000;
        	step = 200;
        	TimeManager.setSpeedup(1.0);
        	TimeManager.setTime(0L);
        }
        LOGGER.info(String.format("Scenario start=%d, duration=%d, step=%d, speedup=%g\n", TimeManager.now(), duration, step, TimeManager.getSpeedup()));
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
    	TimeManager.runStepControlled(duration);
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
