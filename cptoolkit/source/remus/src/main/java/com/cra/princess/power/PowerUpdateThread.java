package com.cra.princess.power;

import com.cra.princess.metron.remus.state.RemusPowerState;
import org.apache.activemq.command.ActiveMQMapMessage;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.MessageProducer;
import java.util.Date;

/**
 * Periodically sends remaining battery power update messages to an ActiveMQ topic
 * 
 */
public class PowerUpdateThread extends Thread {
	private static final Logger LOG = Logger.getLogger(PowerUpdateThread.class.getName());

	private boolean doWork = true;
	private RemusBattery battery = null;
	private MessageProducer powerMessageProducer = null;
	private boolean paused = false;

	public PowerUpdateThread(RemusBattery battery, MessageProducer powerMessageProducer) {
		super();

		if (battery == null) {
			String msg = "Invalid battery provided";
			LOG.error(msg);
			throw new IllegalArgumentException(msg);
		}

		if (powerMessageProducer == null) {
			String msg = "Invalid powerMessageProducer provided";
			LOG.error(msg);
			throw new IllegalArgumentException(msg);
		}

		this.battery = battery;
		this.powerMessageProducer = powerMessageProducer;
	}
	
	@Override
	public void run() {
		while(doWork) {
			if (this.paused == false) {
				try {
					MapMessage message = createRemainingPowerMessage();
					this.powerMessageProducer.send(message);

					Thread.sleep(1000);
				} catch (JMSException e) {
					LOG.error(e.getMessage(), e);
				} catch (InterruptedException e) {
					// Ignore
				}
			}
			else {
				// Wait to resume
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					// Ignore
				}
			}
		}
	}

	private MapMessage createRemainingPowerMessage() {
		MapMessage message = new ActiveMQMapMessage();
		try {
			Date now = new Date();
			message.setLong(RemusPowerState.DATA_FIELD_TIMESTAMP, now.getTime());
			message.setDouble(RemusPowerState.DATA_FIELD_POWER, this.battery.getRemaining());
		} catch (JMSException e) {
			LOG.error(e.getMessage(), e);
		}

		return message;
	}

	public void stopWork() {
		this.doWork = false;
	}

	public void pauseWork() {
		this.paused = true;
	}

	public void resumeWork() {
		this.paused = false;
	}
}
