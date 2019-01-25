package com.cra.princess.evaluation;

import com.cra.princess.evaluation.messages.CpInitialParams;
import com.cra.princess.evaluation.messages.DvlSensorPerturbationType;
import com.cra.princess.evaluation.messages.PerturbingCurrentType;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.StepMessage;
import com.cra.princess.simulation.Runner;
import com.cra.princess.simulation.TimeManager;
import com.cra.princess.simulation.config.Configuration;
import com.cra.princess.simulation.config.CurrentRegion;
import com.cra.princess.simulation.config.DetectableObject;
import com.cra.princess.simulation.config.Region;
import com.cra.princess.simulation.events.SensorPerturbationEvent;
import org.apache.log4j.Logger;
import scala.collection.immutable.List;

import javax.json.Json;
import javax.json.JsonException;
import javax.json.JsonReader;
import java.io.*;

public class EvaluationScenarioManager {
    private static final Logger LOG = Logger.getLogger(EvaluationScenarioManager.class.getName());

    private static final String CP_BASE_SCENARIO_FILENAME = "scenarios/scenario-cp.json";

    public static final String SCENARIO_FILENAME = "scenario.json";

    public static void generateCPScenario(CpInitialParams initialParams) throws IOException {
        Configuration configuration = new Configuration(CP_BASE_SCENARIO_FILENAME);

        // Use Initial Params to configure new CP scenario

        // Formerly CP3 Params
        double llLat = initialParams.SearchRegion().LowerLeftLocation().Lat();
        double llLon = initialParams.SearchRegion().LowerLeftLocation().Lon();
        double urLat = initialParams.SearchRegion().UpperRightLocation().Lat();
        double urLon = initialParams.SearchRegion().UpperRightLocation().Lon();
        double objLat = initialParams.SearchRegion().ObjectLocation().Lat();
        double objLon = initialParams.SearchRegion().ObjectLocation().Lon();

        Region searchRegion = new Region();
        searchRegion.setsLat(llLat);
        searchRegion.setwLon(llLon);
        searchRegion.setnLat(urLat);
        searchRegion.seteLon(urLon);
        configuration.setSearchRegion(searchRegion);

        DetectableObject detectableObject = new DetectableObject();
        detectableObject.setLat(objLat);
        detectableObject.setLon(objLon);
        configuration.addDetectableObject(detectableObject);

        // Formerly CP1 Params
        // We don't use depth in the CP1 scenario, so just use whatever was provided when needed.
        double depth = configuration.getVehicleOrigin().getDepth();

        // Use CP1 Initial Params to configure new CP1 scenario
        double originLat = initialParams.Origin().Lat();
        double originLon = initialParams.Origin().Lon();
        double destLat = initialParams.Destination().Lat();
        double destLon = initialParams.Destination().Lon();

        configuration.setVehicleOrigin(originLat, originLon, depth);
        configuration.setDestination(destLat, destLon, depth);

        List<DvlSensorPerturbationType> sensorPerturbations = initialParams.DVLSensorPerturbations();
        scala.collection.Iterator iter = sensorPerturbations.iterator();
        DvlSensorPerturbationType sensorPerturbation = null;
        SensorPerturbationEvent event = null;
        String json = null;
        JsonReader reader = null;
        while (iter.hasNext()) {
            sensorPerturbation = (DvlSensorPerturbationType)iter.next();

            json = "{ \"time\": " + sensorPerturbation.TimeIntoScenario() + ", \"name\": \"" + sensorPerturbation.SensorName() + "\", \"bias\": " + sensorPerturbation.SensorBias() + ", \"noiseDev\": " + sensorPerturbation.SensorNoise() + ", \"anchor\": " + sensorPerturbation.SensorAnchor() + ", \"anchorProbability\": " + sensorPerturbation.SensorAnchorProbability() + " }";
            reader = Json.createReader(new ByteArrayInputStream(json.getBytes()));

            event = new SensorPerturbationEvent();
            event.configure(reader.readObject());

            configuration.addEvent(event);
        }

        List<PerturbingCurrentType> currents = initialParams.PerturbingCurrents();
        iter = currents.iterator();
        PerturbingCurrentType current = null;
        CurrentRegion region = null;
        while (iter.hasNext()) {
            current = (PerturbingCurrentType)iter.next();

            region = new CurrentRegion();
            region.setsLat(current.LowerLeftLocation().Lat());
            region.setwLon(current.LowerLeftLocation().Lon());
            region.setnLat(current.UpperRightLocation().Lat());
            region.seteLon(current.UpperRightLocation().Lon());
            region.setvE(current.vE());
            region.setvN(current.vN());

            configuration.addCurrentRegion(region);
        }

        saveScenarioFile(configuration);
    }

    // Save new scenario to file
    private static void saveScenarioFile(Configuration configuration) throws IOException {
        FileWriter f = null;

        try {
            String jsonString = configuration.getJsonString();
            f = new FileWriter(SCENARIO_FILENAME);
            f.write(jsonString);
        } catch (IOException e) {
            LOG.error(e.getMessage(), e);
            throw e;
        } finally {
            try {
                f.close();
            } catch (IOException e) {
                LOG.error(e.getMessage(), e);
            }
        }
    }

    public static void runScenario(boolean runStepped) throws IOException {
        File scenarioFile = new File(SCENARIO_FILENAME);
        if (scenarioFile.exists() && scenarioFile.isFile()) {
            if (runStepped == true) {
                LOG.debug("Starting scenario in stepper mode: " + SCENARIO_FILENAME);
            }
            else {
                LOG.debug("Starting scenario: " + SCENARIO_FILENAME);
            }
            Runner runner = new Runner();
            try {
                InputStream is = new FileInputStream(SCENARIO_FILENAME);
                runner.load(is);

                if (runStepped == true) {
                    runner.runStepperMode();
                }
                else {
                    runner.run();
                }

                // Cleanly shut down when simulation is over
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
                LOG.error(e.getMessage(), e);
                throw e;
            } catch (JsonException e) {
                LOG.error(e.getMessage(), e);
                throw e;
            }

            EvaluationMessenger.getInstance().sendScenarioStartedMessage();

            if (runStepped == true) {
                LOG.debug("Scenario started in stepper mode");
            }
            else {
                LOG.debug("Scenario started");
            }
        }
        else {
            throw new IOException("Invalid scenario file: " + SCENARIO_FILENAME);
        }
    }

    public static void sendStepMessage(long timeStep) {
        StepMessage stepMessage = new StepMessage(timeStep);
        JmsManager.sendStepMessage(stepMessage);
    }
}
