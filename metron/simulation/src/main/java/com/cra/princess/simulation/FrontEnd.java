package com.cra.princess.simulation;

import java.awt.EventQueue;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Date;

import javax.json.JsonException;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import com.cra.princess.messaging.DvlMessage;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.SimulationControlMessage;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.events.EventDispatcher;

import net.miginfocom.swing.MigLayout;

public class FrontEnd implements MessageHandler<GroundTruthMessage>, TimeStepped {

    private JFrame frame;
    private JTextField txtScenariojson;
    private JButton btnBrowse;

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
        if (args.length != 0) {
            if (args.length == 1) {
                runHeadless(args[0]);                
            } else {
                printUsage("simulation");
            }
        } else {
            EventQueue.invokeLater(new Runnable() {
                public void run() {
                    try {
                        FrontEnd window = new FrontEnd();
                        window.frame.setVisible(true);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }                
            });
        }
    }
    
    public static void runHeadless(String scenarioName) {
        Runner runner = new Runner();
        try {
            InputStream is = new FileInputStream(new File(scenarioName));
            runner.load(is);

            EventDispatcher.registerConsumer(GroundTruthMessage.class, new MessageHandler<GroundTruthMessage>() {
                @Override
                public void handleMessage(GroundTruthMessage gt) {         
                        System.out.println(String.format("%s %g %g %g %g %g %g %g %g %g", new Date(TimeManager.now()), gt.trueLatitude, gt.trueLongitude, gt.trueDepth,
                                gt.vE, gt.vN, gt.vU, gt.roll, gt.pitch, gt.heading));
                }
            });

            EventDispatcher.registerConsumer(DvlMessage.class, new MessageHandler<DvlMessage>() {
                @Override
                public void handleMessage(DvlMessage meas) {
                    System.out.println(meas);
                }
            });
            
            runner.addTimeStepped(new TimeStepped() {
                @Override
                public void initialize() { }
                @Override
                public void update() { }
                @Override
                public void reset() { }
                @Override
                public void stop() {
                    JmsManager.sendSimulationControlMessage(SimulationControlMessage.stop());
                    JmsManager.stop();
                }
                
            });
            
            runner.run();
        } catch (FileNotFoundException e1) {
            System.err.println("File not found:\n" + e1.getLocalizedMessage());
        } catch (JsonException e1) {
            System.err.println("JSON failed to parse:\n" + e1.getLocalizedMessage());
        }        
    }
    
    public static void printUsage(String name) {
        System.err.format("usage: %s [scenario_file]\n", name);
        System.err.format("\tscenario_file:\tA valid JSON AUV simulator configuration. If present, run a headless simulation, exiting on completion.\n");
        System.err.format("Run an AUV simulation, publishing state to JMS.\n");
    }

    final JFileChooser fc = new JFileChooser(".");
    final Runner runner = new Runner();
    private JLabel lblSimulationTime;
    private JLabel lblTime;
    private JButton btnStart;
    private JButton btnAbort;
    private JLabel lblVehiclePosition;
    private JLabel lblPosition;
    private JLabel lblVehicleSog;
    private JLabel lblSog;
    private JLabel lblVehicleDepth;
    private JLabel lblDepth;
    
    /**
     * Create the application.
     */
    public FrontEnd() {
        setup();
    }

    /**
     * Initialize the contents of the frame.
     */
    private void setup() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.getContentPane().setLayout(new MigLayout("", "[][grow][]", "[][][][][]"));
        
        JLabel lblScenarioFile = new JLabel("Scenario File");
        lblScenarioFile.setFont(new Font("Tahoma", Font.BOLD, 11));
        frame.getContentPane().add(lblScenarioFile, "cell 0 0,alignx left");
        
        txtScenariojson = new JTextField();
        frame.getContentPane().add(txtScenariojson, "cell 0 1 2 1,growx");
        txtScenariojson.setColumns(10);
        
