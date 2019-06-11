package com.cra.princess.simulation;

import javax.json.JsonNumber;
import javax.json.JsonObject;

public class JsonConfigurableFactory {
    public JsonConfigurable construct(JsonObject config) {
    	if (config == null) {
    		throw new ConfigurationException("Missing required configuration section");
    	}
        JsonConfigurable o;
        try {
        	String typename = config.getString("type");
            o = (JsonConfigurable) Class.forName(typename).newInstance();
            JsonObject configObj = config.getJsonObject("config");
            o.configure(configObj);
        } catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
            throw new ConfigurationException("Error constructing object : " + e.getClass().getName() + " : " + e.getLocalizedMessage());
        }
        
        return o;
    }
    
    public JsonConfigurable construct(JsonObject config, String context) {
    	try {
    		return construct(config);
    	} catch (ConfigurationException e) {
    		throw new ConfigurationException("Missing required configuration section for " + context);
    	}
    }
    
    public static double getDouble(JsonObject config, String key) {
    	JsonNumber num = config.getJsonNumber(key);
    	if (num == null) {
    		throw new ConfigurationException("Missing valid number for key " + key);
    	}
    	return num.doubleValue();    	
    }
    
    public static double getDouble(JsonObject config, String key, double def) {
    	try {
    		return getDouble(config, key);
    	} catch (ConfigurationException e) {
    		return def;
    	}
    }
}
