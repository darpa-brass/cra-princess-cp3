package com.cra.sim.sensor;

import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

import javax.json.JsonObject;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.ObjectDetectionMessage;
import com.cra.princess.simulation.ConfigurationException;
import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonConfigurableFactory;
import com.cra.princess.simulation.TimeManager;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.World;
import com.cra.princess.simulation.events.EventDispatcher;
import com.metsci.dynamic.simple.AffineTransform;

public class ObjectDetector  implements JsonConfigurable, MessageHandler<GroundTruthMessage>, TimeStepped, Sensor {
	private static final Logger LOGGER = Logger.getLogger(ObjectDetector.class.getName());
	GroundTruthMessage cachedState;
	long lastMessageTime = 0;
	long detectionInterval = 50;
	double coarseRange;
	double range;
	double apertureH; // half the 'xy' aperture
	double apertureV; // half the 'xz' aperture
	AffineTransform bodyToSensor;
	AffineTransform worldToBody = new AffineTransform();
	ObjectDetectionModel detectionModel;
	
	public ObjectDetector() {
        EventDispatcher.registerConsumer(GroundTruthMessage.class, this);
        TimeManager.addStepper(this);
	}
	
	@Override
	public void initialize() {		
		reset();
	}

	@Override
	public void update() {
        long elapsed = TimeManager.now() - lastMessageTime;
        if (elapsed >= detectionInterval && cachedState != null) {
            lastMessageTime = TimeManager.now();
            List<ObjectDetectionMessage> objects = getMeasurement(cachedState); 
            if (objects == null)
            	return;
            for (ObjectDetectionMessage message : objects) {
            	EventDispatcher.publishEvent(message);
            	JmsManager.sendObjectDetectionMessage(message);
            }
        }
	}

	private ArrayList<ObjectDetectionMessage> getMeasurement(GroundTruthMessage state) {		
		worldToBody.setRotation(
				Math.toRadians(state.roll), 
				Math.toRadians(state.pitch), 
				Math.toRadians(state.heading)).transpose();
		List<double[]> nearby = World.bottomObjectStore.getNearby(state.trueLatitude, state.trueLongitude, state.trueDepth, coarseRange);
		List<double[]> opportunity = new ArrayList<double[]>();
		for (double[] near : nearby) {
			double[] sensorXyz = bodyToSensor.transform(worldToBody.transform(near));
			double r2 = sensorXyz[0]*sensorXyz[0] + sensorXyz[1]*sensorXyz[1];
			double rho = Math.sqrt(r2 + sensorXyz[2]*sensorXyz[2]);
			double r = Math.sqrt(r2);
			double theta = Math.atan2(sensorXyz[1], sensorXyz[0]);
			double verticalAzimuth = Math.atan2(sensorXyz[2], sensorXyz[0]);			
			if (rho < range && Math.abs(theta) < apertureH && Math.abs(verticalAzimuth) < apertureV) {
				double phi = Math.atan2(sensorXyz[2], r);
				opportunity.add(new double[] {rho, theta, phi});
				// LOGGER.info(String.format("Got object sensor op: %g, %g, %g (%g, %g, %g)", sensorXyz[0], sensorXyz[1], sensorXyz[2], rho, theta, verticalAzimuth));
			}
		}
		if (opportunity.isEmpty())
			return null;
		ArrayList<ObjectDetectionMessage> message = new ArrayList<ObjectDetectionMessage>();
		for (double[] op : opportunity) {			
			if (detectionModel.detect(op)) {
				ObjectDetectionMessage detect = new ObjectDetectionMessage();
				detect.timestamp = TimeManager.now();
				detect.set(detectionModel.dirty(op));				
				message.add(detect);
				LOGGER.fine("Detection: " + detect);
			}
		}
		return message;
	}

	@Override
	public void reset() {
		cachedState = null;
		lastMessageTime = 0;
	}

	@Override
	public void stop() {		
	}

	@Override
	public void handleMessage(GroundTruthMessage message) {
		cachedState = message;
	}

	@Override
	public void configure(JsonObject o) {
		try {	
			JsonObject off = o.getJsonObject("offset");
			double x = off.getJsonNumber("x").doubleValue();
			double y = off.getJsonNumber("y").doubleValue();
			double z = off.getJsonNumber("z").doubleValue();
			JsonObject ori = o.getJsonObject("orientation");
			double roll = ori.getJsonNumber("roll").doubleValue();
			double pitch = ori.getJsonNumber("pitch").doubleValue();
			double yaw = ori.getJsonNumber("yaw").doubleValue();

			ConfigurationException.check("x", x, -3, 3);
			ConfigurationException.check("y", y, -0.5, 0.5);
			ConfigurationException.check("z", z, -0.5, 0.5);			
			ConfigurationException.check("pitch", pitch, -90, 90);			
			
			bodyToSensor = (new AffineTransform(x, y, z, 
					Math.toRadians(roll), Math.toRadians(pitch), Math.toRadians(yaw))).transpose();
			range = o.getJsonNumber("range").doubleValue();
			apertureH = o.getJsonNumber("horizontalAperture").doubleValue();
			apertureV = o.getJsonNumber("verticalAperture").doubleValue();

			ConfigurationException.check("range", range, 0, 1e3);
			ConfigurationException.check("horizontalAperture", apertureH, 0, 180);
			ConfigurationException.check("verticalAperture", apertureV, 0, 90);
			apertureH = 0.5*Math.toRadians(apertureH);
			apertureV = 0.5*Math.toRadians(apertureV);
			
			coarseRange = range + Math.sqrt(x*x + y*y + z*z);
			
			JsonConfigurableFactory fac = new JsonConfigurableFactory();
			JsonObject objectDetectionConfig = o.getJsonObject("detection");
	        detectionModel = (ObjectDetectionModel) fac.construct(objectDetectionConfig);
			
		} catch (NullPointerException e) {
			throw new ConfigurationException("One or more required parameters missing.\n" + e.getMessage());
		}		
	}

	public static void main(String[] args) {
		
		ObjectDetector det = new ObjectDetector();
		det.worldToBody = new AffineTransform(0, 0, 0, 0, 0, 0);
		det.bodyToSensor = (new AffineTransform(0, 0, 0, 0, -Math.PI*0.5, 0)).transpose();
		List<double[]> nearby = new ArrayList<double[]>();
		nearby.add(new double[] {10, 1, 20});		
		for (double[] near : nearby) {
			double[] x1 = det.worldToBody.transform(near);
			double[] sensorXyz = det.bodyToSensor.transform(x1);
			double r2 = sensorXyz[0]*sensorXyz[0] + sensorXyz[1]*sensorXyz[1];
			double rho = Math.sqrt(r2 + sensorXyz[2]*sensorXyz[2]);
			double r = Math.sqrt(r2);
			double theta = Math.atan2(sensorXyz[1], sensorXyz[0]);
			double phi = Math.atan2(sensorXyz[2], r);
			System.out.println(String.format("x = [%g, %g, %g] r = [%g, %g, %g]", sensorXyz[0], sensorXyz[1], sensorXyz[2], rho, theta, phi));
		}
	}

	@Override
	public void register(SensorManager manager) {
		// Does not have a standard perturbation, so nothing here
	}
	
}
