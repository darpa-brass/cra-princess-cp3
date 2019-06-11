package com.cra.princess.messaging;

import java.util.ArrayList;
import java.util.List;

import javax.jms.Connection;
import javax.jms.Destination;
import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Message;
import javax.jms.MessageConsumer;
import javax.jms.MessageListener;
import javax.jms.MessageProducer;
import javax.jms.Session;

import org.apache.activemq.ActiveMQConnectionFactory;

/**
 * Static class for managing JMS connection.
 * 
 * This initial implementation has hard-coded JMS URL and topic names in the form of constant Strings.
 * 
 * The design looks a little verbose, with repeated member variables and functions for each message type. I feel that
 * this is justified, since I don't anticipate a lot of different message types, and Java's lack of concrete specialized
 * classes makes things kind of hacky otherwise. If a lot of message types come into play, I'd suggest a code-generating
 * program to generate the boilerplate for each (basically doing part of a C++ preprocessor's job).
 * 
 * @author chagnon
 *
 */
public class JmsManager {
    public static final String JMS_URL = "tcp://localhost:61616";
    private static Connection connection;
    private static Session session;

    public static final String CONTROL_TOPIC = "princess.control";
    private static Destination controlTopic; 
    private static JmsListener<SimulationControlMessage> controlListener;
    private static MessageProducer controlProducer;
    
    public static final String STEPPING_TOPIC = "princess.timestep";
    private static Destination steppingTopic;
    private static JmsListener<StepMessage> stepListener;
    private static MessageProducer stepProducer;
    
    public static final String SENSOR_PERTURBATION_TOPIC = "princess.sensor.perturbation";
    private static Destination sensorPerturbationTopic;
    private static JmsListener<SensorPerturbation> sensorPerturbationListener;
    private static MessageProducer sensorPerturbationProducer;
    
    public static final String STATE_TOPIC = "princess.truth";
    private static Destination truthTopic;
    private static JmsListener<GroundTruthMessage> truthListener;
    private static MessageProducer truthProducer;

    public static final String DVL_TOPIC = "princess.dvl";
    private static Destination dvlTopic;
    private static JmsListener<DvlMessage> dvlListener;
    private static MessageProducer dvlProducer;
    
    public static final String POWER_TOPIC = "princess.power";
    private static Destination powerTopic;
    private static JmsListener<PowerMessage> powerListener;
    private static MessageProducer powerProducer;
    
    public static final String WATER_SPEED_TOPIC = "princess.waterspeed";
    private static Destination waterSpeedTopic;
    private static JmsListener<WaterSpeedMessage> waterSpeedListener;
    private static MessageProducer waterSpeedProducer;

    public static final String RPM_TOPIC = "princess.rpm";
    private static Destination rpmTopic;
    private static JmsListener<RpmMessage> rpmListener;
    private static MessageProducer rpmProducer;
    
    public static final String OBJECT_DETECTION_TOPIC = "princess.objectdetection";
    private static Destination objectDetectionTopic;
    private static JmsListener<ObjectDetectionMessage> objectDetectionListener;
    private static MessageProducer objectDetectionProducer;
    
    public static final String POWER_PERTURBATION_TOPIC = "princess.battery.perturbation";
    private static Destination powerPerturbationTopic;
    private static JmsListener<RemusBatteryPerturbation> powerPerturbationListener;
    private static MessageProducer powerPerturbationProducer;
    
    public static final String COMMAND_TOPIC = "princess.vehicle.command";
    private static Destination commandTopic;
    private static JmsListener<VehicleCommand> commandListener;
    private static MessageProducer commandProducer;

    private JmsManager() {
    }

