package com.cra.princess.simulation;

import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.List;

import javax.json.JsonArray;
import javax.json.JsonObject;
import javax.json.JsonValue;

public class RegionBasedBathymetrySource implements BathymetrySource, JsonConfigurable {
    private class RectangularBathy {
        Rectangle2D where;
        double depth;
    }
    private double defaultDepth = Double.MAX_VALUE;
    private List<RectangularBathy> rectangles = new ArrayList<>();

    @Override
    public double depth(double lat, double lon) {
    	RectangularBathy ans = null;
        for (RectangularBathy rect : rectangles) {
            if (rect.where.contains(new Point2D.Double(lon, lat))) {
                ans = rect;
            }
        }
        if (ans == null) {
            return defaultDepth;
        }
        return ans.depth;
    }

    @Override
    public void configure(JsonObject config) {
    	defaultDepth = config.getJsonNumber("defaultDepth").doubleValue();
    	if (config.containsKey("regions")) {
    		JsonArray regions = config.getJsonArray("regions");
    		for (JsonValue tmp : regions) {
    			JsonObject region = (JsonObject) tmp;
    			RectangularBathy rect = new RectangularBathy();
            
    			double wLon = region.getJsonNumber("wLon").doubleValue();
    			double sLat = region.getJsonNumber("sLat").doubleValue();
    			double eLon = region.getJsonNumber("eLon").doubleValue();
    			double nLat = region.getJsonNumber("nLat").doubleValue();
            
    			rect.where = new Rectangle2D.Double(wLon, sLat, eLon - wLon, nLat - sLat);            
    			rect.depth = region.getJsonNumber("depth").doubleValue();
            
    			rectangles.add(rect);
    		}
        }
    }
}
