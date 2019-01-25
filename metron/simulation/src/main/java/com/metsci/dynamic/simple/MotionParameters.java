package com.metsci.dynamic.simple;

import java.util.Properties;

import javax.json.JsonObject;

import com.cra.princess.simulation.ConfigurationException;

/*
 * Parameters defining motions in motion model.  All values are in SI units.
 */

public class MotionParameters {
 
	public static MotionParameters getTest() {
		double maxSpeed = 3.0;
		double minSpeed = 0.1;
		double maxPitch = 80.0;
		double turnRadius = 17.0; 		
		double m22h = 3.73;
		double m33h = 3.73;
		double drag = 0.0295;
		double thrust = 3.09e-7;
		double rpmMax = 700.0;
		double swayPerTurn = 1.01;
		double heavePerTurn = 1.01;
		double pitchRate = 0.1;
		double headingRate = (maxSpeed/turnRadius) * 0.25;
		return new MotionParameters(maxSpeed, minSpeed, maxPitch, turnRadius, 
				m22h, m33h, drag, thrust, rpmMax, 
				swayPerTurn, heavePerTurn, pitchRate, headingRate);
	}
	
	
	/*
	 * Read motion properties from java properties file. Format is [prefix].key = value. Keys are
	 * motion.speed.max = maximum speed in m/s
	 * motion.speed.min = min speed in m/s
	 * motion.speed.m22h = total mass m22 / m11
	 * motion.speed.m33h = total mass m33 / m11
	 * motion.speed.drag = 0.5 * rho * A * Cd / m11
	 * motion.speed.thrust = rho * K0 / m11
	 * motion.pitch.max.deg = maximum pitch in degrees
	 * motion.pitch.rate.deg = maximum pitch rate in deg/s
	 * motion.turn.radius = turning radius in meters (fixed at all speeds)
	 * motion.heading.rate.deg = maximum heading rate change in deg/s^2 (default value is 25% of implied max turn rate)
	 */
	public static MotionParameters fromProperties(Properties props, String prefix) {
		double maxSpeed = Double.parseDouble((props.getProperty(join(prefix, "motion.speed.max"), "5.0")));
		double minSpeed = Double.parseDouble((props.getProperty(join(prefix, "motion.speed.min"), "1.0")));
		double maxPitch = Double.parseDouble((props.getProperty(join(prefix, "motion.pitch.max.deg"), "10.0")));
		double turnRadius = Double.parseDouble((props.getProperty(join(prefix, "motion.turn.radius"), "60.0")));
		double m22h = Double.parseDouble((props.getProperty(join(prefix, "motion.speed.m22h"), "3.73")));
		double m33h = Double.parseDouble((props.getProperty(join(prefix, "motion.speed.m33h"), "3.73")));
		double drag = Double.parseDouble((props.getProperty(join(prefix, "motion.speed.drag"), "0.0295")));
		double thrust = Double.parseDouble((props.getProperty(join(prefix, "motion.speed.thrust"), "3.54e-7")));
		double rpmMax = Double.parseDouble((props.getProperty(join(prefix, "motion.speed.rpmMax"), "700")));
		double swayPerTurn = Double.parseDouble((props.getProperty(join(prefix, "motion.turn.sway"), "1.01")));
		double heavePerTurn = Double.parseDouble((props.getProperty(join(prefix, "motion.turn.heave"), "1.01")));
		double pitchRate = Double.parseDouble((props.getProperty(join(prefix, "motion.pitch.rate.deg"), "2.9")));
		double headingRate = (maxSpeed/turnRadius) * 0.25;
		headingRate = Double.parseDouble((props.getProperty(join(prefix, "motion.heading.rate.deg"), String.valueOf(Math.toDegrees(headingRate)) )));
		
		
		return new MotionParameters(maxSpeed, minSpeed, maxPitch, turnRadius,
				m22h, m33h, drag, thrust, rpmMax,
				swayPerTurn, heavePerTurn, pitchRate, headingRate);
	}
	
	   
    /*
     * Read motion properties from json node.  Simple number props:
     * maxSpeed : 
     * minSpeed :
     * maxPitch :
     * turnRadius :
     * speedRate :
     * pitchRate :
     * headingRate :
     */
    public static MotionParameters fromJson(JsonObject o) {        
        double maxSpeed = 5.0;
        double minSpeed = 1.0;
        double maxPitch = 10.0;
        double turnRadius = 60.0;    
		double m22h = 1.82;
		double m33h = 1.82;
		double drag = 0.0295;
		double thrust = 3.54e-7;
		double rpmMax = 700;
		double swayPerTurn = 1.01;
		double heavePerTurn = 1.01;
        double pitchRate  = 0.5;
        double headingRate = 1.0;
        if (o.containsKey("maxSpeed"))
            maxSpeed = o.getJsonNumber("maxSpeed").doubleValue(); 
        if (o.containsKey("minSpeed"))
            minSpeed = o.getJsonNumber("minSpeed").doubleValue();
        if (o.containsKey("maxPitch"))
            maxPitch = o.getJsonNumber("maxPitch").doubleValue();
        if (o.containsKey("turnRadius"))
            turnRadius = o.getJsonNumber("turnRadius").doubleValue();
        if (o.containsKey("m22h"))
            m22h = o.getJsonNumber("m22h").doubleValue();
        if (o.containsKey("m33h"))
            m33h = o.getJsonNumber("m33h").doubleValue();
        if (o.containsKey("drag"))
            drag = o.getJsonNumber("drag").doubleValue();
        if (o.containsKey("thrust"))
            thrust = o.getJsonNumber("thrust").doubleValue();
        if (o.containsKey("rpmMax"))
        	rpmMax = o.getJsonNumber("rpmMax").doubleValue();
        if (o.containsKey("swayPerTurn"))
        	swayPerTurn = o.getJsonNumber("swayPerTurn").doubleValue();
        if (o.containsKey("heavePerTurn"))
        	heavePerTurn = o.getJsonNumber("heavePerTurn").doubleValue();
        if (o.containsKey("pitchRate"))
            pitchRate = o.getJsonNumber("pitchRate").doubleValue();        
        headingRate = (maxSpeed/turnRadius) * 0.25;
        if (o.containsKey("headingRate"))
            headingRate = o.getJsonNumber("headingRate").doubleValue();               
		return new MotionParameters(maxSpeed, minSpeed, maxPitch, turnRadius,
				m22h, m33h, drag, thrust, rpmMax,
				swayPerTurn, heavePerTurn,
				pitchRate, headingRate);
    }
	
    	
	protected MotionParameters(double maxSpeed, double minSpeed, double maxPitch, double turnRadius, 
			double m22h, double m33h, double drag, double thrust, double rpmMax,
			double swayPerTurn, double heavePerTurn,
			double pitchRate, double headingRate)
	{
		ConfigurationException.check("Min speed", minSpeed, 0.1, maxSpeed);
	    ConfigurationException.check("Max speed", maxSpeed, minSpeed, 6.0);	    	   	    	   
	    ConfigurationException.check("Turn radius", turnRadius, maxSpeed/(2.0*Math.PI), 100.0);
	    ConfigurationException.check("Max pitch", maxPitch, 5.0, 88.0);	        
	    ConfigurationException.check("Heading tracking rate", headingRate, 1e-4, maxSpeed/turnRadius);
        ConfigurationException.check("Pitch tracking rate", pitchRate, 1e-4, Math.PI);
        ConfigurationException.check("m22h mass", m22h, 0, 10);
        ConfigurationException.check("m33h mass", m33h,0, 10);
        ConfigurationException.check("Semi-dimensional drag", drag, 0, 0.1);
        ConfigurationException.check("Semi-dimensional thrust", thrust, 1e-8, 1e-5);  
        ConfigurationException.check("Max RPM", rpmMax, 0, 1000);
		this.maxSpeed = maxSpeed;
		this.minSpeed = minSpeed;
		this.maxPitch = maxPitch;
		this.turnRadius = turnRadius;
		this.m22h = m22h;
		this.m33h = m33h;
		this.drag = drag;
		this.thrust = thrust;
		this.rpmMax = rpmMax;
		this.swayPerTurn = swayPerTurn;
		this.heavePerTurn = heavePerTurn;
		this.pitchRate = pitchRate;
		this.headingRate = headingRate;	    
	}
	
	
	protected double maxSpeed;
	protected double minSpeed;
	protected double maxPitch;
	protected double turnRadius;	
	protected double m22h;
	protected double m33h;
	protected double drag;
	protected double thrust;
	protected double rpmMax;
	protected double swayPerTurn;
	protected double heavePerTurn;
	protected double pitchRate;
	protected double headingRate;
	
	
	public double getMaxSpeed() {
		return maxSpeed;
	}
	public void setMaxSpeed(double maxSpeed) {
		this.maxSpeed = maxSpeed;
	}
	public double getMinSpeed() {
		return minSpeed;
	}
	public void setMinSpeed(double minSpeed) {
		this.minSpeed = minSpeed;
	}
	public double getMaxPitch() {
		return maxPitch;
	}
	public void setMaxPitch(double maxPitch) {
		this.maxPitch = maxPitch;
	}
	public double getTurnRadius() {
		return turnRadius;
	}
	public void setTurnRadius(double turnRadius) {
		this.turnRadius = turnRadius;
	}
	public double getM22h() {
		return m22h;
	}


