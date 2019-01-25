package com.cra.princess.metron;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import javax.jms.Connection;
import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.MessageProducer;
import javax.jms.Session;
import javax.jms.Destination;

import com.cra.princess.metron.remus.state.*;
import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.broker.BrokerService;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

import com.cra.princess.metron.remus.command.RemusVehicleCommand;
import com.cra.princess.metron.remus.control.SimulationControlListener;
import com.cra.princess.metron.remus.control.SimulationControlMessage;

/**
 * Class to test messages to and from the Metron REMUS simulator.
 * 
 */
public class MetronRemusManagerTest implements VehicleGroundTruthUpdateListener, DvlSensorUpdateListener, SimulationControlListener, ObjectDetectionListener, RpmSensorUpdateListener, WaterSpeedSensorUpdateListener {
	private static BrokerService broker = null;
	private static Connection connection = null;
	private static Session session = null;
	private static MessageProducer truthProducer = null;
	private static MessageProducer dvlProducer = null;
	private static MessageProducer controlProducer = null;
	private static MessageProducer objectDetectionProducer = null;
	private static MessageProducer rpmProducer = null;
	private static MessageProducer waterSpeedProducer = null;

	@BeforeClass
    public static void runOnceBeforeClass() throws Exception {
		// Start an embedded JMS broker
    	broker = new BrokerService();
    	broker.addConnector("tcp://localhost:61616");
    	broker.start();

    	// Create the princess.state JMS topic
    	ActiveMQConnectionFactory factory = new ActiveMQConnectionFactory("tcp://localhost:61616");
    	connection = factory.createConnection();
        connection.start();
        session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
    	Destination truthTopic = session.createTopic("princess.truth");
    	truthProducer = session.createProducer(truthTopic);    
    	Destination dvlTopic = session.createTopic("princess.dvl");
    	dvlProducer = session.createProducer(dvlTopic);
    	Destination controlTopic = session.createTopic("princess.control");
    	controlProducer = session.createProducer(controlTopic);
		Destination objectDetectionTopic = session.createTopic("princess.objectdetection");
		objectDetectionProducer = session.createProducer(objectDetectionTopic);
		Destination rpmTopic = session.createTopic("princess.rpm");
		rpmProducer = session.createProducer(rpmTopic);
		Destination waterSpeedTopic = session.createTopic("princess.waterspeed");
		waterSpeedProducer = session.createProducer(waterSpeedTopic);
	}

    @AfterClass
    public static void runOnceAfterClass() throws Exception {
    	// Shut down JMS
    	session.close();
    	connection.close();
    	broker.stop();
    }
	
	@Test
    public void createAndSendTest() throws RemusManagerException, JMSException {
		MetronRemusManager manager = MetronRemusManager.getInstance();
    	assertNotNull(manager);

    	manager.addVehicleGroundTruthUpdateListener(this);
    	manager.addDvlSensorUpdateListener(this);
    	manager.addSimulationControlListener(this);
		manager.addObjectDetectionListener(this);
		manager.addRpmSensorUpdateListener(this);
		manager.addWaterSpeedSensorUpdateListener(this);

    	manager.start();

    	sendGroundTruthMessage();
    	
    	sendDvlSensorUpdateMessage();

    	sendControlMessage();    	
    	
    	sendVehicleCommandMessage();

		sendObjectDetectionMessage();

		sendRpmSensorUpdateMessage();

		sendWaterSpeedSensorUpdateMessage();

    	manager.stop();
	}

