package com.cra.princess.models;

import com.cra.princess.localizationalgorithm.KinematicsModel;
import org.apache.commons.lang3.ArrayUtils;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Provides pseudo-realistic generation of measurement trajectories from a UUV 
 */
public class UUVDataGeneration {

    public double[] getVelocityMultipliers() {
        return velocityMultipliers;
    }

    public void setVelocityMultipliers(double[] velocityMultipliers) {
        this.velocityMultipliers = velocityMultipliers;
    }

    /** Represents an observed trajectory on a UUV */
    public static class UUVTrajectory {
        private double initialCovarianceDiagonal;
        private double initialCovarianceOffDiagonal;
        private double[] actuators;
        private double[] initialState;
        private List<Double[]> velocityMeasurements;

        public UUVTrajectory(double initialCovarianceDiagonal, double initialCovarianceOffDiagonal,
                double[] actuators, double[] initialState, List<Double[]> velocityMeasurements) {
            this.initialCovarianceDiagonal = initialCovarianceDiagonal;
            this.initialCovarianceOffDiagonal = initialCovarianceOffDiagonal;
            this.actuators = actuators;
            this.initialState = initialState;
            this.velocityMeasurements = velocityMeasurements;
        }

        public double[] getActuators() {
            return actuators;
        }

        public double[] getInitialState() {
            return initialState;
        }

        public List<Double[]> getVelocityMeasurements() {
            return velocityMeasurements;
        }

        public double getInitialCovarianceDiagonal() {
            return initialCovarianceDiagonal;
        }

        public double getInitialCovarianceOffDiagonal() {
            return initialCovarianceOffDiagonal;
        }
    }

    private int trajectoryLength;
    private double[] processNoise;
    private double[] measurementNoise;
    private double stepLengthSeconds;
    private double[] velocityMultipliers;

    /**
     * Create a data generator, directly specifying all noise variables
     * @param trajectoryLength The length (number of motion steps) of each trajectory
     * @param processNoise Standard deviations in [dx, dy]
     * @param velocityMultipliers Multipliers for x and y velocity, useful for simulating water current, for instance
     * @param measurementNoise Standard deviations of noise on sensor measurements [dx, dy]
     * @param stepLengthSeconds Number of elapsed seconds between each sensor reading in the trajectory
     */
    public UUVDataGeneration(int trajectoryLength, double[] processNoise, double[] velocityMultipliers, double[] measurementNoise, double stepLengthSeconds) {
        this.trajectoryLength = trajectoryLength;
        this.processNoise = processNoise;
        this.measurementNoise = measurementNoise;
        this.stepLengthSeconds = stepLengthSeconds;
        this.velocityMultipliers = velocityMultipliers;
    }

    /**
     * Create a data generator with default parameters
     * @param trajectoryLength The length (number of motion steps) of each trajectory
     */
    public UUVDataGeneration(int trajectoryLength) {
        this(trajectoryLength, new double[] {0.3, 0.3}, new double[] {1.0, 1.0}, new double[] { 0.1, 0.2}, 0.1);
    }

    public UUVTrajectory generate(double rpm, double bearing, double[] startVelocities) {
        return generate(new Random(), rpm, bearing, startVelocities);
    }

    public UUVTrajectory generate(Random rand, double rpm, double bearing, double[] startVelocities) {
        double gearRatio = 2;
        double pitch = (Math.PI / 6.0) * (180 / Math.PI);
        double slip = 10;

        double[] state = ArrayUtils.clone(startVelocities);

        List<Double[]> velocityMeasurements = new ArrayList<Double[]>();
        for(int i = 0; i < this.trajectoryLength; i++) {
            double[] accel = KinematicsModel.getAcceleration(new double[] {rpm, gearRatio, pitch, slip, bearing}, state);
            state[0] = state[0] + stepLengthSeconds * velocityMultipliers[0] * accel[0] + rand.nextGaussian() * processNoise[0];
            state[1] = state[1] + stepLengthSeconds * velocityMultipliers[1] * accel[1] + rand.nextGaussian() * processNoise[1];

            // incorporate measurement noise
            velocityMeasurements.add(new Double[] {
                    state[0] + rand.nextGaussian() * measurementNoise[0],
                    state[1] + rand.nextGaussian() * measurementNoise[1] });
        }

        double diagonalCovariance = rand.nextDouble() * 0.1;
        double offDiagonalCovariance = diagonalCovariance * rand.nextDouble();
        return new UUVTrajectory(diagonalCovariance, offDiagonalCovariance,
                new double[] {rpm, gearRatio, pitch, slip, bearing},
                new double[] {0, 0, startVelocities[0], startVelocities[1]}, velocityMeasurements);
    }

    /**
     * Generate one trajectory of length trajectoryLength
     */
    public UUVTrajectory generate() {
        Random rand = new Random();
        double initialXVelocity = rand.nextDouble() * 120 - 60;
        double initialYVelocity = rand.nextDouble() * 120 - 60;
        return this.generate(rand, rand.nextDouble() * 3000, rand.nextDouble() * Math.PI,
                            new double[] {initialXVelocity, initialYVelocity});
    }

    public UUVTrajectory generate(Random rand) {
        double initialXVelocity = rand.nextDouble() * 120 - 60;
        double initialYVelocity = rand.nextDouble() * 120 - 60;
        return this.generate(rand, rand.nextDouble() * 3000, rand.nextDouble() * Math.PI,
                new double[] {initialXVelocity, initialYVelocity});
    }

    public int getTrajectoryLength() {
        return trajectoryLength;
    }

    public void setTrajectoryLength(int trajectoryLength) {
        this.trajectoryLength = trajectoryLength;
    }

    public double[] getProcessNoise() {
        return processNoise;
    }

    public void setProcessNoise(double[] processNoise) {
        this.processNoise = processNoise;
    }

    public double[] getMeasurementNoise() {
        return measurementNoise;
    }

    public void setMeasurementNoise(double[] measurementNoise) {
        this.measurementNoise = measurementNoise;
    }

    public double getStepLengthSeconds() {
        return stepLengthSeconds;
    }

    public void setStepLengthSeconds(double stepLengthSeconds) {
        this.stepLengthSeconds = stepLengthSeconds;
    }
}
