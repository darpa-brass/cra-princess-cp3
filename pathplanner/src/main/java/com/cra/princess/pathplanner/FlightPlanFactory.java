package com.cra.princess.pathplanner;

import com.cra.princess.pathplanner.generators.*;

import java.util.ArrayList;
import java.util.List;

/**
 * The {@link FlightPlanFactory} is the primary mechanism for generating {@link FlightPlan}s. What kind of {@link FlightPlan}
 * it generates is controlled by the underlying {@link FlightPlanGenerator} which is determined by a {@link Settings}.
 * Updating the settings with a a call to {@link FlightPlanFactory#updateSettings(Settings)} will create a new underlying
 * {@link FlightPlanGenerator} to use to actually create the {@link FlightPlan}.
 *
 * NOTE: When specifying points for the Search area and the Vehicles start and return locations, all coordinates
 * should be in a local cartesian coridinate system and not latitude/longitude. The generated FlightPath will also
 * be in the local system and will need to be explicitly converted back to latitude/longitude;
 *
 * Here is a sample use
 * <pre>
 * {@code
 *  // Create a factory with the default settings
 * FlightPlanFactory factory = new FlightPlanFactory();
 *
 * // Create a model of the vehicle
 * VehicleModel vehicleModel = new VehicleModel(new Point(0.0, 0.0), new Point(0.0, 0.0), 25);
 *
 * // Create a model of the sensor
 * SensorModel sensorModel = new SensorModel(45 * (Math.PI / 180.0));
 *
 * // Specify the area to search in x/y coordinates
 * List<Point> points = Arrays.asList(new Point(0, 0), new Point(0, 60), new Point(100, 60), new Point(100, 0))
 * Polygon searchArea = new Polygon(points);
 *
 * // Generate a FlightPlan
 * FlightPlan flightPlan = factory.generate(vehicleModel, sensorModel, searchArea);
 *
 * // Decide that we actually want a spiral pattern instead of a Lawnmower
 * FlightPlanFactory.Settings.Builder builder = new FlightPlanFactory.Settings.Builder();
 * FlightPlanFactory.Settings settings1 = builder.generatorType(Generator.LAWNMOWER).build();
 *
 * // Update the factory
 * factory.updateSettings(settings1);
 *
 * // Generate a new FlightPlan
 * FlightPlan alternateFlightPlan = factory.generate(vehicleModel, sensorModel, searchArea);
 *
 *  }
 * </pre>
 *
 */
public class FlightPlanFactory implements FlightPlanGenerator
{
    /**
     * Class to specify how the {@link FlightPlanFactory} should generate a flightpath
     */
    public static class Settings
    {
        final Generator generatorType;
        final double rotation;
        final boolean bounded;

        public Settings(Generator generatorType, double rotation, boolean bounded)
        {
            this.generatorType = generatorType;
            this.rotation = rotation;
            this.bounded = bounded;
        }

        public static class Builder{
            Generator generatorType = Generator.LAWNMOWER;
            double rotation = 0.0;
            boolean bounded = true;

            public Builder generatorType(Generator generatorType)
            {
                this.generatorType = generatorType;
                return this;
            }

            public Builder rotation(double rotation)
            {
                this.rotation = rotation;
                return this;
            }

            public Builder bounded(boolean bounded)
            {
                this.bounded = bounded;
                return this;
            }

            public Settings build(){
                return new Settings(generatorType, rotation, bounded);
            }
        }
    }

    /**
     * Possible Flight Path types.
     */
    public enum Generator
    {
        LAWNMOWER,
        SPIRAL,
        OFFSET_POLYGON
    }

    private static final Settings DEFAULT_SETTINGS = new Settings.Builder().build();
    private RotatingGenerator currentGenerator;

    public FlightPlanFactory()
    {
        currentGenerator = build(DEFAULT_SETTINGS);
    }

    public FlightPlanFactory(Settings settings)
    {
        currentGenerator = build(settings);
    }

    /**
     * Update the settings that specify what type of {@link FlightPath} is generated
     * @param settings
     */
    public void updateSettings(Settings settings)
    {
        currentGenerator = build(settings);
    }

    @Override
    public FlightPlan generate(VehicleModel vehicleModel, SensorModel sensorModel, Polygon area)
    {
        FlightPlan flightPlan = currentGenerator.generate(vehicleModel, sensorModel, area);

        // Tweak the flightplan to insert the start and return location
        FlightPath path = flightPlan.getFlightPath();
        List<Point> points = new ArrayList<>(path.getPoints());
        points.add(0, vehicleModel.getStartLocation());
        points.add(vehicleModel.getReturnLocation());

        return new FlightPlan(vehicleModel, sensorModel, new FlightPath(points), area);
    }

    private static RotatingGenerator build(Settings settings)
    {
        FlightPlanGenerator generator = createBaseGenerator(settings.generatorType);
        if(settings.bounded){
            generator = new BoundingGenerator(generator);
        }
        return new RotatingGenerator(generator, settings.rotation);
    }

    private static FlightPlanGenerator createBaseGenerator(Generator generator)
    {
        switch(generator)
        {
            case LAWNMOWER:
                return new Lawnmower();
            case SPIRAL:
                return new Spiral();
            case OFFSET_POLYGON:
                return new OffsetPolygon();
        }
        return new Lawnmower();
    }
}
