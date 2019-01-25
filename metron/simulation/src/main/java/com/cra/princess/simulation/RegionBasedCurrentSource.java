package com.cra.princess.simulation;

import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.List;

import javax.json.JsonArray;
import javax.json.JsonObject;
import javax.json.JsonValue;

public class RegionBasedCurrentSource implements CurrentSource, JsonConfigurable {
    private class RectangularCurrent {
        Rectangle2D where;
        Point2D current;
    }
    private List<RectangularCurrent> rectangles = new ArrayList<>();

    @Override
    public Point2D current(double lat, double lon, double depth) {
        RectangularCurrent ans = null;
        for (RectangularCurrent rect : rectangles) {
            if (rect.where.contains(new Point2D.Double(lon, lat))) {
                ans = rect;
            }
        }
        if (ans == null) {
            return new Point2D.Double();
        }
        return ans.current;
    }

    @Override
    public void configure(JsonObject config) {
        JsonArray regions = config.getJsonArray("regions");
        for (JsonValue tmp : regions) {
            JsonObject region = (JsonObject) tmp;
            RectangularCurrent rect = new RectangularCurrent();
            
            double wLon = region.getJsonNumber("wLon").doubleValue();
            double sLat = region.getJsonNumber("sLat").doubleValue();
            double eLon = region.getJsonNumber("eLon").doubleValue();
            double nLat = region.getJsonNumber("nLat").doubleValue();
            
            rect.where = new Rectangle2D.Double(wLon, sLat, eLon - wLon, nLat - sLat);
            
            Point2D vel = new Point2D.Double();
            vel.setLocation(region.getJsonNumber("vE").doubleValue(), region.getJsonNumber("vN").doubleValue());
            
            rect.current = vel;
            
            rectangles.add(rect);
        }
    }
}
