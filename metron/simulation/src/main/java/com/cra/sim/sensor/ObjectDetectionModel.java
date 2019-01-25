package com.cra.sim.sensor;

import java.util.Random;

import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonEncodable;
import com.cra.princess.simulation.RandomManager;

public abstract class ObjectDetectionModel implements JsonConfigurable, JsonEncodable {

    protected Random generator;

    public abstract boolean detect(double[] op);

    public double[] dirty(double[] op) {
        return op;
    }

    public ObjectDetectionModel() {
        generator = RandomManager.getGenerator();
    }

}