package com.cra.princess.metron.viewer.view;

import java.awt.BorderLayout;
import java.awt.event.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.*;

import com.cra.princess.messaging.StepMessage;
import com.cra.princess.metron.MetronRemusManager;
import com.cra.princess.metron.remus.control.SimulationControlListener;
import com.cra.princess.metron.remus.control.SimulationControlMessage;
//import com.cra.princess.metron.remus.perturbation.BatteryPerturbationListener;
//import com.cra.princess.messaging.RemusBatteryPerturbation;
//import com.cra.princess.metron.remus.perturbation.RemusSensorPerturbation;
//import com.cra.princess.metron.remus.perturbation.SensorPerturbationListener;
import com.cra.princess.metron.remus.state.*;
import com.cra.princess.metron.viewer.capture.JmsTestHarnessCapture;
import com.cra.princess.metron.viewer.csv.CsvWriter;
import com.cra.princess.simulation.TimeManager;
import org.apache.log4j.Logger;

import com.cra.princess.metron.RemusManagerException;
import com.cra.princess.metron.remus.command.RemusVehicleCommand;
import com.cra.princess.metron.remus.command.VehicleCommandListener;
import com.cra.princess.metron.viewer.controller.RemusViewerController;
import com.cra.princess.metron.viewer.model.ScenarioFileReader;

import javax.json.JsonException;

import com.cra.princess.simulation.Runner;
import com.cra.princess.messaging.JmsManager;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Oct 10, 2016<br>
 * <br>
 * Copyright 2016 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

// public class RemusViewerFrame extends JFrame implements VehicleGroundTruthUpdateListener, DvlSensorUpdateListener, VehicleCommandListener, KalmanFilterOutputListener, VehiclePowerUpdateListener, SimulationControlListener, ObjectDetectionListener, RpmSensorUpdateListener, WaterSpeedSensorUpdateListener, TransformedDvlSensorUpdateListener, BatteryPerturbationListener, SensorPerturbationListener {
public class RemusViewerFrame extends JFrame implements VehicleGroundTruthUpdateListener, DvlSensorUpdateListener, VehicleCommandListener, KalmanFilterOutputListener, VehiclePowerUpdateListener, SimulationControlListener, ObjectDetectionListener, RpmSensorUpdateListener, WaterSpeedSensorUpdateListener, TransformedDvlSensorUpdateListener {
	private static final long serialVersionUID = 1L;
	private static final String APP_TITLE = "REMUS Track Viewer";

	private static final String APP_VERSION = "1.3.0";

	private static final String ABOUT_MESSAGE = "PRINCESS\n" + APP_TITLE + "\n" + "Version " + APP_VERSION + "\n" + "Charles River Analytics, Inc.\n" + "Copyright 2019";

	private static Logger LOG = Logger.getLogger(RemusViewerFrame.class.getName());

	private RemusViewerController controller = null;
	private JmsTestHarnessCapture capture = null;

	private JMenuBar menuBar = null;
	private JFrame frame = null;
	private RemusTrackPanel trackPanel = null;
	private DataViewPanel dataPanel = null;
	private JLabel timeLabel = null;
	private JPanel timePanel = null;
	private JPanel learningPanel = null;
	private JMenuItem openMenuItem = null;
	private JButton startScenario = null;
	private JButton stopScenario = null;
	private JButton pauseScenario = null;
	private JButton resumeScenario = null;
	private JScrollPane trackPanelScrollPane = null;
	private ControlPanel controlPanel = null;
	private VehicleCommandDataPanel vehicleCommandDataPanel = null;
	private PerturbationDataPanel perturbationDataPanel = null;
	private JTabbedPane tabbedPane = null;

	private ColorChooserDialog colorChooserDialog = null;

	private ScenarioFileReader scenarioFileReader = null;

	private SimpleDateFormat sdf = null;

	private File lastFileDirectory = null;

	private CsvWriter groundTruthCsvWriter = null;
	private CsvWriter dvlCsvWriter = null;
	private CsvWriter transformedDvlCsvWriter = null;

