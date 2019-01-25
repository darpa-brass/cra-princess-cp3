package com.cra.princess.pathplanner;

import org.apache.log4j.Logger;

import javax.swing.SwingUtilities;
import java.util.ArrayList;
import java.util.List;

import static com.cra.princess.pathplanner.FlightPlanFactory.Generator.LAWNMOWER;
import static com.cra.princess.pathplanner.FlightPlanFactory.Generator.SPIRAL;

/**
 * PRINCESS API for the FlightPlanFactory
 *
 */
public class PathPlanner {
    private static final Logger LOG = Logger.getLogger(PathPlanner.class.getName());

    private static final double EARTH_RADIUS = 6371008.8; // m WGS84 mean radius
    private static final double LAT_DEGREE_METER =  180.0 / (Math.PI * EARTH_RADIUS);

    private double originLatDeg = 0.0;
    private double originLonDeg = 0.0;

    private VehicleModel vehicleModel = null;
    private SensorModel sensorModel = null;
    private Polygon searchArea = null;
    private FlightPlanFactory flightPlanFactory = null;
    private List<Point> searchAreaBounds = null;
    private FlightPlan flightPlan = null;

    public static FlightPlanFactory.Generator LAWNMOWER_PATTERN = LAWNMOWER;
    public static FlightPlanFactory.Generator SPIRAL_PATTERN = SPIRAL;

    public PathPlanner(double searchAreaLowerLeftLat, double searchAreaLowerLeftLon,
                       double searchAreaUpperRightLat, double searchAreaUpperRightLon,
                       double searchDepthMeters, double sensorFieldOfViewRadians, FlightPlanFactory.Generator searchPattern,
                       boolean boundedBySearchArea, double rotation) {
        this.originLatDeg = searchAreaLowerLeftLat;
        this.originLonDeg = searchAreaLowerLeftLon;

        Point origin = convert(this.originLatDeg, this.originLonDeg);
        Point ur = convert(searchAreaUpperRightLat, searchAreaUpperRightLon);

        this.vehicleModel = new VehicleModel(origin, origin, searchDepthMeters);
        this.sensorModel = new SensorModel(sensorFieldOfViewRadians);

        // Expand into search area rectangle
        this.searchAreaBounds = new ArrayList<Point>();
        this.searchAreaBounds.add(origin);
        this.searchAreaBounds.add(new Point(origin.getX(), ur.getY()));
        this.searchAreaBounds.add(ur);
        this.searchAreaBounds.add(new Point(ur.getX(), origin.getY()));
        this.searchAreaBounds.add(origin);

        this.searchArea = new Polygon(this.searchAreaBounds);

        FlightPlanFactory.Settings settings = new FlightPlanFactory.Settings(searchPattern, rotation, boundedBySearchArea);

        this.flightPlanFactory = new FlightPlanFactory(settings);
    }

    public List<Waypoint> plan() {
        List<Waypoint> waypoints = new ArrayList<Waypoint>();

        this.flightPlan = flightPlanFactory.generate(this.vehicleModel, this.sensorModel, this.searchArea);
        FlightPath path = flightPlan.getFlightPath();
        List<Point> pathPoints = path.getPoints();
        for (Point point : pathPoints) {
            Waypoint wp = convert(point);
            waypoints.add(wp);
        }

        return waypoints;
    }

    public FlightPlan getFlightPlan() {
        return flightPlan;
    }

    private Point convert(double lat, double lon) {
        double lonDegreeMeter = LAT_DEGREE_METER / Math.cos(Math.toRadians(this.originLatDeg));

        double x = (lon - this.originLonDeg) / lonDegreeMeter;
        double y = (lat - this.originLatDeg) / LAT_DEGREE_METER;

        LOG.debug("x = " + x + ", y = " + y);

        Point point = new Point(x,y);
        return point;
    }

    private Waypoint convert(Point point) {
        double lonDegreeMeter = LAT_DEGREE_METER / Math.cos(Math.toRadians(this.originLatDeg));
        double lat = this.originLatDeg + point.getY() * LAT_DEGREE_METER;
        double lon = this.originLonDeg + point.getX() * lonDegreeMeter;

        LOG.debug("lat = " + lat + ", lon = " + lon);

        Waypoint waypoint = new Waypoint(lat,lon);

        return waypoint;
    }

    public static void main(String[] args) {
        double searchAreaLowerLeftLat = 30.0;
        double searchAreaLowerLeftLon = -117.0;
        double searchAreaUpperRightLat = 30.001;
        double searchAreaUpperRightLon = -116.998;

        double searchDepthMeters = 20.0;
        double sensorFieldOfViewRadians = Math.toRadians(30.0);

        double rotation = 10.0;

        // Bounded Lawnmower Pattern
        PathPlanner boundedLawnmower = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
                searchAreaUpperRightLat, searchAreaUpperRightLon,
                searchDepthMeters, sensorFieldOfViewRadians,
                PathPlanner.LAWNMOWER_PATTERN,true, rotation);
        boundedLawnmower.plan();

        // Unbounded Lawnmower Pattern
        PathPlanner unboundedLawnmower = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
                searchAreaUpperRightLat, searchAreaUpperRightLon,
                searchDepthMeters, sensorFieldOfViewRadians,
                PathPlanner.LAWNMOWER_PATTERN,false, rotation);
        unboundedLawnmower.plan();

        // Bounded Spiral Pattern
        PathPlanner boundedSpiral = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
                searchAreaUpperRightLat, searchAreaUpperRightLon,
                searchDepthMeters, sensorFieldOfViewRadians,
                PathPlanner.SPIRAL_PATTERN,true, rotation);
        boundedSpiral.plan();

        // Unbounded Spiral Pattern
        PathPlanner unboundedSpiral = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
                searchAreaUpperRightLat, searchAreaUpperRightLon,
                searchDepthMeters, sensorFieldOfViewRadians,
                PathPlanner.SPIRAL_PATTERN,false, rotation);
        unboundedSpiral.plan();

        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                QuickView qv1 = new QuickView(boundedLawnmower.getFlightPlan(), "BoundingGenerator{Lawnmower}");
                QuickView qv2 = new QuickView(unboundedLawnmower.getFlightPlan(), "Lawnmower");
                QuickView qv3 = new QuickView(boundedSpiral.getFlightPlan(), "BoundingGenerator{Spiral}");
                QuickView qv4 = new QuickView(unboundedSpiral.getFlightPlan(), "Spiral");
            }
        });
    }
}