	public void setM22h(double m22h) {
		this.m22h = m22h;
	}


	public double getM33h() {
		return m33h;
	}


	public void setM33h(double m33h) {
		this.m33h = m33h;
	}


	public double getDrag() {
		return drag;
	}


	public void setDrag(double drag) {
		this.drag = drag;
	}


	public double getThrust() {
		return thrust;
	}


	public void setThrust(double thrust) {
		this.thrust = thrust;
	}

	public double getRpmMax() {
		return rpmMax;
	}


	public void setRpmMax(double rpmMax) {
		this.rpmMax = rpmMax;
	}


	public double getSwayPerTurn() {
		return swayPerTurn;
	}


	public void setSwayPerTurn(double swayPerTurn) {
		this.swayPerTurn = swayPerTurn;
	}


	public double getHeavePerTurn() {
		return heavePerTurn;
	}


	public void setHeavePerTurn(double heavePerTurn) {
		this.heavePerTurn = heavePerTurn;
	}


	public double getPitchRate() {
		return pitchRate;
	}
	public void setPitchRate(double pitchRate) {
		this.pitchRate = pitchRate;
	}
	public double getHeadingRate() {
		return headingRate;
	}
	public void setHeadingRate(double headingRate) {
		this.headingRate = headingRate;
	}
	
		
	protected static String join(String s1, String s2) {
	    if (s1 == null || s1.length() == 0)
	        return s2;
	    if (s2 == null || s2.length() == 0)
	        return s1;
		String s = s1 +"." + s2;
		return s.replaceAll("\\.+", ".");		
	}
	
	public static void main(String[] args) {
		String s1 = "foo....";
		String s2 = "...bar..";
		System.out.println(join(s1,s2));

		Properties props = new Properties();
		props.setProperty("red.motion.speed.max", "1.5");
		System.out.println("Read property: " + props.getProperty("red.motion.speed.max"));
		System.out.println("Read property: " + props.getProperty(join("red", "motion.speed.max")));
		MotionParameters mp = MotionParameters.fromProperties(props, "red");
		System.out.println("Max speed is now " + mp.getMaxSpeed());		
	}		
}
