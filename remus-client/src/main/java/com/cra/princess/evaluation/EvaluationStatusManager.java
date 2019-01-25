package com.cra.princess.evaluation;

import com.cra.princess.evaluation.util.EvaluationUtils;
import com.cra.princess.metron.MetronRemusManager;
import com.cra.princess.metron.remus.state.*;
import org.apache.log4j.Logger;

import javax.json.Json;
import javax.json.JsonObjectBuilder;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Sends regular status update messages (ground truth, sensors, etc.) to the ReSTful test harness service
 *
 */
public class EvaluationStatusManager extends Thread implements VehicleGroundTruthUpdateListener, DvlSensorUpdateListener, RpmSensorUpdateListener, WaterSpeedSensorUpdateListener, ObjectDetectionListener, VehiclePowerUpdateListener {
    private static final Logger LOG = Logger.getLogger(EvaluationStatusManager.class.getName());

    private static final int STATUS_FREQUENCY_MS = 10000;

    private TestHarnessAdapter testHarnessAdapter = null;
    private MetronRemusManager remusManager = null;

    private boolean working = true;

    private RemusVehicleState currentVehicleState = null;
    private RemusDvlData currentDvlData = null;
    private RemusRpmData currentRpmData = null;
    private RemusWaterSpeedData currentWaterSpeedData = null;
    private RemusObjectDetectionState currentObjectDetection = null;
    private RemusPowerState currentVehiclePower = null;

