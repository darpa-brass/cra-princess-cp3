package com.cra.princess.metron.viewer.view;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Stroke;
import java.awt.event.*;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

import javax.swing.*;

import com.cra.princess.metron.remus.state.TransformedRemusDvlData;
import com.cra.princess.metron.viewer.controller.RemusViewerController;
import com.cra.princess.metron.viewer.model.components.*;
import org.apache.log4j.Logger;

import com.cra.princess.metron.remus.state.RemusDvlData;
import com.cra.princess.metron.remus.state.RemusVehicleState;
import com.cra.princess.metron.viewer.model.ScenarioFileReader;
import com.metsci.dynamic.simple.AffineTransform;


/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Oct 10, 2016<br>
 * <br>
 * Copyright 2016 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class RemusTrackPanel extends JPanel implements MouseWheelListener, MouseListener, MouseMotionListener, KeyListener {
	private static final long serialVersionUID = 1L;

	private static final double R = 6371008.8; // Radius of the Earth in meters
	private static final Color OCEAN_BLUE = new Color(153, 204, 255);

	private static Logger LOG = Logger.getLogger(RemusTrackPanel.class.getName());

	private static int PANEL_WIDTH = 800;
	private static int PANEL_HEIGHT = 400;

	private RemusViewerController controller = null;

	// Map extents: min/max lat and lon
	// MXR 24-JAN-2017: note that these values were selected based on data contained in REMUS simulator scenario file.
	// Find the min and max lat and lon values in the scenario and set these accordingly.
	// They may need some fine tuning to get things to render perfectly.
	// These values may need to be updated if the base scenario file (used by the Metron scenario generator) changes.
	public static double MIN_LON = -0.008;
	public static double MAX_LON = 0.008;
	public static double MIN_LAT = 0.008;
	public static double MAX_LAT = -0.008;

	private List<Location> remusTrack = null;
	private List<Location> dvlSensorTrack = null;
	private List<Location> transformedDvlSensorTrack = null;
	private List<Location> kalmanFilterTrack = null;

	private boolean showRemusTrack = true;
	private boolean showDvlSensorTrack = true;
	private boolean showTransformedDvlSensorTrack = true;
	private boolean showKalmanFilterTrack = true;
	private boolean showPerturbationAreas = true;
	private boolean showSearchArea = true;
	private boolean showOriginLocation = true;
	private boolean showDestinationLocation = true;

	private ScenarioFileReader scenarioFileReader = null;

	private long scenarioStart = -1L;
	private long lastDvlTimestamp = 0L;
	private double lastDvlLat = 0.0;
	private double lastDvlLon = 0.0;

	private long lastTransformedDvlTimestamp = 0L;
	private double lastTransformedDvlLat = 0.0;
	private double lastTransformedDvlLon = 0.0;

	private int zoomLevel = 0;
	public static final int MIN_ZOOM_LEVEL = -19;
	public static final int MAX_ZOOM_LEVEL = 19;
	public double lonOffset = -0.008;
	public double latOffset = 0.008;
	public double startPanX = 0.0;
	public double startPanY = 0.0;

	private int fadeSteps = 20;

	public RemusTrackPanel(RemusViewerController controller) {
		super();

		this.controller = controller;

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);

		this.setBackground(OCEAN_BLUE);

		this.remusTrack = new CopyOnWriteArrayList<Location>();
		this.dvlSensorTrack = new CopyOnWriteArrayList<Location>();
		this.transformedDvlSensorTrack = new CopyOnWriteArrayList<Location>();
		this.kalmanFilterTrack = new CopyOnWriteArrayList<Location>();

		this.addMouseWheelListener(this);
		this.addMouseListener(this);
		this.addMouseMotionListener(this);
		this.addKeyListener(this);
		this.setFocusable(true);
	}

	public void setScenarioFileReader(ScenarioFileReader scenarioFileReader) {
		this.scenarioFileReader = scenarioFileReader;

		// Initialize the scenario view
		this.lastDvlTimestamp = 0L;
		this.lastDvlLat = this.scenarioFileReader.getRemusOrigin().getLatitude();
		this.lastDvlLon = this.scenarioFileReader.getRemusOrigin().getLongitude();
		this.lastTransformedDvlTimestamp = 0L;
		this.lastTransformedDvlLat = this.scenarioFileReader.getRemusOrigin().getLatitude();
		this.lastTransformedDvlLon = this.scenarioFileReader.getRemusOrigin().getLongitude();
		this.remusTrack.clear();
		this.dvlSensorTrack.clear();
		this.transformedDvlSensorTrack.clear();
		this.kalmanFilterTrack.clear();
		this.zoomLevel = 0;

		repaint();
	}

	public void updateGroundTruthTrack(RemusVehicleState vehicleState) {
		double lat = vehicleState.getTrueLatitude();
		double lon = vehicleState.getTrueLongitude();

		this.remusTrack.add(new Location(lat, lon, 0));

		repaint();
	}

	public void updateDvlSensorTrack(RemusDvlData dvlDataUpdateMessage) {
		long dvlTimestamp = dvlDataUpdateMessage.getTimestamp();
		if (this.lastDvlTimestamp == 0L) {
			this.lastDvlTimestamp = dvlTimestamp;
		}

//		double vE = dvlDataUpdateMessage.getvE();
//		double vN = dvlDataUpdateMessage.getvN();

		double roll = Math.toRadians(dvlDataUpdateMessage.getRoll());
		double pitch = Math.toRadians(dvlDataUpdateMessage.getPitch());
		double yaw = Math.toRadians(dvlDataUpdateMessage.getHeading());
		AffineTransform bodyToWorld = new AffineTransform(0, 0, 0, roll, pitch, yaw);
		double[] bodyVelocity = new double[] {dvlDataUpdateMessage.getSurge(), dvlDataUpdateMessage.getSway(), dvlDataUpdateMessage.getHeave()};
		double[] worldVelocity = bodyToWorld.transform(bodyVelocity);
		double vE = worldVelocity[1];
		double vN = worldVelocity[0];

		double heading = Math.atan2(vE, vN); // This function returns the angle, in radians, between -pi and pi.
		heading *= 180.0 / Math.PI; // Convert from radians to degrees. Now heading is in the range [-180, 180]
		if (heading < 0.0) {
			heading += 360.0; // Get rid of negative headings.
		}

		// It's more accurate to use surge instead of vE and vN
		// Leaving old calculations in case we roll back
		double speed = Math.sqrt((vE * vE) + (vN * vN));
		long timeMs = dvlTimestamp - this.lastDvlTimestamp;
		double distanceM = speed * (timeMs / 1000.0);
		//double distanceM = dvlDataUpdateMessage.getSurge() * (timeMs / 1000.0);

		double lat1 = Math.toRadians(this.lastDvlLat); // Current lat point converted to radians
		double lon1 = Math.toRadians(this.lastDvlLon); // Current lon point converted to radians
		double brng = Math.toRadians(heading);

		double lat2 = Math.asin(Math.sin(lat1) * Math.cos(distanceM / R) + Math.cos(lat1) * Math.sin(distanceM / R) * Math.cos(brng));
		double lon2 = lon1 + Math.atan2(Math.sin(brng) * Math.sin(distanceM / R) * Math.cos(lat1), Math.cos(distanceM / R) - Math.sin(lat1) * Math.sin(lat2));

		this.lastDvlTimestamp = dvlTimestamp;
		this.lastDvlLat = Math.toDegrees(lat2);
		this.lastDvlLon = Math.toDegrees(lon2);

		this.dvlSensorTrack.add(new Location(this.lastDvlLat, this.lastDvlLon, 0));

		repaint();
	}

	public void updateTransformedDvlSensorTrack(TransformedRemusDvlData dvlDataUpdateMessage) {
		long dvlTimestamp = dvlDataUpdateMessage.getTimestamp();
		if (this.lastTransformedDvlTimestamp == 0L) {
			this.lastTransformedDvlTimestamp = dvlTimestamp;
		}

//		double vE = dvlDataUpdateMessage.getvE();
//		double vN = dvlDataUpdateMessage.getvN();

		double roll = Math.toRadians(dvlDataUpdateMessage.getRoll());
		double pitch = Math.toRadians(dvlDataUpdateMessage.getPitch());
		double yaw = Math.toRadians(dvlDataUpdateMessage.getHeading());
		AffineTransform bodyToWorld = new AffineTransform(0, 0, 0, roll, pitch, yaw);
		double[] bodyVelocity = new double[] {dvlDataUpdateMessage.getSurge(), dvlDataUpdateMessage.getSway(), dvlDataUpdateMessage.getHeave()};
		double[] worldVelocity = bodyToWorld.transform(bodyVelocity);
		double vE = worldVelocity[1];
		double vN = worldVelocity[0];

		double heading = Math.atan2(vE, vN); // This function returns the angle, in radians, between -pi and pi.
		heading *= 180.0 / Math.PI; // Convert from radians to degrees. Now heading is in the range [-180, 180]
		if (heading < 0.0) {
			heading += 360.0; // Get rid of negative headings.
		}

		double speed = Math.sqrt((vE * vE) + (vN * vN));
		long timeMs = dvlTimestamp - this.lastTransformedDvlTimestamp;
		double distanceM = speed * (timeMs / 1000.0);
		//double distanceM = dvlDataUpdateMessage.getSurge() * (timeMs / 1000.0);

		double lat1 = Math.toRadians(this.lastTransformedDvlLat); // Current lat point converted to radians
		double lon1 = Math.toRadians(this.lastTransformedDvlLon); // Current lon point converted to radians
		double brng = Math.toRadians(heading);

		double lat2 = Math.asin(Math.sin(lat1) * Math.cos(distanceM / R) + Math.cos(lat1) * Math.sin(distanceM / R) * Math.cos(brng));
		double lon2 = lon1 + Math.atan2(Math.sin(brng) * Math.sin(distanceM / R) * Math.cos(lat1), Math.cos(distanceM / R) - Math.sin(lat1) * Math.sin(lat2));

		this.lastTransformedDvlTimestamp = dvlTimestamp;
		this.lastTransformedDvlLat = Math.toDegrees(lat2);
		this.lastTransformedDvlLon = Math.toDegrees(lon2);

		this.transformedDvlSensorTrack.add(new Location(this.lastTransformedDvlLat, this.lastTransformedDvlLon, 0));

		repaint();
	}

	public void updateKalmanFilterTrack(com.cra.princess.messaging.types.Location location) {
		double lat = this.scenarioFileReader.getRemusOrigin().getLatitude() + location.lat();
		double lon = this.scenarioFileReader.getRemusOrigin().getLongitude() + location.lon();

		this.kalmanFilterTrack.add(new Location(lat, lon, 0));

		repaint();
	}

	public void zoomIn() {
		this.zoomLevel++;
		if (zoomLevel > MAX_ZOOM_LEVEL) {
			this.zoomLevel = MAX_ZOOM_LEVEL;
		}

		repaint();
	}

	public void zoomOut() {
		this.zoomLevel--;
		if (zoomLevel < MIN_ZOOM_LEVEL) {
			this.zoomLevel = MIN_ZOOM_LEVEL;
		}

		repaint();
	}

	public void setShowRemusTrack(boolean show) {
		this.showRemusTrack = show;

		repaint();
	}

	public void setShowDvlSensorTrack(boolean show) {
		this.showDvlSensorTrack = show;

		repaint();
	}

	public void setShowTransformedDvlSensorTrack(boolean show) {
		this.showTransformedDvlSensorTrack = show;

		repaint();
	}

	public void setShowKalmanFilterTrack(boolean show) {
		this.showKalmanFilterTrack = show;

		repaint();
	}

	public void setShowPerturbationAreas(boolean show) {
		this.showPerturbationAreas = show;

		repaint();
	}

	public void setShowSearchArea(boolean show) {
		this.showSearchArea = show;

		repaint();
	}

	public void setShowOriginLocation(boolean show) {
		this.showOriginLocation = show;

		repaint();
	}

	public void setShowDestinationLocation(boolean show) {
		this.showDestinationLocation = show;

		repaint();
	}

	@Override
	public void paint(Graphics g) {
		super.paint( g );
		Graphics2D g2d = (Graphics2D)g;

		if (this.scenarioFileReader != null && this.controller != null) {
			// NOTE: calling order of these functions affects rendering

			if (this.showPerturbationAreas) {
				drawPerturbationAreas(g2d);
			}

			if (this.showSearchArea) {
				drawSearchArea(g2d);
			}

			if (this.showRemusTrack) {
				drawGroundTruthTrack(g2d);
			}

			if (this.showDvlSensorTrack) {
				drawDvlSensorTrack(g2d);
			}

			if (this.showTransformedDvlSensorTrack) {
				drawTransformedDvlSensorTrack(g2d);
			}

			if (this.showKalmanFilterTrack) {
				drawKalmanFilterTrack(g2d);
			}

			if (this.showOriginLocation) {
				Origin origin = this.scenarioFileReader.getRemusOrigin();
				if (origin != null) {
					g2d.setColor(this.controller.getOriginColor());
					origin.draw(this, this.zoomLevel, g2d, lonOffset, latOffset);
				}
			}

			if (this.showDestinationLocation) {
				Destination destination = this.scenarioFileReader.getRemusDestination();
				if (destination != null) {
					g2d.setColor(this.controller.getDestinationColor());
					destination.draw(this, this.zoomLevel, g2d, lonOffset, latOffset);
				}
			}

			SearchObject searchObject = this.scenarioFileReader.getSearchObjectLocation();
			if (searchObject != null) {
				g2d.setColor(Color.BLACK);
				searchObject.draw(this, this.zoomLevel, g2d, lonOffset, latOffset);
			}
		}
	}

	/* Draw perturbing areas of current */
	private void drawPerturbationAreas(Graphics2D g2d) {
		// Draw perturbing areas of current
		g2d.setColor(this.controller.getCurrentBorderColor());

		Stroke currentStroke = g2d.getStroke();
		g2d.setStroke(new BasicStroke(3));

		List<PerturbingCurrent> pcs = scenarioFileReader.getPerturbingCurrents();

		for (PerturbingCurrent pc : pcs) {
			pc.draw(this, this.zoomLevel, g2d, lonOffset, latOffset);
		}

		g2d.setStroke(currentStroke);
		g2d.setColor(Color.BLACK);
	}

	/* Draw search area */
	private void drawSearchArea(Graphics2D g2d) {
		// Draw search area
		g2d.setColor(this.controller.getSearchAreaBorderColor());

		Stroke currentStroke = g2d.getStroke();
		g2d.setStroke(new BasicStroke(3));

		SearchArea searchArea = this.scenarioFileReader.getSearchArea();

		if (searchArea != null) {
			searchArea.draw(this, this.zoomLevel, g2d, lonOffset, latOffset);
		}

		g2d.setStroke(currentStroke);
		g2d.setColor(Color.BLACK);
	}

	public void setFadeSteps(int steps) {
		this.fadeSteps = (steps < 0) ? 1 : steps;
	}

	/* Draw the REMUS track as shown by the ground truth data */
	private void drawGroundTruthTrack(Graphics2D g2d) {
		// Draw REMUS track from ground truth data
		drawTrack(this.controller.getGroundTruthTrackColor(), this.remusTrack, g2d);
	}

	/* Draw the REMUS track as shown by the DVL sensor data */
	private void drawDvlSensorTrack(Graphics2D g2d) {
		// Draw REMUS track from DVL sensor data
		drawTrack(this.controller.getDvlSensorTrackColor(), this.dvlSensorTrack, g2d);
	}

	/* Draw the REMUS track as shown by the Transformed DVL sensor data */
	private void drawTransformedDvlSensorTrack(Graphics2D g2d) {
		// Draw REMUS track from Transformed DVL sensor data
		drawTrack(this.controller.getTransformedDvlSensorTrackColor(), this.transformedDvlSensorTrack, g2d);
	}

	/* Draw the REMUS track as shown by the Kalman Filter data */
	private void drawKalmanFilterTrack(Graphics2D g2d) {
		// Draw REMUS track from Kalman Filter data
		drawTrack(this.controller.getKalmanFilterTrackColor(), this.kalmanFilterTrack, g2d);
	}

	/* Draw a REMUS track */
	private void drawTrack(Color trackColor, List<Location> track, Graphics2D g2d) {
		// Draw REMUS track from Kalman Filter data
		int startingIndex = (track.size()-fadeSteps-1 < 0) ? 0 : track.size()-fadeSteps-1;
		int endingIndex = (track.size()-1 < 0) ? 0 : track.size()-1;
		int alphaFade = 0;
		for (Location location : track.subList(startingIndex, endingIndex)) {
			Color fading = new Color(trackColor.getRed(), trackColor.getGreen(), trackColor.getBlue(), (alphaFade > 255) ? 255 : alphaFade);
			g2d.setColor(fading);
			Point p = ScenarioComponent.scaleToDisplay(this, this.zoomLevel, location.getLatitude(), location.getLongitude(), lonOffset, latOffset);
			g2d.fillOval(p.x, p.y, 3, 3);
			alphaFade += (int)Math.ceil((190.0/(double)(endingIndex-startingIndex)));
		}
		g2d.setColor(Color.BLACK);
	}

	public void mouseWheelMoved(MouseWheelEvent e) {
		int wheelRotation = e.getWheelRotation();
		if (wheelRotation > 0) {
			zoomOut();
			repaint();
		} else {
			zoomIn();
			repaint();
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
		Double[] lonlat = ScenarioComponent.displayToLonLat(this, this.zoomLevel, e.getY(), e.getX(), lonOffset, latOffset);
		this.startPanX = lonlat[0];
		this.startPanY = lonlat[1];
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		Double[] lonlat = ScenarioComponent.displayToLonLat(this, this.zoomLevel, e.getY(), e.getX(), lonOffset, latOffset);
		this.startPanX = lonlat[0];
		this.startPanY = lonlat[1];
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		Double[] lonlat = ScenarioComponent.displayToLonLat(this, this.zoomLevel, ((e.getY() - this.startPanY)), ((e.getX() - this.startPanX)), this.lonOffset, this.latOffset);
		this.lonOffset -= lonlat[0]/10;
		this.latOffset -= lonlat[1]/10;
		repaint();
	}

	@Override
	public void keyPressed(KeyEvent e) {
		int key = e.getKeyCode();
		if (key == KeyEvent.VK_LEFT) {
			this.lonOffset = lonOffset - (((RemusTrackPanel.MAX_LON - RemusTrackPanel.MIN_LON)/100));
		}
		if (key == KeyEvent.VK_RIGHT) {
			this.lonOffset = lonOffset + (((RemusTrackPanel.MAX_LON - RemusTrackPanel.MIN_LON)/100));
		}
		if (key == KeyEvent.VK_UP) {
			this.latOffset = latOffset + (((RemusTrackPanel.MAX_LON - RemusTrackPanel.MIN_LON)/100));
		}
		if (key == KeyEvent.VK_DOWN) {
			this.latOffset = latOffset - (((RemusTrackPanel.MAX_LON - RemusTrackPanel.MIN_LON)/100));
		}
		if ((key == KeyEvent.VK_MINUS) && ((e.getModifiers() & KeyEvent.CTRL_MASK) != 0)) {
			this.zoomLevel--;
		}
		if ((key == KeyEvent.VK_EQUALS) && ((e.getModifiers() & KeyEvent.CTRL_MASK) != 0)) {
			this.zoomLevel++;
		}
		repaint();
	}

	@Override
	public void keyReleased(KeyEvent e) {}
	@Override
	public void keyTyped(KeyEvent e) {}
	@Override
	public void mouseEntered(MouseEvent e) {}
	@Override
	public void mouseExited(MouseEvent e) {}
	@Override
	public void mouseMoved(MouseEvent e) {}
	@Override
	public void mouseClicked(MouseEvent e) {}
}