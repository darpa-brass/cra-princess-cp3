package com.metsci.dynamic.simple;

import java.awt.geom.Point2D;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Logger;

import javax.json.JsonObject;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.simulation.ConfigurationException;
import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.LtpGeodetics;
import com.cra.princess.simulation.TimeManager;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.World;
import com.cra.princess.simulation.events.EventDispatcher;
import com.metsci.numerics.ode.DifferentialEquation;
import com.metsci.numerics.ode.Ode45;
import com.metsci.numerics.ode.TimestepException;

/*
 * MB Gratton 2016-03-01: Basic 1st order/closed loop motion model.
 * 
 */
public class MotionModel implements 
    DifferentialEquation, 
    JsonConfigurable, 
    MessageHandler<VehicleCommand>,
    TimeStepped
    {
    private final static Logger LOGGER = Logger.getLogger(MotionModel.class.getName());
    
	// Command
	protected double speedCommand;	
	protected double headingCommand;
	protected double pitchCommand;
	protected double depthCommand;
	
    private long lastUpdate = 0;
    
    protected class InitialCondition {        
        /**
         * Heading, in degrees clockwise from North.
         */
        public double heading;
        /**
         * Pitch in degrees. Nose up is positive.
         */
        public double pitch;
        /**
         * Speed over water in m/s
         */
        public double speed;

        @Override
        public String toString() {
            return "InitialCondition [heading=" + heading+ ", pitch=" + pitch + ", speed=" + speed + "]";
        }
    }
    InitialCondition ic;
    
	// Geodetics
	private LtpGeodetics geoCalc;
	private double originDown = 0;
	
	protected enum DepthMode {
	    DEPTH, PITCH
	}
	protected DepthMode depthMode = DepthMode.PITCH;
	
	// Vehicle motion parameters
	MotionParameters param;

	// State variable packing order.
	protected enum State {
		NORTHING, EASTING, DOWN, SURGE, HEADING, PITCH
	}
	double[] odeState = new double[State.values().length];
	// DE solver
	protected Ode45 odeSolver;

	@Override
	public void configure(JsonObject o) {
	    if (o.containsKey("motionModel")) {
	        setParameters(MotionParameters.fromJson(o.getJsonObject("motionModel")));
	    } else { 
	        // LOGGER.warning("No motionModel defined in json. Using default values");
            setParameters(MotionParameters.getTest());
	    }
	    if (o.containsKey("origin")) {
	        JsonObject origin = o.getJsonObject("origin");
            double lat, lon, down = 0;
            if (origin.containsKey("depth"))
                down = origin.getJsonNumber("depth").doubleValue();     
            lat = origin.getJsonNumber("lat").doubleValue();
            lon = origin.getJsonNumber("lon").doubleValue();
            setOrigin(lat, lon, down);	        
	    } else {
	        setOrigin(0,0,0);
	    }
	    if (o.containsKey("ic")) {
	        JsonObject ico = o.getJsonObject("ic");
            ic = new InitialCondition();
            ic.heading = ico.getJsonNumber("heading").doubleValue();
            ic.pitch = ico.getJsonNumber("pitch").doubleValue();
            ic.speed = ico.getJsonNumber("speed").doubleValue();	     
            ConfigurationException.check("pitch IC", ic.pitch, -param.maxPitch, param.maxPitch);
            ConfigurationException.check("speed IC", ic.speed, param.minSpeed, param.maxSpeed);
	    } else {
	        ic = null;
	    }
	    initialize();
	    
	    if (o.containsKey("command")) {
	    	JsonObject co = o.getJsonObject("command");
	    	VehicleCommand command = new VehicleCommand();
    		command.depthTarget = co.getJsonNumber("depthTarget").doubleValue();
    		command.headingTarget = co.getJsonNumber("headingTarget").doubleValue();
    		command.speedTarget = co.getJsonNumber("speedTarget").doubleValue();
    		handleMessage(command);
	    }
	    EventDispatcher.registerConsumer(VehicleCommand.class, this);
	}
	
	
    @Override
	public void handleMessage(VehicleCommand message) {
        headingCommand = unwind(Math.toRadians(message.headingTarget));
        speedCommand = Math.min(param.maxSpeed, Math.max(param.minSpeed, message.speedTarget));
        setDepthCommand(message.depthTarget);
	}


    @Override
    public void initialize() {
    	prepOdeSolver(guessTolerance(param));    	            
        if (ic == null)
            setState(0,0,0,0,0,0);
        else {
            double psi = Math.toRadians(ic.heading);
            double theta = Math.toRadians(ic.pitch);
            double vn = ic.speed * Math.cos(psi) * Math.cos(theta);
            double ve = ic.speed * Math.sin(psi) * Math.cos(theta);
            double vd = -ic.speed * Math.sin(theta);            
            setState(0,0,0,vn,ve,vd);            
        }
        lastUpdate = TimeManager.now();
    }
    
    @Override
    public void reset() {
        ic = null;
        headingCommand = 0;
        setPitchCommand(0);
        speedCommand = 0;        
        initialize();        
    }

    @Override
    public void update() {
        long now = TimeManager.now();
        double elapsed = 1e-3*(now - lastUpdate);
        lastUpdate = now;
        try {
            update(elapsed);
        } catch (TimestepException e) {
            LOGGER.warning("Could not integrate ODE: " + e.getLocalizedMessage());
            throw new RuntimeException(e.getLocalizedMessage());
        }
        // This state handling is a little awkward.  Ideally we'd have a separate thing that just
        // sends GroundTruthMessages to JMS.
        GroundTruthMessage state = makeStateMessage();
        JmsManager.sendGroundTruth(state);
        EventDispatcher.publishEvent(state);        
    }
    
    
    public GroundTruthMessage makeStateMessage() {
        // Could have the message as a member variable, but I'd be nervous about its
        // mutability.
        GroundTruthMessage m = new GroundTruthMessage();
        m.heading = Math.toDegrees(getHeading());
        m.pitch = Math.toDegrees(getPitch());
        m.roll = 0;
        m.timestamp = TimeManager.now();
        double[] latLon = geoCalc.getLatLon(getNorthing(), getEasting());
        m.trueLatitude = latLon[0];
        m.trueLongitude = latLon[1];
        m.trueDepth = originDown + getDown();
        Point2D current = World.currentSource.current(m.trueLatitude, m.trueLongitude, m.trueDepth);        
        double[] velocity = getVelocityWorld();
        m.vE = velocity[1] + current.getX();
        m.vN = velocity[0] + current.getY();
        m.vU = -velocity[2];
        // Extended state information
        m.surge = getSurge();
        m.sway = getSway();
        m.heave = getHeave();
        m.northing = getNorthing();
        m.easting = getEasting();
        m.down = getDown();
        m.waterCurrentE = current.getX();
        m.waterCurrentN = current.getY();
        m.waterDepth = World.bathymetrySource.depth(m.trueLatitude, m.trueLongitude);
        m.rpm = getRpm();
        m.rudderAngle = Math.toDegrees(getRudderAngle());
        m.elevatorAngle = Math.toDegrees(getElevatorAngle());
        return m;
    }
	

	private void update(double timeStep) throws TimestepException { // timeStep is measured in seconds
	    odeSolver.integrate(0, timeStep, odeState);
		odeState = odeSolver.getState();					
	}

	protected void setState(double north_, double east_, double down_, double velocityNorth_, double velocityEast_,
			double velocityDown_) {
	    odeState[State.NORTHING.ordinal()] = north_;
	    odeState[State.EASTING.ordinal()] = east_;
	    odeState[State.DOWN.ordinal()] = down_;		
		odeState[State.SURGE.ordinal()]= Math.sqrt(
				velocityNorth_ * velocityNorth_ + velocityEast_ * velocityEast_ + velocityDown_ * velocityDown_);
		double speed2D = Math.sqrt(velocityNorth_ * velocityNorth_ + velocityEast_ * velocityEast_);
		odeState[State.HEADING.ordinal()] = Math.atan2(velocityEast_, velocityNorth_);
		odeState[State.PITCH.ordinal()]= -Math.atan2(velocityDown_, speed2D);				
	}

	// Called by ODE solver.
	@Override
	public void computeDerivative(double[] rhs, final double[] state, double t) {				
	    odeState = state;	    		
		double[] latLon = geoCalc.getLatLon(getNorthing(), getEasting());
		Point2D currentEN = World.currentSource.current(latLon[0], latLon[1], getDown() + originDown);
		double[] velocity = getVelocityWorld(); 
		rhs[State.NORTHING.ordinal()] = velocity[0] + currentEN.getY();
		rhs[State.EASTING.ordinal()] = velocity[1] + currentEN.getX();
		rhs[State.DOWN.ordinal()] = velocity[2];
		
		double omega = getTurnRate();
		double q = getPitchRate();
		double rpm = getRpm();
		double surge = getSurge();
		double sway = getSway();
		double heave = getHeave();
		rhs[State.SURGE.ordinal()] = param.getM22h()*sway*omega - param.getM33h()*heave*q 
				- param.getDrag()*Math.abs(surge)*surge
				+ param.getThrust()*Math.abs(rpm)*rpm;
		rhs[State.HEADING.ordinal()] = omega/Math.cos(getPitch());
		rhs[State.PITCH.ordinal()] = q;
	}

	protected void prepOdeSolver(double tolerance) {
		odeSolver = new Ode45(this, odeState);
		odeState = odeSolver.getState();
		odeSolver.setTolerance(tolerance);
		odeSolver.setMinDt(1e-3);
        odeSolver.setMuddle(true);
	}

	protected double getTurnRate() {
		double maxHeadingRate = getSurge()/param.getTurnRadius();		
		double headingError = unwind(headingCommand - getHeading());
		return sat(param.getHeadingRate() * headingError, maxHeadingRate);
	}
	
	protected double getPitchRate() {
	    if (depthMode == DepthMode.DEPTH) {
	        double KP = 0.3 * param.getPitchRate() / Math.max(getSurge(), 1.0);
	        double error = depthCommand - getDown();
	        pitchCommand = sat(-KP * error, Math.toRadians(param.getMaxPitch()));
	    }
	    return param.getPitchRate() * (pitchCommand - getPitch());
	}
    
    protected double getRpm() {
    	speedCommand = Math.max(Math.min(param.getMaxSpeed(), speedCommand), param.getMinSpeed());
    	final double KP = 100.0;
    	double rpm0 = Math.sqrt(param.getDrag()/param.getThrust() )*speedCommand;
    	return  Math.min(param.getRpmMax(), rpm0 + KP*(speedCommand - getSurge()) );    	
    }
    
    // Only for output -- not used in dynamics
    protected double getRudderAngle() {    	
    	return param.getRudderAngleMap()*getTurnRate();    	
    }
    protected double getElevatorAngle() {
    	return param.getElevatorAngleMap()*getPitch();
    }
	   
    protected void setDepthCommand(double depthTarget) {
        depthMode = DepthMode.DEPTH;
        depthCommand = depthTarget - originDown;
    }
    
    protected void setPitchCommand(double pitchTarget) {
        depthMode = DepthMode.PITCH;
        pitchCommand = sat(pitchTarget, Math.toRadians(param.getMaxPitch()));
    }

    
	protected double sat(double x, double maxX) {
		if (Math.abs(x) > maxX)
			return Math.signum(x) * maxX;
		return x;
	}

	public static double unwind(double d) {
		final double BIAS = 1e-5; // Resolve branch cuts
		final double TURN = 2.0 * Math.PI;
		d += BIAS;
		while (d > Math.PI)
			d -= TURN;
		while (d < -Math.PI)
			d += TURN;
		d -= BIAS;
		return d;
	}

	public double getHeading() {
		return unwind(odeState[State.HEADING.ordinal()]);
	}

	public double getNorthing() {
		return odeState[State.NORTHING.ordinal()];
	}

	public double getEasting() {
		return odeState[State.EASTING.ordinal()];
	}

	public double getDown() {
		return odeState[State.DOWN.ordinal()];
	}

	public double[] getVelocityWorld() {			   
	    double[] vw = new double[] {getSurge(), getSway(), getHeave()};
	    AffineTransform R = new AffineTransform(0,0,0,  getRoll(), getPitch(), getHeading());
	    R.transform(vw);	    
	    return vw;
	}
	
	public double getRoll() {
		return 0; // no roll mode
	}
	
	public double getPitch() {
		return odeState[State.PITCH.ordinal()];
	}

	public double getSpeed() {
		double u = getSurge();
		double v = getSway();
		double w = getHeave();
		return Math.sqrt(u*u + v*v + w*w);
	}
	
	public double getSurge() {
		return odeState[State.SURGE.ordinal()];
	}

	public double getSway() {		
		return -param.getSwayPerTurn() * getTurnRate();
	}
	
	public double getHeave() {		
		return param.getHeavePerTurn() * getPitchRate();
	}
	
	/* Extract capabilities */
	public MotionParameters getMotionParameters() { 
		return param; 		
	}

	protected void setParameters(MotionParameters param_)  {
	    param = param_;	          
	}
	
	protected void setOrigin(double originLat, double originLon, double originDown)    {        
        this.originDown = originDown;
        geoCalc = new LtpGeodetics(originLat, originLon);        
    }
    
    protected void setOrigin(double originLat, double originLon)    {
        setOrigin(originLat, originLon, 0);
    }
    
    protected void setIc(InitialCondition ic) { 
        this.ic = ic; 
    }          
    
    protected double guessTolerance(MotionParameters param) {
        final double MIN_TOL = 1e-8;
        double tol = 1e-4;        
        tol = Math.max(tol, MIN_TOL);
        LOGGER.fine(String.format("Using ODE tolerance of %g", tol));                
        return tol;
    }
   
    public MotionModel() {                        
        TimeManager.addStepper(this);
    }
	
    @Override
    public void stop() {
    }

    
	static public void main(String[] args) {
		MotionModel testModel = new MotionModel();
		testModel.setParameters(MotionParameters.getTest());
		testModel.setOrigin(32.0, -170, 0);
		MotionModel.InitialCondition ic = testModel.new InitialCondition();
		ic.heading = 0;
		ic.pitch = 0;
		ic.speed = 2.2;
		testModel.setIc(ic);				
		testModel.initialize();
		
		VehicleCommand cmd = new VehicleCommand();
		cmd.depthTarget = 5.0;
		cmd.headingTarget = 179.0;
		cmd.speedTarget = 3.0;		        
		testModel.handleMessage(cmd);
		double dt = 1.0;
		double tIntegrate = 150.0;
		double tmax = tIntegrate;
		double t = 0;
		try {
		    FileWriter of = new FileWriter("test.dat");
/*		    while (t < tmax) {			
		        testModel.update(dt);			
		        t += dt;
		        double[] vw = testModel.getVelocityWorld();
		        of.write(String.format("%g %g %g %g %g %g %g %g\n", t, testModel.getNorthing(), testModel.getEasting(), testModel.getDown(),
		                vw[0], vw[1], vw[2], testModel.getHeading()));
		    }
		    cmd.headingTarget = -92;
		    testModel.handleMessage(cmd);
		    tmax = 2*tIntegrate;
		    while (t < tmax) {            
                testModel.update(dt);           
                t += dt;
                double[] vw = testModel.getVelocityWorld();
                of.write(String.format("%g %g %g %g %g %g %g %g\n", t, testModel.getNorthing(), testModel.getEasting(), testModel.getDown(),
                        vw[0], vw[1], vw[2], testModel.getHeading()));
            }
		    cmd.headingTarget = 85;
            testModel.handleMessage(cmd);
            tmax = 3*tIntegrate;
            while (t < tmax) {            
                testModel.update(dt);           
                t += dt;
                double[] vw = testModel.getVelocityWorld();
                of.write(String.format("%g %g %g %g %g %g %g %g\n", t, testModel.getNorthing(), testModel.getEasting(), testModel.getDown(),
                        vw[0], vw[1], vw[2], testModel.getHeading()));
            }*/
            while (t < tmax) {            
                testModel.update(dt);           
                t += dt;                
                of.write(String.format("%g %g %g %g\n", t, testModel.getSpeed(), testModel.getHeading(), testModel.getRpm()
                        ));
            }
            cmd.headingTarget = 1;
            cmd.speedTarget = 3.0;
            testModel.handleMessage(cmd);
            tmax += tIntegrate;
            while (t < tmax) {            
                testModel.update(dt);           
                t += dt;                
                of.write(String.format("%g %g %g %g\n", t, testModel.getSpeed(), testModel.getHeading(), testModel.getRpm()
                        ));
            }
            cmd.headingTarget = 90;            
            testModel.handleMessage(cmd);
            tmax += tIntegrate;
            while (t < tmax) {            
                testModel.update(dt);           
                t += dt;                
                of.write(String.format("%g %g %g %g\n", t, testModel.getSpeed(), testModel.getHeading(), testModel.getRpm()
                        ));
            }
            cmd.depthTarget = 20;            
            testModel.handleMessage(cmd);
            tmax += tIntegrate;
            while (t < tmax) {            
                testModel.update(dt);           
                t += dt;                
                of.write(String.format("%g %g %g %g\n", t, testModel.getSpeed(), testModel.getHeading(), testModel.getRpm()
                        ));
            }
		    of.close();
		} catch (TimestepException e) {
		    System.out.println("Ooops, timestep underflow!");		    
		} catch (IOException e) {
		    System.out.println("Ooops, can't open file.");
		}
	}


}
