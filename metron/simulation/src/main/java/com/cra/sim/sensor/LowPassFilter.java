package com.cra.sim.sensor;

import com.cra.princess.simulation.TimeManager;

public class LowPassFilter {
    protected double state;
    protected double lambda; // s-plane cut-off.
    protected long lastTime;
    
    public LowPassFilter(double lambda) {
        lastTime  = 0L;
        state = 0;
        this.lambda = lambda;
    }
    
    public double observe(double obs) {
        long now = TimeManager.now();
        if (lastTime == 0L) {
            lastTime = now;
            return state;
        }        
        double dt = ((double) now - lastTime)*1e-3;
        if (dt <= 0)
            return state;
        lastTime = now;
        
        double a = Math.exp(-lambda*dt);
        state = a*state + (1.0-a)*obs;        
        return state;
    }
}
