package com.cra.princess.simulation;

import java.util.Random;

import javax.json.JsonObject;

public class RandomManager implements JsonConfigurable {
    protected static Random seedSource = new Random(0L);
    
    
    public static Random getGenerator() {
        return new Random(seedSource.nextLong());
    }


    @Override
    public void configure(JsonObject o) {     
        if (o.containsKey("seed")) {
            seedSource = new Random(o.getJsonNumber("seed").longValue());
        } else {
            seedSource = new Random(0L);
        }
    }
}