	private LegendDialog legendDialog = null;
	private PowerDialog powerDialog = null;

	private JTextField scenarioPlaybackSpeed = null;
	private JButton setPlaybackSpeed = null;

	private JTextField scenarioFadeSteps = null;
	private JButton setFadeSteps = null;

	private JCheckBoxMenuItem jmsCaptureMenuItem = null;
	private JCheckBoxMenuItem learningMenuItem = null;

	private JTextField timeStepCount = null;
	private JButton step = null;

	public RemusViewerFrame(RemusViewerController controller) {
		super();

		if (controller == null) {
			LOG.error("No controller provided.... exiting application");
			System.exit(-1);
		}

		this.controller = controller;
		this.controller.addVehicleGroundTruthUpdateListener(this);
		this.controller.addDvlSensorUpdateListener(this);
		this.controller.addTransformedDvlSensorUpdateListener(this);
		this.controller.addVehicleCommandUpdateListener(this);
		this.controller.addKalmanFilterOutputListener(this);
		this.controller.addPowerListener(this);
		this.controller.addControlListener(this);
		this.controller.addObjectDetectionListener(this);
		this.controller.addRpmSensorUpdateListener(this);
		this.controller.addWaterSpeedSensorUpdateListener(this);
		// this.controller.addBatteryPerturbationListener(this);
		// this.controller.addSensorPerturbationListener(this);

		this.groundTruthCsvWriter = new CsvWriter("groundTruthSurge");
		this.dvlCsvWriter = new CsvWriter("dvlSurge");
		this.transformedDvlCsvWriter = new CsvWriter("transformedDvlSurge");

		try {
			this.controller.start();
		}
		catch (RemusManagerException e) {
			LOG.error("Controller failed to start.... exiting application", e);
			System.exit(-1);
		}

		LOG.info("Starting " + APP_TITLE + " v" + APP_VERSION);

		this.sdf = new SimpleDateFormat("EEE MMM dd HH:mm:ss z yyyy");

		this.frame = this;

		this.colorChooserDialog = new ColorChooserDialog(controller, this);

		this.setTitle(APP_TITLE);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		this.trackPanel = new RemusTrackPanel(controller);
		this.trackPanelScrollPane = new JScrollPane(this.trackPanel);
		this.add(this.trackPanelScrollPane, BorderLayout.CENTER);

		this.menuBar = new JMenuBar();
		createFileMenu();
		createToolMenu();
		createViewMenu();
		createHelpMenu();
		this.setJMenuBar(this.menuBar);

		this.addWindowListener(new java.awt.event.WindowAdapter() {
			@Override
			public void windowClosing(java.awt.event.WindowEvent windowEvent) {
				exitApp();
			}
		});

		this.learningPanel = new JPanel();
		this.timeStepCount = new JTextField(3);
		this.timeStepCount.setText("1000");
		this.step = new JButton("Step >");
		this.step.setEnabled(true);
		this.step.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				long timeSteps = Long.parseLong(timeStepCount.getText());
				sendStepMessage(timeSteps);
			}
		});
		this.learningPanel.add(this.timeStepCount);
		this.learningPanel.add(this.step);
		this.learningPanel.setVisible(false);

		this.timePanel = new JPanel();
		this.timeLabel = new JLabel("No time data available");
		this.startScenario = new JButton("Start");
		this.startScenario.setEnabled(false);
		this.startScenario.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				startScenario.setEnabled(false);
				stopScenario.setEnabled(true);
				pauseScenario.setEnabled(true);
				resumeScenario.setEnabled(false);
				setPlaybackSpeed.setEnabled(true);
				setFadeSteps.setEnabled(true);
				openMenuItem.setEnabled(false);
				if (jmsCaptureMenuItem.isSelected()) {
					capture = new JmsTestHarnessCapture(controller);
					capture.start();
					jmsCaptureMenuItem.setEnabled(false);
				}
				runScenario(false);
			}
		});
		this.stopScenario = new JButton("Stop");
		this.stopScenario.setEnabled(false);
		this.stopScenario.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (jmsCaptureMenuItem.isSelected()) {
					capture.stopCapture();
					capture = null;
					jmsCaptureMenuItem.setSelected(false);
					jmsCaptureMenuItem.setEnabled(true);
				}

				MetronRemusManager mrm = MetronRemusManager.getInstance();
				try {
					mrm.sendSimulationEnded();
				} catch (RemusManagerException ex) {
					LOG.error(ex.getMessage(), ex);
				}
				openMenuItem.setEnabled(true);
				startScenario.setEnabled(false);
				stopScenario.setEnabled(false);
				pauseScenario.setEnabled(false);
				resumeScenario.setEnabled(false);
				setPlaybackSpeed.setEnabled(false);
				setFadeSteps.setEnabled(true);
			}
		});
		this.pauseScenario = new JButton("Pause");
		this.pauseScenario.setEnabled(false);
		this.pauseScenario.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				MetronRemusManager mrm = MetronRemusManager.getInstance();
				try {
					mrm.sendSimulationPause();
				} catch (RemusManagerException ex) {
					LOG.error(ex.getMessage(), ex);
				}
				pauseScenario.setEnabled(false);
				resumeScenario.setEnabled(true);
			}
		});
		this.resumeScenario = new JButton("Resume");
		this.resumeScenario.setEnabled(false);
		this.resumeScenario.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				MetronRemusManager mrm = MetronRemusManager.getInstance();
				try {
					mrm.sendSimulationResume();
				} catch (RemusManagerException ex) {
					LOG.error(ex.getMessage(), ex);
				}
				resumeScenario.setEnabled(false);
				pauseScenario.setEnabled(true);
			}
		});
		this.scenarioPlaybackSpeed = new JTextField(3);
		this.scenarioPlaybackSpeed.setText("1.0");
		this.setPlaybackSpeed = new JButton("Set Speed");
		this.setPlaybackSpeed.setEnabled(false);
		this.setPlaybackSpeed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				MetronRemusManager mrm = MetronRemusManager.getInstance();
				try {
					mrm.sendScenarioPlaybackSpeed(Double.parseDouble(scenarioPlaybackSpeed.getText()));
				} catch (RemusManagerException ex) {
					LOG.error(ex.getMessage(), ex);
				}
				pauseScenario.setEnabled(true);
				resumeScenario.setEnabled(false);
			}
		});

		this.scenarioFadeSteps = new JTextField(3);
		this.scenarioFadeSteps.setText("20");
		this.setFadeSteps = new JButton("Set Fade Steps");
		this.setFadeSteps.setEnabled(true);
		this.setFadeSteps.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				trackPanel.setFadeSteps(Integer.parseInt(scenarioFadeSteps.getText()));
				pauseScenario.setEnabled(true);
				resumeScenario.setEnabled(false);
			}
		});

		this.timePanel.add(this.startScenario);
		this.timePanel.add(this.pauseScenario);
		this.timePanel.add(this.timeLabel);
		this.timePanel.add(this.resumeScenario);
		this.timePanel.add(this.stopScenario);
		this.timePanel.add(this.scenarioPlaybackSpeed);
		this.timePanel.add(this.setPlaybackSpeed);
		this.timePanel.add(this.scenarioFadeSteps);
		this.timePanel.add(this.setFadeSteps);
		this.timePanel.setVisible(true);
		this.add(this.timePanel, BorderLayout.NORTH);

		this.dataPanel = new DataViewPanel(controller, this.colorChooserDialog, this.trackPanel);
		this.vehicleCommandDataPanel = new VehicleCommandDataPanel();
		this.perturbationDataPanel = new PerturbationDataPanel();
		this.controlPanel = new ControlPanel(this.controller);
		this.tabbedPane = new JTabbedPane();
		this.tabbedPane.add("Data", this.dataPanel);
		this.tabbedPane.add("Commands", this.vehicleCommandDataPanel);
		// this.tabbedPane.add("Events", this.perturbationDataPanel);
		this.tabbedPane.add("Send", this.controlPanel);
		this.add(this.tabbedPane, BorderLayout.EAST);

		this.pack();
		this.setVisible(true);

		this.colorChooserDialog.setLocationRelativeTo(this);

		this.lastFileDirectory = new File(System.getProperty("user.home"));

		this.legendDialog = new LegendDialog(this.controller, this.colorChooserDialog, this.trackPanel, this);
		this.legendDialog.setLocationRelativeTo(this);

		this.powerDialog = new PowerDialog(this);
		this.powerDialog.setLocationRelativeTo(this);
	}

	// TODO: ugly hack but just git 'er done!
	public LegendDialog getLegendDialog() {
		return legendDialog;
	}

	/*
	 * Shut down the application
	 */
	private void exitApp() {
		this.controller.stop();
		if (this.capture != null) {
			this.capture.stopCapture();
		}

		if (this.groundTruthCsvWriter != null) {
			this.groundTruthCsvWriter.close();
		}
		if (this.dvlCsvWriter != null) {
			this.dvlCsvWriter.close();
		}
		if (this.transformedDvlCsvWriter != null) {
			this.transformedDvlCsvWriter.close();
		}

		this.colorChooserDialog.dispose();
		this.legendDialog.dispose();
		this.powerDialog.dispose();
		this.frame.dispose();

		System.exit(0);
	}

	/*
	 * Select the scenario file to view
	 */
	private void chooseScenarioFile() {
		File scenarioFile = null;

		JFileChooser fc = new JFileChooser();
		fc.setDialogTitle("Open Scenario File");
		fc.setCurrentDirectory(this.lastFileDirectory);
		fc.setFileSelectionMode(JFileChooser.FILES_ONLY);
		int result = fc.showOpenDialog(this);
		if (result == JFileChooser.APPROVE_OPTION) {
			this.lastFileDirectory = fc.getCurrentDirectory();
			scenarioFile = fc.getSelectedFile();

			LOG.info("Loading scenario file: " + scenarioFile.getAbsolutePath());

			try {
				this.scenarioFileReader = this.controller.getScenarioFileReader(scenarioFile);

				this.setTitle(APP_TITLE + " [" + scenarioFile.getAbsolutePath() + "]");
				this.timeLabel.setText("No time data available");
				this.trackPanel.setScenarioFileReader(this.scenarioFileReader);
				this.dataPanel.reset();
				this.vehicleCommandDataPanel.reset();
				this.perturbationDataPanel.reset();

				if (this.learningMenuItem.isSelected()) {
					runScenario(true);
				}
				else {
					this.startScenario.setEnabled(true);
					this.stopScenario.setEnabled(false);
					this.scenarioPlaybackSpeed.setText(this.scenarioFileReader.getScenarioPlaybackSpeed().toString());
				}
			} catch (IOException e) {
				LOG.warn(e);
				JOptionPane.showMessageDialog(this, "The selected scenario file cannot be loaded or contains invalid content", "Invalid scenario file", JOptionPane.WARNING_MESSAGE);
			}
		}
	}

	private void createFileMenu() {
		JMenu menu = new JMenu("File");
		menuBar.add(menu);

		// File -> Open Scenario File...
		this.openMenuItem = new JMenuItem("Open Scenario File...");
		this.openMenuItem.setAccelerator(KeyStroke.getKeyStroke('O', InputEvent.CTRL_DOWN_MASK));
		this.openMenuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				chooseScenarioFile();
			}
		});
		menu.add(this.openMenuItem);

		menu.addSeparator();

		// File -> Exit
		JMenuItem exitMenuItem = new JMenuItem("Exit");
		exitMenuItem.setAccelerator(KeyStroke.getKeyStroke('X', InputEvent.CTRL_DOWN_MASK));
		exitMenuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				exitApp();
			}
		});
		menu.add(exitMenuItem);
	}

	private void createToolMenu() {
		JMenu menu = new JMenu("Tool");
		menuBar.add(menu);

		// Tool -> JMS Capture Mode
		this.jmsCaptureMenuItem = new JCheckBoxMenuItem("JMS Capture Mode", false);
		this.jmsCaptureMenuItem.setAccelerator(KeyStroke.getKeyStroke('J', InputEvent.CTRL_DOWN_MASK));
		this.jmsCaptureMenuItem.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				// Do nothing; used for selection only
			}
		});
		menu.add(this.jmsCaptureMenuItem);

		// Tool -> Reinforced Learning Mode
		this.learningMenuItem = new JCheckBoxMenuItem("Reinforced Learning Mode", false);
		this.learningMenuItem.setAccelerator(KeyStroke.getKeyStroke('R', InputEvent.CTRL_DOWN_MASK));
		this.learningMenuItem.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				if (learningPanel.isVisible()) {
					frame.remove(learningPanel);
					learningPanel.setVisible(false);
					timePanel.setVisible(true);
					frame.add(timePanel, BorderLayout.NORTH);
				}
				else {
					frame.remove(timePanel);
					timePanel.setVisible(false);
					learningPanel.setVisible(true);
					frame.add(learningPanel, BorderLayout.NORTH);
				}
				frame.pack();
				frame.repaint();
			}
		});
		menu.add(this.learningMenuItem);
	}

	private void createViewMenu() {
		JMenu menu = new JMenu("View");
		menuBar.add(menu);

		// View -> Legend Dialog...
		JMenuItem legendMenuItem = new JMenuItem("Legend...");
		legendMenuItem.setAccelerator(KeyStroke.getKeyStroke('L', InputEvent.CTRL_DOWN_MASK));
		legendMenuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				legendDialog.setVisible(true);
			}
		});
		menu.add(legendMenuItem);

		// View -> Power Dialog...
		JMenuItem powerMenuItem = new JMenuItem("Power...");
		powerMenuItem.setAccelerator(KeyStroke.getKeyStroke('P', InputEvent.CTRL_DOWN_MASK));
		powerMenuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				powerDialog.setVisible(true);
			}
		});
		menu.add(powerMenuItem);

		// View -> Hide Tabs
		JCheckBoxMenuItem tabsMenuItem = new JCheckBoxMenuItem("Tabs", true);
		tabsMenuItem.setAccelerator(KeyStroke.getKeyStroke('T', InputEvent.CTRL_DOWN_MASK));
		tabsMenuItem.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				if (tabbedPane.isVisible()) {
					tabbedPane.setVisible(false);
				}
				else {
					tabbedPane.setVisible(true);
				}
			}
		});
		menu.add(tabsMenuItem);
	}

	private void createHelpMenu() {
		JMenu menu = new JMenu("Help");
		menuBar.add(menu);

		// Help -> About...
		JMenuItem menuItem = new JMenuItem("About...");
		menuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				showAbout();
			}
		});
		menu.add(menuItem);
	}

	private void showAbout() {
		JOptionPane.showMessageDialog(this.frame, ABOUT_MESSAGE, "About", JOptionPane.PLAIN_MESSAGE);
	}

	private void updateTimeDisplay(RemusVehicleState vehicleState) {
		long timestamp = vehicleState.getTimestamp();
		Date date = new Date(timestamp);
		this.timeLabel.setText(this.sdf.format(date));
	}

	@Override
	public void vehicleGroundTruthUpdate(RemusVehicleState vehicleStateUpdate) {
		updateTimeDisplay(vehicleStateUpdate);
		this.trackPanel.updateGroundTruthTrack(vehicleStateUpdate);
		this.dataPanel.updateGroundTruthTrack(vehicleStateUpdate);
		this.groundTruthCsvWriter.appendSurgeValue(vehicleStateUpdate.getTimestamp(), vehicleStateUpdate.getSurge());
	}

	@Override
	public void dvlSensorUpdate(RemusDvlData dvlDataUpdate) {
		this.trackPanel.updateDvlSensorTrack(dvlDataUpdate);
		this.dataPanel.updateDvlSensorData(dvlDataUpdate);
		this.dvlCsvWriter.appendSurgeValue(dvlDataUpdate.getTimestamp(), dvlDataUpdate.getSurge());
	}

	@Override
	public void vehicleCommandUpdate(RemusVehicleCommand vehicleCommand) {
		updateVehicleCommandData(vehicleCommand);
	}

	@Override
	public void kalmanFilterOutputUpdate(com.cra.princess.messaging.types.Location location) {
		this.trackPanel.updateKalmanFilterTrack(location);
	}

	@Override
	public void vehiclePowerUpdate(RemusPowerState powerUpdate) {
		this.dataPanel.updatePowerData(powerUpdate);
		this.powerDialog.updatePowerData(powerUpdate);
	}

	@Override
	public void controlUpdate(SimulationControlMessage controlMessage) {
		// Check to see if the simulation has ended
		if (controlMessage != null) {
			String message = controlMessage.getPlayControl();
			if (message != null && message.isEmpty() == false) {
				if (message.equals(SimulationControlMessage.CONTROL_COMMAND_STOP)) {
					MetronRemusManager mrm = MetronRemusManager.getInstance();

					openMenuItem.setEnabled(true);
					startScenario.setEnabled(false);
					stopScenario.setEnabled(false);
					pauseScenario.setEnabled(false);
					resumeScenario.setEnabled(false);
					setPlaybackSpeed.setEnabled(false);
					setFadeSteps.setEnabled(true);

					JOptionPane.showMessageDialog(this, "The scenario has ended.", "Scenario Complete", JOptionPane.INFORMATION_MESSAGE);
				}
			}
		}
	}

	@Override
	public void objectDetected(RemusObjectDetectionState objectDetectionMessage) {
		this.dataPanel.updateObjectDetection(objectDetectionMessage);
	}

	@Override
	public void rpmSensorUpdate(RemusRpmData rpmDataUpdateMessage) {
		this.dataPanel.updateRpmSensorData(rpmDataUpdateMessage);
	}

	@Override
	public void waterSpeedSensorUpdate(RemusWaterSpeedData waterSpeedDataUpdateMessage) {
		this.dataPanel.updateWaterSpeedSensorData(waterSpeedDataUpdateMessage);
	}

	@Override
	public void transformedDvlSensorUpdate(TransformedRemusDvlData transformedRemusDvlUpdate) {
		this.trackPanel.updateTransformedDvlSensorTrack(transformedRemusDvlUpdate);
		this.transformedDvlCsvWriter.appendSurgeValue(transformedRemusDvlUpdate.getTimestamp(), transformedRemusDvlUpdate.getSurge());
	}