	private void sendGroundTruthMessage() throws JMSException {
    	// Send state update data String to the MetronRemusManager as a MapMessage
		MapMessage message = session.createMapMessage();

		message.setLong("timestamp", 1474383471000L);
		message.setDouble("trueLongitude", -117.000000);
		message.setDouble("trueLatitude", 30.000000);
		message.setDouble("trueDepth", 10.000);
       	message.setDouble("vE", 0.000);
       	message.setDouble("vN", 0.280);
       	message.setDouble("vU", -0.155);
       	message.setDouble("pitch", -29.00);
       	message.setDouble("roll", 0.00);
       	message.setDouble("heading", 0.00);
		
		truthProducer.send(message);

    	// Wait for message to be sent
    	try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// Ignore
		} 		
	}	

	private void sendDvlSensorUpdateMessage() throws JMSException {
    	// Send state update data String to the MetronRemusManager as a MapMessage
		MapMessage message = session.createMapMessage();

		message.setLong("timestamp", 1474383471000L);
		message.setDouble("depth", 10.000);
       	message.setDouble("vE", 0.000);
       	message.setDouble("vN", 0.280);
       	message.setDouble("vU", -0.155);
       	message.setDouble("pitch", -29.00);
       	message.setDouble("roll", 0.00);
       	message.setDouble("heading", 0.00);
		
		dvlProducer.send(message);

    	// Wait for message to be sent
    	try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// Ignore
		} 		
	}

	private void sendControlMessage() throws JMSException {
    	// Send state update data String to the MetronRemusManager as a MapMessage
		MapMessage message = session.createMapMessage();

		message.setString("detail", "Simulation over");
		
		controlProducer.send(message);

    	// Wait for message to be sent
    	try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// Ignore
		} 		
	}

	private void sendObjectDetectionMessage() throws JMSException {
		// Send state update data String to the MetronRemusManager as a MapMessage
		MapMessage message = session.createMapMessage();

		message.setLong("timestamp", 1474383471000L);
		message.setDouble("range", 10.0);
		message.setDouble("theta", 0.1);
		message.setDouble("phi", 0.001);

		objectDetectionProducer.send(message);

		// Wait for message to be sent
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// Ignore
		}
	}

	private void sendRpmSensorUpdateMessage() throws JMSException {
		// Send state update data String to the MetronRemusManager as a MapMessage
		MapMessage message = session.createMapMessage();

		message.setLong("timestamp", 1474383471000L);
		message.setDouble("PropellerRpm", 123.4);

		rpmProducer.send(message);

		// Wait for message to be sent
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// Ignore
		}
	}

	private void sendWaterSpeedSensorUpdateMessage() throws JMSException {
		// Send state update data String to the MetronRemusManager as a MapMessage
		MapMessage message = session.createMapMessage();

		message.setLong("timestamp", 1474383471000L);
		message.setDouble("WaterSpeed", 1.2);

		waterSpeedProducer.send(message);

		// Wait for message to be sent
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// Ignore
		}
	}

	private void sendVehicleCommandMessage() throws RemusManagerException {
		MetronRemusManager manager = MetronRemusManager.getInstance();
    	assertNotNull(manager);

    	// Send a vehicle command
    	double heading = 90.0;
    	double depth = 10.0;
    	double speed = 5.0;
    	RemusVehicleCommand command = new RemusVehicleCommand(heading, depth, speed);
    	manager.sendVehicleCommand(command);

    	// Wait for message to be sent
    	try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// Ignore
		} 		
	}	
	
	@Override
	public void vehicleGroundTruthUpdate(RemusVehicleState vehicleStateUpdateMessage) {
		assertNotNull(vehicleStateUpdateMessage);

		assertTrue(vehicleStateUpdateMessage.getTimestamp() == 1474383471000L);
		assertTrue(vehicleStateUpdateMessage.getTrueLatitude() == 30.0);
		assertTrue(vehicleStateUpdateMessage.getTrueLongitude() == -117.0);
		assertTrue(vehicleStateUpdateMessage.getTrueDepth() == 10.0);
		assertTrue(vehicleStateUpdateMessage.getvE() == 0.0);
		assertTrue(vehicleStateUpdateMessage.getvN() == 0.280);
		assertTrue(vehicleStateUpdateMessage.getvU() == -0.155);
		assertTrue(vehicleStateUpdateMessage.getPitch() == -29.0);
		assertTrue(vehicleStateUpdateMessage.getRoll() == 0.0);
		assertTrue(vehicleStateUpdateMessage.getHeading() == 0.0);
	}

	@Override
	public void dvlSensorUpdate(RemusDvlData dvlDataMessage) {
		assertNotNull(dvlDataMessage);

		assertTrue(dvlDataMessage.getTimestamp() == 1474383471000L);
		assertTrue(dvlDataMessage.getDepth() == 10.0);
		assertTrue(dvlDataMessage.getvE() == 0.0);
		assertTrue(dvlDataMessage.getvN() == 0.280);
		assertTrue(dvlDataMessage.getvU() == -0.155);
		assertTrue(dvlDataMessage.getPitch() == -29.0);
		assertTrue(dvlDataMessage.getRoll() == 0.0);
		assertTrue(dvlDataMessage.getHeading() == 0.0);
	}

	@Override
	public void controlUpdate(SimulationControlMessage controlMessage) {
		assertNotNull(controlMessage);

		assertTrue(controlMessage.getPlayControl().equals(SimulationControlMessage.CONTROL_COMMAND_STOP));
	}

	@Override
	public void objectDetected(RemusObjectDetectionState objectDetectionMessage) {
		assertNotNull(objectDetectionMessage);

		assertTrue(objectDetectionMessage.getTimestamp() == 1474383471000L);
		assertTrue(objectDetectionMessage.getRange() == 10.0);
		assertTrue(objectDetectionMessage.getTheta() == 0.1);
		assertTrue(objectDetectionMessage.getPhi() == 0.001);
	}

	@Override
	public void rpmSensorUpdate(RemusRpmData rpmDataMessage) {
		assertNotNull(rpmDataMessage);

		assertTrue(rpmDataMessage.getTimestamp() == 1474383471000L);
		assertTrue(rpmDataMessage.getRpm() == 123.4);
	}

	@Override
	public void waterSpeedSensorUpdate(RemusWaterSpeedData waterSpeedDataUpdateMessage) {
		assertNotNull(waterSpeedDataUpdateMessage);

		assertTrue(waterSpeedDataUpdateMessage.getTimestamp() == 1474383471000L);
		assertTrue(waterSpeedDataUpdateMessage.getSpeed() == 1.2);
	}
}
