package com.cra.princess.pathplanner;

import javax.swing.*;
import java.awt.*;
import java.awt.Color;
import java.awt.image.BufferedImage;
import java.util.List;
import java.util.stream.Collectors;

public class QuickView extends JFrame
{
    public static final Dimension DEFAULT_SIZE = new Dimension(1280, 720);
    private JLabel imageLabel;
    private final Dimension size;

    public QuickView(FlightPlan plan, String pathType){
        this(plan, pathType, DEFAULT_SIZE);
    }

    public QuickView(FlightPlan plan, String pathType, Dimension size){
        this.size = size;
        BufferedImage image = createImage(plan, size, 25, pathType);
        ImageIcon imageIcon = new ImageIcon(image);
        imageLabel = new JLabel(imageIcon);
        imageLabel.setIcon(imageIcon);
        setLayout(new FlowLayout());
        setSize(size.width, size.height);
        add(imageLabel);
        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    public void update(final FlightPlan plan, final String flightPathType)
    {
        SwingUtilities.invokeLater(() -> {
            BufferedImage image = createImage(plan, size, 25, flightPathType);
            ImageIcon imageIcon = new ImageIcon(image);
            imageLabel.setIcon(imageIcon);
            repaint();
        });
    }

    public static void display(FlightPlan flightPlan)
    {
        display(flightPlan, DEFAULT_SIZE);
    }

    public static void display(final FlightPlan flightPlan, final Dimension size){
        SwingUtilities.invokeLater(() -> {
            BufferedImage image = createImage(flightPlan, size, 25, "??");
            ImageIcon imageIcon = new ImageIcon(image);
            JLabel imageLabel = new JLabel();
            imageLabel.setIcon(imageIcon);
            JFrame frame = new JFrame();
            frame.setLayout(new FlowLayout());
            frame.setSize(size.width, size.height);
            frame.add(imageLabel);
            frame.pack();
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);
        });
    }

    public static Point toScreen(Point p, Bounds bounds, Dimension imageSize, double ratio, int margin){
        double x = (p.getX() - bounds.getMinX()) * ratio;
        double y = (p.getY() - bounds.getMinY()) * ratio;
        y = imageSize.getHeight() - y;
        return new Point(x + margin, y + margin);
    }

    public static double scalingRatio(Bounds bounds, Dimension imageSize){
        double flightAspectRatio = bounds.getWidth() / bounds.getHeight();
        double imageAspectRatio = imageSize.getWidth() / imageSize.getHeight();
        if(flightAspectRatio < imageAspectRatio){
            // flight is taller than image
            // scale so that flight is the full height
            return imageSize.height / bounds.getHeight();

        } else {
            // flight is wider than image
            // scale so flight is the full width
            return imageSize.width / bounds.getWidth();
        }
    }

    public static List<Point> toImage(List<Point> points, Bounds bounds, Dimension imageSize, double scale, int margin)
    {
        return points.stream().map(point -> toScreen(point, bounds, imageSize, scale, margin)).collect(Collectors.toList());
    }

    public static List<String> labels(List<Point> points){
        return points.stream().map(Point::toString).collect(Collectors.toList());
    }

    public static void draw(FlightPath flightPath, Bounds bounds,  Graphics2D g, Dimension imageSize, double scale, int margin)
    {
        List<Point> imagePoints = toImage(flightPath.getPoints(), bounds, imageSize, scale, margin);
        List<String> labels = labels(flightPath.getPoints());
        draw(imagePoints, labels, g, false, Color.green);
    }

    public static void draw(Polygon polygon, Bounds bounds,  Graphics2D g, Dimension imageSize, double scale, int margin)
    {
        List<Point> imagePoints = toImage(polygon.getPoints(), bounds, imageSize, scale, margin);
        List<String> labels = labels(polygon.getPoints());
        draw(imagePoints, labels, g, true, Color.red);
    }