//	@Override
//	public void batteryPerturbationUpdate(RemusBatteryPerturbation perturbation) {
//		// this.perturbationDataPanel.addPerturbation(perturbation);
//	}
//
//	@Override
//	public void sensorPerturbationUpdate(RemusSensorPerturbation perturbation) {
//		// this.perturbationDataPanel.addPerturbation(perturbation);
//	}

	private void runScenario(boolean stepped) {
		Runner runner = new Runner();
		try {
			InputStream is = new FileInputStream(this.scenarioFileReader.getScenarioFile());
			runner.load(is);
			if (stepped == true) {
				runner.runStepperMode();
			}
			else {
				runner.run();
			}

			// Cleanly shut down JmsManager when sim is over.
			TimeManager.addStepper(new TimeManager.TimeStepped() {
				@Override
				public void initialize() { }
				@Override
				public void update() { }
				@Override
				public void reset() { }
				@Override
				public void stop() {
					JmsManager.stop();
				}
			});
		} catch (FileNotFoundException e) {
			System.err.println("File not found:\n" + e.getLocalizedMessage());
		} catch (JsonException e) {
			System.err.println("JSON failed to parse:\n" + e.getLocalizedMessage());
		}
	}

	private void updateVehicleCommandData(RemusVehicleCommand vehicleCommand) {
		this.vehicleCommandDataPanel.updateVehicleCommandData(vehicleCommand);
	}

	private void sendStepMessage(long timeStep) {
		StepMessage stepMessage = new StepMessage(timeStep);
		JmsManager.sendStepMessage(stepMessage);
	}
}