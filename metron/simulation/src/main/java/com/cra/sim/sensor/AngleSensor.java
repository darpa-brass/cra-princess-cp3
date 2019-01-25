package com.cra.sim.sensor;

public class AngleSensor {
    
    protected RandomWalk biasWalk;
    protected LowPassFilter biasFilter;
    protected double bias;
    protected WhiteNoise sampleNoise;
    
    public AngleSensor(double fixedBias, double biasDev, double biasTimescale, double noiseDev, double biasCutoff) {
        biasWalk = new RandomWalk(biasTimescale, biasDev);
        biasFilter = new LowPassFilter(biasCutoff);
        bias = fixedBias;
        sampleNoise = new WhiteNoise(noiseDev);                
    }
    
    public double observe(double trueValue) {
        double b = biasFilter.observe(biasWalk.update()) + bias;
        double w = sampleNoise.update();
        return trueValue + b + w;
    }
}
