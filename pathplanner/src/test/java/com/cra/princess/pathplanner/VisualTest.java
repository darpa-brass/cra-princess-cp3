package com.cra.princess.pathplanner;

import com.cra.princess.pathplanner.generators.*;

import javax.swing.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;

public class VisualTest implements Runnable
{
    final VehicleModel vehicleModel;
    final SensorModel sensorModel;
    List<Polygon> polygons = new ArrayList<>();
    List<FlightPlanGenerator> generators = new ArrayList<>();
    QuickView view;

    int polygonIndex = 0;
    int generatorIndex = 0;
    double angle = 0.0;

    public VisualTest(VehicleModel vehicleModel, SensorModel sensorModel){
        this.vehicleModel = vehicleModel;
        this.sensorModel = sensorModel;
        addPolygons();
        addGenerators();
        FlightPlan fp = getFlightPlan();
        view = new QuickView(fp, getGenerator().toString());
        view.addKeyListener(new KeyAdapter()
        {
            @Override
            public void keyReleased(KeyEvent e)
            {
                switch(e.getKeyCode()){
                    case KeyEvent.VK_UP:
                        generatorIndex++;
                        break;
                    case KeyEvent.VK_DOWN:
                        generatorIndex--;
                        break;
                    case KeyEvent.VK_LEFT:
                        polygonIndex--;
                        break;
                    case KeyEvent.VK_RIGHT:
                        polygonIndex++;
                        break;
                }

                generatorIndex = (generatorIndex + generators.size()) % generators.size();
                polygonIndex = (polygonIndex + polygons.size()) % polygons.size();
            }
        });
    }

    @Override
    public void run()
    {
        while(true){
            SwingUtilities.invokeLater(() ->
            {
                FlightPlanGenerator generator = getGenerator();
                if(generator instanceof RotatingGenerator){
                    ((RotatingGenerator) generator).setAngleInRadians(angle);
                }
                view.update(getFlightPlan(), generator.toString());
                angle += 0.01;
            });

            try
            {
                Thread.sleep(100);
            } catch (InterruptedException e){
                break;
            }
        }
    }

    private FlightPlan getFlightPlan(){
        return getGenerator().generate(vehicleModel, sensorModel, getPolygon());
    }

    private FlightPlanGenerator getGenerator(){
        return generators.get(generatorIndex);
    }

    private Polygon getPolygon(){
        return polygons.get(polygonIndex);
    }

    private void addPolygons(){
        /*
        {
            List<Point> points = new ArrayList<>();
            points.add(new Point(10, 10));
            points.add(new Point(50, 70));
            points.add(new Point(500, 100));
            points.add(new Point(550, 10));
            polygons.add(new Polygon(points));
        }
        */

        {
            List<Point> points = new ArrayList<>();
            points.add(new Point(10, 10));
            points.add(new Point(50, 110));
            points.add(new Point(300, 200));
            points.add(new Point(350, 10));
            polygons.add(new Polygon(points));
        }

        {
            List<Point> points = new ArrayList<>();
            points.add(new Point(10, 10));
            points.add(new Point(10, 100));
            points.add(new Point(100, 100));
            points.add(new Point(100, 10));
            polygons.add(new Polygon(points));
        }

        {
            List<Point> points = new ArrayList<>();
            points.add(new Point(0, 0));
            points.add(new Point(-20, 50));
            points.add(new Point(0, 100));
            points.add(new Point(50, 120));
            points.add(new Point(100, 100));
            points.add(new Point(120, 50));
            points.add(new Point(100, 0));
            points.add(new Point(50, -20));
            polygons.add(new Polygon(points));
        }

        {
            List<Point> points = new ArrayList<>();
            points.add(new Point(0, -200));
            points.add(new Point(-20, -100));
            points.add(new Point(-30, -90));
            points.add(new Point(-100, 0));
            points.add(new Point(-120, 200));
            points.add(new Point(-20, 100));
            points.add(new Point(0, 50));
            points.add(new Point(120, 120));
            points.add(new Point(90, -120));
            polygons.add(new Polygon(points));
        }
    }

    private void addGenerators()
    {
        generators.add(new Lawnmower());
        generators.add(new BoundingGenerator(new Lawnmower()));
        generators.add(new Spiral());
        generators.add(new BoundingGenerator(new Spiral()));
        generators.add(new OffsetPolygon());

        generators.add(new RotatingGenerator(new Lawnmower(), 0.0));
        generators.add(new RotatingGenerator(new Spiral(), 0.0));

        generators.add(new RotatingGenerator(new BoundingGenerator(new Lawnmower()), 0.0));
        generators.add(new RotatingGenerator(new BoundingGenerator(new Spiral()), 0.0));
    }

    public static void main(String[] args) throws InterruptedException{
        final VehicleModel vehicleModel = new VehicleModel(new Point(0,0), new Point(0,0), 10);
        final SensorModel sensorModel = new SensorModel(45 * (Math.PI / 180.0));
        VisualTest visualTest = new VisualTest(vehicleModel, sensorModel);
        visualTest.run();
    }
}
