package com.cra.sim.sensor;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.simulation.ConfigurationException;

public class RangeDependentObjectDetectionModel extends ObjectDetectionModel {
	protected double Pd0;
    protected double Pd1;
	protected double range0;
	protected double range1;

    @Override
	public boolean detect(double[] op) {
		double range = Math.max(Math.min(op[0], range1), range0);		
		double t = (range-range0)/(range1-range0);
		double Pd = t*Pd1 + (1.0-t)*Pd0;					
		return (generator.nextDouble() < Pd);			
	}

	@Override
	public void configure(JsonObject o) {
		setPd0(o.getJsonNumber("Pd0").doubleValue());
        setPd1(o.getJsonNumber("Pd1").doubleValue());
        setRange0(o.getJsonNumber("range0").doubleValue());
        setRange1(o.getJsonNumber("range1").doubleValue());
        checkRanges();
	}

    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("type", RangeDependentObjectDetectionModel.class.getName())
            .add("config",
                    Json.createObjectBuilder()
                    .add("Pd0", Pd0)
                    .add("Pd1", Pd1)
                    .add("range0", range0)
                    .add("range1", range1)
                    .build())
            .build();
    }

    public double getPd0() {
        return Pd0;
    }

    public void setPd0(double pd0) {
        ConfigurationException.check("Pd0", Pd0, 0, 1);
        Pd0 = pd0;
    }

    public double getPd1() {
        ConfigurationException.check("Pd1", Pd1, 0, 1);
        return Pd1;
    }

    public void setPd1(double pd1) {
        Pd1 = pd1;
    }

    public double getRange0() {
        return range0;
    }

    public void setRange0(double range0) {
        ConfigurationException.check("range0", range0, 0, 1e3);
        this.range0 = range0;
    }

    public double getRange1() {
        return range1;
    }

    public void setRange1(double range1) {
        ConfigurationException.check("range1", range1, 0, 1e3);
        this.range1 = range1;
    }
    
    private void checkRanges() {
        if (Math.abs(range0 - range1) < 1e-6) {
            throw new ConfigurationException(String.format("Ranges %g and %g are too close together.", range0, range1));
        }
        
        if (range0 > range1) {
            double tmp = range0;
            range0 = range1;
            range1 = tmp;
            tmp = Pd0;
            Pd0 = Pd1;
            Pd1 = tmp;
        }
    }

    @Override
    public String toString() {
        return "RangeDependentObjectDetectionModel [Pd0=" + Pd0 + ", Pd1=" + Pd1 + ", range0=" + range0 + ", range1=" + range1 + "]";
    }
}
