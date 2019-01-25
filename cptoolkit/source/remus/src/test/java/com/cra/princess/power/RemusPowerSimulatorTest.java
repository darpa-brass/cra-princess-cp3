package com.cra.princess.power;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.broker.BrokerService;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

import javax.jms.Connection;
import javax.jms.Destination;
import javax.jms.JMSException;
import javax.jms.Session;

import static junit.framework.TestCase.assertTrue;

/**
 * Testing the simulated array of batteries on a REMUS
 * 
 */
public class RemusPowerSimulatorTest {
	private static BrokerService broker = null;
	private static Connection connection = null;
	private static Session session = null;

	@BeforeClass
	public static void runOnceBeforeClass() throws Exception {
		// Start an embedded JMS broker
		broker = new BrokerService();
		broker.addConnector("tcp://localhost:61616");
		broker.start();

		ActiveMQConnectionFactory factory = new ActiveMQConnectionFactory("tcp://localhost:61616");
		connection = factory.createConnection();
		connection.start();
		session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
	}

	@AfterClass
	public static void runOnceAfterClass() throws Exception {
		broker.stop();
		session.close();
		connection.close();
	}

	@Test
	public void powerSimulatorTest() {

		try {
			RemusPowerSimulator sim = new RemusPowerSimulator(5.4, session);
			assertTrue(sim != null);

			sim.start();
			// Wait 5 seconds for the power to go down
			Thread.sleep(5000);
			sim.stop();
		}
		catch(JMSException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
