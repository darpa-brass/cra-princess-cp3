package com.cra.princess.simulation;

import java.util.ArrayList;
import java.util.List;

import javax.json.JsonArray;
import javax.json.JsonObject;
import javax.json.JsonValue;

public class BottomObjectStore implements JsonConfigurable {		
	LtpGeodetics geo;
	protected final List<double[]> nothing = new ArrayList<double[]>();
	protected List<double[]> object = new ArrayList<double[]>();	
	
	public static final BottomObjectStore nullStore = new BottomObjectStore() {						
		@Override 
		public List<double[]> getNearby(double lat0, double lon0, double depth0, double range) {
			return nothing;
		}
	};
	
	public BottomObjectStore() {		
	}
	
	/**
	 * Return a list of northEastDown arrays of RELATIVE northing/easting/downs to objects.
	 * Only objects inside the 2*range x 2*range x 2*range AABB are returned.
	 * @param lat0 -- location of observer
	 * @param lon0 -- location of observer
	 * @param depth0 -- location of observer
	 * @param range -- range of interesting objects
	 * @return List of 3-vectors northing/easting/down from (lat0, lon0, depth0) to objects
	 * in range
	 */
	public List<double[]> getNearby(double lat0, double lon0, double depth0, double range) {
		if (geo == null)
			return nothing;
		double[] ne0 = geo.getNorthingEasting(lat0, lon0);
		double depth = World.bathymetrySource.depth(lat0, lon0);
		ArrayList<double[]> close = new ArrayList<double[]>();
		for (double[] ne : object) {		
			if (Math.abs(ne[0] - ne0[0]) < range 
					&& Math.abs(ne[1] - ne0[1]) < range 
					&& Math.abs(depth - depth0) < range) {
				close.add(new double[] {ne[0] - ne0[0], ne[1] - ne0[1], depth- depth0});
			}
		}
		return close;
	}
	
	public void add(double lat, double lon) {	
		if (geo == null) {
    		geo = new LtpGeodetics(lat, lon);
    	}
		object.add(geo.getNorthingEasting(lat, lon));
	}
	
    @Override
    public void configure(JsonObject config) {    	    	
    	if (config.containsKey("objects")) {
    		JsonArray jarray = config.getJsonArray("objects");
    		for (JsonValue jval : jarray) {
    			JsonObject jo = (JsonObject) jval;            
    			
    			double lat = jo.getJsonNumber("lat").doubleValue();
    			double lon = jo.getJsonNumber("lon").doubleValue();            
    			add(lat, lon);
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
