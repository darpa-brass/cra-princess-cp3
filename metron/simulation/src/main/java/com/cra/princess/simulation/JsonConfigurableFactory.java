package com.cra.princess.simulation;

import javax.json.JsonObject;

public class JsonConfigurableFactory {
    public JsonConfigurable construct(JsonObject config) {

        JsonConfigurable o;
        try {
            o = (JsonConfigurable) Class.forName(config.getString("type")).newInstance();
            o.configure(config.getJsonObject("config"));
        } catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
            throw new ConfigurationException("Error constructing object : " + e.getClass().getName() + " : " + e.getLocalizedMessage());
        }
        
        return o;
    }
}
