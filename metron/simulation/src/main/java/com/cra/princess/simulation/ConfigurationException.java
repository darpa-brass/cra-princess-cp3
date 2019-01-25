package com.cra.princess.simulation;

public class ConfigurationException extends RuntimeException {

    /**
     * 
     */
    private static final long serialVersionUID = -6989886325946727660L;
    
    public ConfigurationException(String what) {
      super(what);
    }
    
	
	public static void check(String name, double value, double min, double max) throws ConfigurationException {
		if (value < min || value > max)
			throw new ConfigurationException(String.format("%s parameter = %g must be in the range [%g, %g]", name ,value, min, max));
	}
	
}
