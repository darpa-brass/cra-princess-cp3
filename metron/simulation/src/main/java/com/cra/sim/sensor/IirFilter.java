package com.cra.sim.sensor;


public class IirFilter {

    public static IirFilter ButterworthLowpass(double cutoff) {
        double[] a = new double[]{};
        double[] b = new double[]{};
        // TODO scale by cutoff.
        // TODO handle multirate inputs? VERY HARD
        return new IirFilter(a,b);
    }
    
    protected double[] a; // weights of old outputs (AR part). Note we assume the first coefficient of 1 is OMITTED
    protected double[] b; // weights of old samples (MA part or denominator part)
    protected Ring sample; 
    protected Ring output; 
    
    public IirFilter(double[] a, double[] b) {
        this.a = a;
        this.b = b;
        sample = new Ring(b.length);
        output = new Ring(a.length);
    }
    
    public double observe(double x) {
        sample.put(x);
        double xs = convolve(sample, b);
        double ys = convolve(output, a);
        double yn = -ys + xs;
        output.put(yn);
        return yn;
    }
    
    public double get() {
        return output.get(0);
    }
    
    protected double convolve(Ring r, double[] w) {
        double x=0;
        for (int i=0; i<w.length; i++) {
            x += w[i]*r.get(-i);
        }
        return x;
    }
    
    
    protected class Ring {
        protected double[] x;
        protected int cursor; // location of last written value
        
        public Ring(int N) {
            x = new double[N];
            cursor = 0;            
        }
        
        double get(int i) {
            return x[loc(i)];
        }
        
        void put(double val) {
            cursor = (cursor + 1) % x.length;
            x[cursor] = val;            
        }
        
        int loc(int i) {
            int loc = (cursor+i) % x.length;
            if (loc < 0)
                loc += (Math.abs(loc)/x.length + 1) * x.length;
            return loc;
        }           
    }
}
