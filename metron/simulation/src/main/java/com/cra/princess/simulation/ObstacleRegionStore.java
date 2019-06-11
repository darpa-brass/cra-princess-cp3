package com.cra.princess.simulation;

import java.util.ArrayList;
import java.util.List;

import javax.json.JsonArray;
import javax.json.JsonObject;
import javax.json.JsonValue;
/* Cylindrical fixed obstacles 
 * 
 * TODO random obstacle location?
 * */
public class ObstacleRegionStore implements JsonConfigurable {		
	LtpGeodetics geo;
	protected final List<double[]> nothing = new ArrayList<double[]>();
	protected List<double[]> object = new ArrayList<double[]>();
	protected ArrayList<Double> objectRadius = new ArrayList<Double>();
	
	public ObstacleRegionStore() {		
	}
	
	/**
	 * True if point is not within any object radius
	 * @param lat0 -- location of ship
	 * @param lon0 -- location of ship 
	 * @return True if no intersection, otherwise False
	 */
	public boolean isCollisionFree(double lat0, double lon0) {
		if (geo == null)
			return true;
		double[] ne0 = geo.getNorthingEasting(lat0, lon0);		
		for (int i=0; i<object.size(); i++) {
			double[] ne = object.get(i);
			double distance = Math.hypot(ne[0] - ne0[0], ne[1] - ne0[1]) - objectRadius.get(i);
			if (distance <= 0)
				return false;
		}
		return true;
	}
	
	public void add(double lat, double lon, double radius) {	
		if (geo == null) {
    		geo = new LtpGeodetics(lat, lon);
    	}
		object.add(geo.getNorthingEasting(lat, lon).clone());
		objectRadius.add(radius);
	}
	
    @Override
    public void configure(JsonObject config) {    	    	
    	if (config.containsKey("obstacles")) {
    		JsonArray jarray = config.getJsonArray("obstacles");
    		for (JsonValue jval : jarray) {
    			JsonObject jo = (JsonObject) jval;            
    			
    			double lat = jo.getJsonNumber("lat").doubleValue();
    			double lon = jo.getJsonNumber("lon").doubleValue(); 
    			double radius = jo.getJsonNumber("radius").doubleValue();
    			add(lat, lon, radius);
    		}
        }
    }

	public void setOrigin(JsonObject originConfig) {
		double lat = originConfig.getJsonNumber("lat").doubleValue();
		double lon = originConfig.getJsonNumber("lon").doubleValue();
		LtpGeodetics newGeo = new LtpGeodetics(lat, lon);		
		for (double[] ne : object) {
			double[] ll = geo.getLatLon(ne[0], ne[1]);
			double[] neNew = newGeo.getNorthingEasting(ll[0], ll[1]);
			ne[0] = neNew[0];
			ne[1] = neNew[1];
		}
		geo = newGeo;
	}
}
