package com.cra.sim.sensor;

import java.util.Random;

import com.cra.princess.simulation.RandomManager;
import com.cra.princess.simulation.TimeManager;

/*
 * A 1D continuous random walk with a starting state of zero. 
 * The std dev of the walk steps is scaled by the interval
 * elapsed between steps.
 */
public class RandomWalk {
    protected Random generator;
    protected double state;
    protected double timescale;
    protected double baseStandardDeviation;
    protected long lastTime;
    
    
    public RandomWalk(double timescale, double baseStandardDeviation) {
        generator = RandomManager.getGenerator();
        state = 0;
        lastTime = 0L;
        this.timescale = timescale;
        this.baseStandardDeviation = baseStandardDeviation;
    }
    
    public double update() {
        long now = TimeManager.now();
        if (lastTime == 0L) {
            lastTime = now;
            return state;
        }        
        double dt = ((double) now - lastTime)*1e-3;
        if (dt <= 0)
            return state;
        lastTime = now;
        
        double sigma = Math.sqrt(dt/timescale) * baseStandardDeviation;
        state += sigma * generator.nextGaussian();        
        return state;
    }     
}