        btnBrowse = new JButton("Browse");
        btnBrowse.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int returnVal = fc.showOpenDialog(frame);

                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    txtScenariojson.setText(fc.getSelectedFile().getAbsolutePath());
                }
            }
        });
        frame.getContentPane().add(btnBrowse, "cell 2 1,alignx right");
        
        final FrontEnd finalRef = this;
        
        btnStart = new JButton("Start");
        btnStart.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    InputStream is = new FileInputStream(new File(txtScenariojson.getText()));
                    runner.load(is);
                } catch (FileNotFoundException e1) {
                    JOptionPane.showMessageDialog(frame, "File not found:\n" + e1.getLocalizedMessage(), "File Not Found", JOptionPane.ERROR_MESSAGE);
                } catch (JsonException e1) {
                    JOptionPane.showMessageDialog(frame, "JSON failed to parse:\n" + e1.getLocalizedMessage(), "Parse Error", JOptionPane.ERROR_MESSAGE);
                }

                // Send out stop message at the end
                TimeManager.addStepper(new TimeStepped() {
                    @Override
                    public void initialize() { }
                    @Override
                    public void update() { }
                    @Override
                    public void reset() { }
                    @Override
                    public void stop() {
                        JmsManager.sendSimulationControlMessage(new SimulationControlMessage());
                    }
                });
                
                // Must add this after the above, as it shuts down JMS.
                TimeManager.addStepper(finalRef);
                
                runner.run();
                btnAbort.setEnabled(true);
                btnStart.setEnabled(false);
                btnBrowse.setEnabled(false);
            }
        });
        frame.getContentPane().add(btnStart, "cell 0 2");
        
        btnAbort = new JButton("Abort");
        btnAbort.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                TimeManager.stop();
                btnStart.setEnabled(true);
                btnAbort.setEnabled(false);
            }
        });
        frame.getContentPane().add(btnAbort, "cell 1 2");
        btnAbort.setEnabled(false);
        
        lblSimulationTime = new JLabel("Simulation Time: ");
        lblSimulationTime.setFont(new Font("Tahoma", Font.BOLD, 11));
        frame.getContentPane().add(lblSimulationTime, "cell 0 3");
        
        lblTime = new JLabel("N/A");
        frame.getContentPane().add(lblTime, "cell 1 3");
        
        lblVehiclePosition = new JLabel("Position (deg):");
        lblVehiclePosition.setFont(new Font("Tahoma", Font.BOLD, 11));
        frame.getContentPane().add(lblVehiclePosition, "cell 0 4");        
        lblPosition = new JLabel("N/A");
        frame.getContentPane().add(lblPosition, "cell 1 4");
        
        lblVehicleDepth = new JLabel("Depth (m):");
        lblVehicleDepth.setFont(new Font("Tahoma", Font.BOLD, 11));
        frame.getContentPane().add(lblVehicleDepth, "cell 0 5");
        lblDepth= new JLabel("N/A");
        frame.getContentPane().add(lblDepth, "cell 1 5");
        
        lblVehicleSog = new JLabel("Speed over ground (m/s):");
        lblVehicleSog.setFont(new Font("Tahoma", Font.BOLD, 11));
        frame.getContentPane().add(lblVehicleSog, "cell 0 6");
        lblSog= new JLabel("N/A");
        frame.getContentPane().add(lblSog, "cell 1 6");
        
        
        JmsManager.addTruthHandler(this);
    }

    @Override
    public void handleMessage(final GroundTruthMessage message) {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                String theTime = new Date(message.timestamp).toString();
                lblTime.setText(theTime);
                String thePos = String.format("(%03.4f, %03.4f)", message.trueLatitude, message.trueLongitude); 
                lblPosition.setText(thePos);
                String theDepth = String.format("%3.2f", message.trueDepth);
                lblDepth.setText(theDepth);
                String theSog = String.format("%02.2f N, %02.2f E, %02.2f D", message.vN, message.vE, -message.vU);
                lblSog.setText(theSog);                
            }
            
        });
    }

    @Override
    public void initialize() {
    }

    @Override
    public void update() {
    }

    @Override
    public void reset() {
    }

    @Override
    public void stop() {
        btnAbort.setEnabled(false);
        btnBrowse.setEnabled(true);
        btnStart.setEnabled(true);

        JOptionPane.showMessageDialog(frame, "Simulation Complete!", "Simulation Complete!", JOptionPane.INFORMATION_MESSAGE);

        frame.dispose();
        JmsManager.stop();
    }
}