    public EvaluationStatusManager() {
        // Defaults
        this.currentVehicleState = new RemusVehicleState(0L, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        this.currentDvlData = new RemusDvlData(0L, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        this.currentRpmData = new RemusRpmData(0L, 0.0);
        this.currentWaterSpeedData = new RemusWaterSpeedData(0L, 0.0);
        this.currentObjectDetection = new RemusObjectDetectionState(0L, 0.0, 0.0, 0.0);
        this.currentVehiclePower = new RemusPowerState(0L, 0.0);

        this.testHarnessAdapter = TestHarnessAdapter.getInstance();

        this.remusManager = MetronRemusManager.getInstance();
        this.remusManager.addVehicleGroundTruthUpdateListener(this);
        this.remusManager.addDvlSensorUpdateListener(this);
        this.remusManager.addRpmSensorUpdateListener(this);
        this.remusManager.addWaterSpeedSensorUpdateListener(this);
        this.remusManager.addObjectDetectionListener(this);
        this.remusManager.addVehiclePowerUpdateListener(this);
    }

    @Override
    public void run() {
        LOG.debug("Starting Evaluation Status Manager");
        while (this.working) {
            // Send a state update request every 10 seconds (see CP1 or CP3 descriptions for frequency)
            String content = generateStatusContent();
            try {
                this.testHarnessAdapter.sendStatusMessage(TestHarnessAdapterConstants.STATUS_STATE_UPDATE, content);
                Thread.sleep(STATUS_FREQUENCY_MS);
            } catch (InterruptedException e) {
                // Ignore
            } catch (IOException e) {
                LOG.error(e.getMessage(), e);
            }
        }
    }

    public void stopWork() {
        this.working = false;
    }

    @Override
    public void vehicleGroundTruthUpdate(RemusVehicleState vehicleStateUpdateMessage) {
        this.currentVehicleState = vehicleStateUpdateMessage;
    }

    @Override
    public void dvlSensorUpdate(RemusDvlData dvlDataUpdateMessage) {
        this.currentDvlData = dvlDataUpdateMessage;
    }

    @Override
    public void rpmSensorUpdate(RemusRpmData rpmDataUpdateMessage) {
        this.currentRpmData = rpmDataUpdateMessage;
    }

    @Override
    public void waterSpeedSensorUpdate(RemusWaterSpeedData waterSpeedDataUpdateMessage) {
        this.currentWaterSpeedData = waterSpeedDataUpdateMessage;
    }

    @Override
    public void objectDetected(RemusObjectDetectionState objectDetectionUpdateMessage) {
        this.currentObjectDetection = objectDetectionUpdateMessage;
    }

    @Override
    public void vehiclePowerUpdate(RemusPowerState vehiclePowerUpdateMessage) {
        this.currentVehiclePower = vehiclePowerUpdateMessage;
    }

    private String generateStatusContent() {
        String statusContent = null;

        SimpleDateFormat dateFormatter = new SimpleDateFormat(EvaluationUtils.ECMASCRIPT_DATE_FORMAT);
        Date timestampDate = null;
        String timestamp = null;

        JsonObjectBuilder builder = Json.createObjectBuilder();

        // Ground Truth
        JsonObjectBuilder groundTruthBuilder = Json.createObjectBuilder();
        timestampDate = new Date(this.currentVehicleState.getTimestamp());
        timestamp = dateFormatter.format(timestampDate);
        groundTruthBuilder.add("Timestamp", timestamp);
        groundTruthBuilder.add("Lat", this.currentVehicleState.getTrueLatitude());
        groundTruthBuilder.add("Lon", this.currentVehicleState.getTrueLongitude());
        groundTruthBuilder.add("Depth", this.currentVehicleState.getTrueDepth());
        groundTruthBuilder.add("vE", this.currentVehicleState.getvE());
        groundTruthBuilder.add("vN", this.currentVehicleState.getvN());
        groundTruthBuilder.add("vU", this.currentVehicleState.getvU());
        groundTruthBuilder.add("Pitch", this.currentVehicleState.getPitch());
        groundTruthBuilder.add("Roll", this.currentVehicleState.getRoll());
        groundTruthBuilder.add("Heading", this.currentVehicleState.getHeading());
        builder.add("GroundTruth", groundTruthBuilder.build());

        // DVL Sensor
        JsonObjectBuilder dvlBuilder = Json.createObjectBuilder();
        timestampDate = new Date(this.currentDvlData.getTimestamp());
        timestamp = dateFormatter.format(timestampDate);
        dvlBuilder.add("Timestamp", timestamp);
        dvlBuilder.add("Depth", this.currentDvlData.getDepth());
        dvlBuilder.add("vE", this.currentDvlData.getvE());
        dvlBuilder.add("vN", this.currentDvlData.getvN());
        dvlBuilder.add("vU", this.currentDvlData.getvU());
        dvlBuilder.add("Pitch", this.currentDvlData.getPitch());
        dvlBuilder.add("Roll", this.currentDvlData.getRoll());
        dvlBuilder.add("Heading", this.currentDvlData.getHeading());
        builder.add("DVLSensor", dvlBuilder.build());

        // Propeller RPM
        JsonObjectBuilder rpmBuilder = Json.createObjectBuilder();
        timestampDate = new Date(this.currentRpmData.getTimestamp());
        timestamp = dateFormatter.format(timestampDate);
        rpmBuilder.add("Timestamp", timestamp);
        rpmBuilder.add("PropellerRPM", this.currentRpmData.getRpm());
        builder.add("RPMSensor", rpmBuilder.build());

        // Water Speed
        JsonObjectBuilder waterSpeedBuilder = Json.createObjectBuilder();
        timestampDate = new Date(this.currentWaterSpeedData.getTimestamp());
        timestamp = dateFormatter.format(timestampDate);
        waterSpeedBuilder.add("Timestamp", timestamp);
        waterSpeedBuilder.add("WaterSpeed", this.currentWaterSpeedData.getSpeed());
        builder.add("WaterSpeedSensor", waterSpeedBuilder.build());

        // Object Detection
        JsonObjectBuilder objectDetectionBuilder = Json.createObjectBuilder();
        timestampDate = new Date(this.currentObjectDetection.getTimestamp());
        timestamp = dateFormatter.format(timestampDate);
        objectDetectionBuilder.add("Timestamp", timestamp);
        objectDetectionBuilder.add("Range", this.currentObjectDetection.getRange());
        objectDetectionBuilder.add("Theta", this.currentObjectDetection.getTheta());
        objectDetectionBuilder.add("Phi", this.currentObjectDetection.getPhi());
        builder.add("ObjectDetectionSensor", objectDetectionBuilder.build());

        // Power
        JsonObjectBuilder powerBuilder = Json.createObjectBuilder();
        timestampDate = new Date(this.currentVehiclePower.getTimestamp());
        timestamp = dateFormatter.format(timestampDate);
        powerBuilder.add("Timestamp", timestamp);
        powerBuilder.add("RemainingBatteryEnergy", this.currentVehiclePower.getPower());
        builder.add("PowerSensor", powerBuilder.build());

        statusContent = EvaluationUtils.jsonToString(builder.build());

        return statusContent;
    }
}
