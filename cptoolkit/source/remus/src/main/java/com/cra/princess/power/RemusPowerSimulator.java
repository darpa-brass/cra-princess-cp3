package com.cra.princess.power;

import com.cra.princess.metron.remus.perturbation.BatteryPerturbationListener;
import com.cra.princess.metron.remus.perturbation.RemusBatteryPerturbation;
import com.cra.princess.metron.remus.state.RemusVehicleState;
import com.cra.princess.metron.remus.state.VehicleGroundTruthUpdateListener;
import com.cra.princess.metron.topic.BatteryPerturbationTopicWatcher;
import org.apache.log4j.Logger;

import javax.jms.*;
import java.lang.IllegalStateException;
import java.util.ArrayList;
import java.util.List;

/**
 * A simulated system monitoring an array of batteries on the REMUS 600 platform
 * 
 */
public class RemusPowerSimulator implements VehicleGroundTruthUpdateListener, BatteryPerturbationListener {
	private static final Logger LOG = Logger.getLogger(RemusPowerSimulator.class.getName());

	// JMS Session
	private Session session = null;

	public static final String POWER_TOPIC = "princess.power";
	private Destination powerTopic = null;
	private MessageProducer powerProducer = null;

	private RemusBattery battery = null;
	private PowerUpdateThread powerUpdateThread = null;
	private PowerReductionThread powerReductionThread = null;

	private List<PowerReductionEvent> events = null;

	private PowerReductionEventPlayer powerReductionEventPlayer = null;
	private BatteryPerturbationTopicWatcher batteryPerturbationTopicWatcher = null;

	private double startingPower = 2200.0;

	public RemusPowerSimulator(double startingPower, Session jmsSession) throws JMSException {
		this.startingPower = startingPower;
		this.session = jmsSession;
		this.events = new ArrayList<PowerReductionEvent>();

		try {
			// Create the topic to send power updates from the REMUS
			this.powerTopic = this.session.createTopic(POWER_TOPIC);
		} catch (JMSException e) {
			LOG.error(e);
			throw e;
		}
	}

	public void addPowerReductionEvent(PowerReductionEvent event) {
		this.events.add(event);
	}

	public void start() {
		try {
			this.powerProducer = this.session.createProducer(this.powerTopic);
		} catch (JMSException e) {
			LOG.error(e);
			throw new IllegalStateException("Could not create JMS power producer");
		}

		this.battery = new RemusBattery(this.startingPower);

		LOG.info("Starting Power Simulator with a charge of " + this.battery.getRemaining() + " Wh");
		this.powerReductionEventPlayer = new PowerReductionEventPlayer(this.battery, this.events);

		this.powerUpdateThread = new PowerUpdateThread(this.battery, this.powerProducer);
		this.powerReductionThread = new PowerReductionThread(this.battery);
		this.batteryPerturbationTopicWatcher = new BatteryPerturbationTopicWatcher(this.session);
		this.batteryPerturbationTopicWatcher.addBatteryPerturbationListener(this);

		this.powerUpdateThread.start();
		this.powerReductionThread.start();
		this.powerReductionEventPlayer.start();
		this.batteryPerturbationTopicWatcher.start();
	}

	public void stop() {
		LOG.info("Stopping Power Simulator with a charge of " + this.battery.getRemaining() + " Wh");
		if (this.batteryPerturbationTopicWatcher != null) {
			this.batteryPerturbationTopicWatcher.removeBatteryPerturbationListener(this);
			this.batteryPerturbationTopicWatcher.stopWatching();
		}

		if (this.powerReductionEventPlayer != null) {
			this.powerReductionEventPlayer.stopWork();
		}

		if (this.powerReductionThread != null) {
			this.powerReductionThread.stopWork();
		}

		if (this.powerUpdateThread != null) {
			this.powerUpdateThread.stopWork();
		}

		try {
			if (this.powerProducer != null) {
				this.powerProducer.close();
			}
		} catch (JMSException e) {
			LOG.error(e);
		}
	}

	public void pause() {
		this.powerUpdateThread.pauseWork();
		this.powerReductionThread.pauseWork();
		this.powerReductionEventPlayer.pauseWork();
	}

	public void resume() {
		this.powerUpdateThread.resumeWork();
		this.powerReductionThread.resumeWork();
		this.powerReductionEventPlayer.resumeWork();
	}

	@Override
	public void vehicleGroundTruthUpdate(RemusVehicleState vehicleStateUpdateMessage) {
		// Listen for vehicle ground truth and use the data in power reduction calculations
		double heading = vehicleStateUpdateMessage.getHeading();

		double vE = vehicleStateUpdateMessage.getvE();
		double vN = vehicleStateUpdateMessage.getvN();
		double speed = Math.sqrt((vE * vE) + (vN * vN));

		this.powerReductionThread.setHeading(heading);
		this.powerReductionThread.setSpeed(speed);
	}

	@Override
	public void batteryPerturbationUpdate(RemusBatteryPerturbation perturbation) {
		// Listen for battery perturbations sent in real time and immediately process them
		double powerReduction = perturbation.getPowerReduction() / 100.0;
		LOG.debug("Battery perturbation received: " + powerReduction + "% reduction");
		double energyUsed = this.battery.getRemaining() * powerReduction;
		LOG.debug("Deducting " + energyUsed + " watt-hours from battery");
		this.battery.useEnergy(energyUsed);
	}
}
