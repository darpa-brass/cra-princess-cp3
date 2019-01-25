package com.cra.sim.sensor;

import java.util.Random;

import com.cra.princess.simulation.RandomManager;
import com.cra.princess.simulation.TimeManager;

/*
 * Normally distributed white noise
 */
public class WhiteNoise {
    protected Random generator;
    protected double baseSigma;
    protected long lastTime;
    protected double state; // only store this in case we are asked for the noise multiple times per update
    
    
    public WhiteNoise(double baseSigma) {
        generator = RandomManager.getGenerator();
        this.baseSigma = baseSigma;
        lastTime = 0L;
        state = 0;
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
                
        state = baseSigma * generator.nextGaussian();        
        return state;
    }
}