    public static void draw(List<Point> points, List<String> labels, Graphics2D g, boolean isClosed, Color color)
    {
        if(points.size() != labels.size()){
            throw new IllegalArgumentException("Points and labels should be the same size");
        }

        if(points.isEmpty()){
            return;
        }

        g.setColor(color);

        Point last = null;
        for(int i = 0; i < points.size(); ++i){
            Point point = points.get(i);
            String label = labels.get(i);
            if(last == null){
                g.drawString(label, (int)point.getX(), (int)point.getY());
                last = point;
                continue;
            }

            g.drawString(label, (int)point.getX(), (int)point.getY());
            g.drawLine((int)last.getX(), (int)last.getY(), (int)point.getX(), (int)point.getY());
            last = point;
        }

        if(isClosed){
            Point p1 = points.get(0);
            Point p2 = points.get(points.size() - 1);
            g.drawLine((int)p1.getX(), (int)p1.getY(), (int)p2.getX(), (int)p2.getY());
        }
    }

    public static BufferedImage createImage(FlightPlan flightPlan, Dimension imageSize, int margin, String pathType){
        Polygon area = flightPlan.getArea();
        FlightPath path = flightPlan.getFlightPath();
        Bounds bounds = area.getBounds().expand(1.5);
        double scale = scalingRatio(bounds, imageSize);
        BufferedImage image = new BufferedImage(imageSize.width + 2 * margin, imageSize.height + 2 * margin, BufferedImage.TYPE_3BYTE_BGR);
        Graphics2D g = image.createGraphics();
        draw(area, bounds, g, imageSize, scale, margin);
        draw(path, bounds, g, imageSize, scale, margin);
        g.setColor(Color.green);
        g.drawString("Flight Path Type: " + pathType, 25, image.getHeight() - 25);
        g.setColor(Color.cyan);
        VehicleModel vehicleModel = flightPlan.getVehicleModel();
        Point startLocation = vehicleModel.getStartLocation();
        Point startLocationScreen = toScreen(vehicleModel.getStartLocation(), bounds, imageSize, scale, margin);
        g.drawString("Start Location: " + startLocation, (int)startLocationScreen.getX(), (int)startLocationScreen.getY() - 10);
        Point returnLocation = vehicleModel.getReturnLocation();
        Point returnLocationScreen = toScreen(returnLocation, bounds, imageSize, scale, margin);
        g.drawString("Return Location: " + returnLocation, (int)returnLocationScreen.getX(), (int)returnLocationScreen.getY() + 10);
        g.dispose();
        return image;
    }


    public static BufferedImage flightPathToImage(Dimension imageSize, FlightPath flightPath){
        int margin = 25;

        Bounds bounds = flightPath.getBounds();

        double flightAspectRatio = bounds.getWidth() / bounds.getHeight();
        double imageAspectRatio = imageSize.getWidth() / imageSize.getHeight();
        final double ratio;
        if(flightAspectRatio < imageAspectRatio){
            // flight is taller than image
            // scale so that flight is the full height
            ratio = imageSize.height / bounds.getHeight();

        } else {
            // flight is wider than image
            // scale so flight is the full width
            ratio = imageSize.width / bounds.getWidth();
        }

        BufferedImage image = new BufferedImage(imageSize.width + 2 * margin, imageSize.height + 2 * margin, BufferedImage.TYPE_3BYTE_BGR);
        Graphics g = image.createGraphics();
        g.setColor(Color.green);
        Point last = null;
        for(Point p: flightPath.getPoints()){
            if(last == null){
                last = toScreen(p, bounds, imageSize, ratio, margin);
                g.drawString(p.toString(), (int)last.getX(), (int)last.getY());
                System.out.println(String.format("%s => %s", p.toString(), last.toString()));
                continue;
            }

            Point curr = toScreen(p, bounds, imageSize, ratio, margin);
            System.out.println(String.format("%s => %s", p.toString(), curr.toString()));
            g.drawString(p.toString(), (int)curr.getX(), (int)curr.getY());
            g.drawLine((int)last.getX(), (int)last.getY(), (int)curr.getX(), (int)curr.getY());
            last = curr;
        }
        g.dispose();
        return image;
    }

}