    static { 
        ActiveMQConnectionFactory fac = new ActiveMQConnectionFactory(JMS_URL);
        try {
            connection = fac.createConnection();
            connection.start();
            session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);

            controlTopic = session.createTopic(CONTROL_TOPIC);
            MessageConsumer consumer = session.createConsumer(controlTopic, null, false);
            controlListener = new JmsListener<>(consumer, SimulationControlMessage.class);
            controlProducer = session.createProducer(controlTopic);
            
            steppingTopic = session.createTopic(STEPPING_TOPIC);
            consumer = session.createConsumer(steppingTopic, null, false);
            stepListener = new JmsListener<>(consumer, StepMessage.class);
            stepProducer = session.createProducer(steppingTopic);
            		            
            truthTopic = session.createTopic(STATE_TOPIC);
            consumer = session.createConsumer(truthTopic, null, false);
            truthListener = new JmsListener<>(consumer, GroundTruthMessage.class);
            truthProducer = session.createProducer(truthTopic);

            dvlTopic = session.createTopic(DVL_TOPIC);
            consumer = session.createConsumer(dvlTopic, null, false);
            dvlListener = new JmsListener<>(consumer, DvlMessage.class);
            dvlProducer = session.createProducer(dvlTopic);

            powerTopic = session.createTopic(POWER_TOPIC);
            consumer = session.createConsumer(powerTopic, null, false);
            powerListener = new JmsListener<>(consumer, PowerMessage.class);
            powerProducer = session.createProducer(powerTopic);
            
            waterSpeedTopic = session.createTopic(WATER_SPEED_TOPIC);
            consumer = session.createConsumer(waterSpeedTopic, null, false);
            waterSpeedListener = new JmsListener<>(consumer, WaterSpeedMessage.class);
            waterSpeedProducer = session.createProducer(waterSpeedTopic);

            rpmTopic = session.createTopic(RPM_TOPIC);
            consumer = session.createConsumer(rpmTopic, null, false);
            rpmListener = new JmsListener<>(consumer, RpmMessage.class);
            rpmProducer = session.createProducer(rpmTopic);
            
            objectDetectionTopic = session.createTopic(OBJECT_DETECTION_TOPIC);
            consumer = session.createConsumer(objectDetectionTopic, null, false);
            objectDetectionListener = new JmsListener<>(consumer, ObjectDetectionMessage.class);
            objectDetectionProducer = session.createProducer(objectDetectionTopic);
            
            sensorPerturbationTopic = session.createTopic(SENSOR_PERTURBATION_TOPIC);
            consumer = session.createConsumer(sensorPerturbationTopic, null, false);
            sensorPerturbationListener = new JmsListener<>(consumer, SensorPerturbation.class);
            sensorPerturbationProducer = session.createProducer(sensorPerturbationTopic);
            
            powerPerturbationTopic = session.createTopic(POWER_PERTURBATION_TOPIC);
            consumer = session.createConsumer(powerPerturbationTopic, null, false);
            powerPerturbationListener = new JmsListener<>(consumer, RemusBatteryPerturbation.class);
            powerPerturbationProducer = session.createProducer(powerPerturbationTopic);
            
            commandTopic = session.createTopic(COMMAND_TOPIC);
            consumer = session.createConsumer(commandTopic, null, false);
            commandListener = new JmsListener<>(consumer, VehicleCommand.class);
            commandProducer = session.createProducer(commandTopic);
        } catch (JMSException e) {
            throw new RuntimeException(e.getMessage());
        }
    }

    /**
     * Implement one of these to sign up to receive messages. The number of different handlers for a particular message
     * is not limited.
     * 
     * @author chagnon
     *
     * @param <T>
     */
    public interface MessageHandler<T> {
        public void handleMessage(T message);
    }

    /**
     * Add a MessageHandler for simulation control.
     * @param handler
     */
    public static void addControlHandler(MessageHandler<SimulationControlMessage> handler) {
        controlListener.addHandler(handler);
    }

    /**
     * Add a MessageHandler for time stepping.
     * @param handler
     */
    public static void addStepHandler(MessageHandler<StepMessage> handler) {
    	stepListener.addHandler(handler);
    }
    
    /**
     * Add a MessageHandler for GroundTruthMessages.
     * @param handler
     */
    public static void addTruthHandler(MessageHandler<GroundTruthMessage> handler) {
        truthListener.addHandler(handler);
    }

    /**
     * Add a MessageHandler for VehicleCommands.
     * @param handler
     */
    public static void addCommandHandler(MessageHandler<VehicleCommand> handler) {
        commandListener.addHandler(handler);
    }

    /**
     * Add a MessageHandler for DvlMessages.
     * @param handler
     */
    public static void addDvlHandler(MessageHandler<DvlMessage> handler) {
        dvlListener.addHandler(handler);
    }

    /**
     * Add a MessageHandler for PowerMessages.
     * @param handler
     */
    public static void addPowerHandler (MessageHandler<PowerMessage> handler) {
        powerListener.addHandler(handler);
    }
    
    /**
     * Add a MessageHandler for RpmMessages.
     * @param handler
     */
    public static void addRpmHandler(MessageHandler<RpmMessage> handler) {
        rpmListener.addHandler(handler);
    }

    /**
     * Add a MessageHandler for ObjectDetectionMessages.
     * @param handler
     */
    public static void addObjectDetectionHandler(MessageHandler<ObjectDetectionMessage> handler) {
        objectDetectionListener.addHandler(handler);
    }
    
    /**
     * Add a MessageHandler for SensorPerturbation messages
     * @param sensors
     */
	public static void addSensorPerturbationHandler(MessageHandler<SensorPerturbation> sensors) {
		sensorPerturbationListener.addHandler(sensors);
	}
    
    /**
     * Add a MessageHandler for PowerPerturbation messages
     * @param sensors
     */
	public static void addRemusBatteryPerturbationHandler(MessageHandler<RemusBatteryPerturbation> sensors) {
		powerPerturbationListener.addHandler(sensors);
	}
    
    /**
     * Send a GroundTruthMessage.  Intended for the simulation side of things.
     * @param message
     */
    public static void sendGroundTruth(GroundTruthMessage message) {
        if (stopped) {
            return;
        }
        try {
            truthProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    /**
     * Send a SimulationControlMessage message.  Intended for the simulation side of things.
     * @param message
     */
    public static void sendSimulationControlMessage(SimulationControlMessage message) {
        if (stopped) {
            return;
        }
        try {
            controlProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    /**
     * Send a StepMessage message.  Forces a timestep to occur in stepping mode
     * @param message
     */
    public static void sendStepMessage(StepMessage message) {
    	if(stopped) {
    		return;
    	}
    	try {
    		stepProducer.send(message.toMapMessage());
    	} catch(JMSException e) {
    		e.printStackTrace();
    	}
    }
    
    /**
     * Send a VehicleCommand.  Intended for the Princess side of things.
     * @param message
     */
    public static void sendVehicleCommand(VehicleCommand message) {
        if (stopped) {
            return;
        }
        try {
            commandProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    /**
     * Send a DvlMessage.
     * @param message
     */
    public static void sendDvlMessage(DvlMessage message) {
        if (stopped) {
            return;
        }
        try {
            dvlProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    /**
     * Send a PowerMessage.
     * @param message
     */
    public static void sendPowerMessage(PowerMessage message) {
        if (stopped) {
            return;
        }
        try {
            powerProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }   
    
    /**
     * Send a PowerPerturbation message.
     * @param message
     */
    public static void sendPowerPerturbation(RemusBatteryPerturbation message) {
        if (stopped) {
            return;
        }
        try {
            powerPerturbationProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    /**
     * Send a WaterSpeedMessage.
     * @param message
     */
    public static void sendWaterSpeedMessage(WaterSpeedMessage message) {
        if (stopped) {
            return;
        }
        try {
            waterSpeedProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    

    /**
     * Send a RpmMessage.
     * @param message
     */
    public static void sendRpmMessage(RpmMessage message) {
        if (stopped) {
            return;
        }
        try {
            rpmProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    /**
     * Send an ObjectDetectionMessage.
     * @param message
     */
    public static void sendObjectDetectionMessage(ObjectDetectionMessage message) {
        if (stopped) {
            return;
        }
        try {
            objectDetectionProducer.send(message.toMapMessage());
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    public static void sendSensorPerturbation(SensorPerturbation message) {
    	if (stopped) {
    		return;    		
    	}
    	try {
    		sensorPerturbationProducer.send(message.toMapMessage());
    	} catch (JMSException e) {
    		e.printStackTrace();
    	}
    }
    
    private static class JmsListener<T extends MappableMessage> implements MessageListener {
        private final List<MessageHandler<T>> handlers = new ArrayList<>();
        private final Class<T> clazz;

        public void addHandler(MessageHandler<T> handler) {
            handlers.add(handler);
        }

        public JmsListener(MessageConsumer consumer, Class<T> clazz) {
            this.clazz = clazz;
            try {
                consumer.setMessageListener(this);
            } catch (JMSException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void onMessage(Message message) {
            if (message instanceof MapMessage) {
                try {
                    MappableMessage o = clazz.newInstance();
                    o.set((MapMessage) message);
                    for (MessageHandler<T> handler : handlers) {
                        handler.handleMessage(clazz.cast(o));
                    }
                } catch (InstantiationException | IllegalAccessException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    
    private static boolean stopped = false;
    public static void stop() {
        stopped = true;
        try {
            if (session != null) {
                session.close();
            }
        } catch (JMSException e) {
            e.printStackTrace();
        }
        try {
            if (connection != null) {
                connection.close();
            }
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    public static void clearHandlers() {
        controlListener.handlers.clear();
        truthListener.handlers.clear();
        commandListener.handlers.clear();
        dvlListener.handlers.clear();
        powerListener.handlers.clear();
        waterSpeedListener.handlers.clear();
        rpmListener.handlers.clear();
        sensorPerturbationListener.handlers.clear();
    }

}
