package com.cra.princess.localizationalgorithm;

/**
 * A simple model of UUV kinematics
 *
 *
 * Ideally, the kinematics model would be acceleration-based rather than velocity-based.
 * the kinematics model we have is a model of maximum attainable velocity
 * better would be a model which relates thrust, water pressure, drag, etc., to accel
 * for now, this is a hack to obtain acceleration from the existing formula,
 * basically it says that we can accelerate to whatever the maximum speed is in 10 seconds - DG
 *
 * new velocity is previous velocity plus motor acceleration and drag
 * calculating drag is actually very complex, this simple model suffices for our needs
 */
public class KinematicsModel {

    /** Gets the acceleration (in inches per second) of the UUV given the previous velocity and the motor controls.
     * @param actuators: An array of 5 values:
     *                 1) motor RPM
     *                 2) gear ratio
     *                 3) pitch (degrees)
     *                 4) slip [0, 100]
     *                 5) heading
     * @param previousVelocity previous velocity and motor controls
     * @return the acceleration array
     */
    public static double[] getAcceleration(double[] actuators, double[] previousVelocity) {
        double rpm = actuators[0];
        double ratio = actuators[1];
        double pitch = actuators[2];
        double slip = actuators[3];
        double heading = actuators[4];
        double prevXVelocity = previousVelocity[0];
        double prevYVelocity = previousVelocity[1];

        double speed = (rpm == 0) ? 0 :(rpm/ratio) * (pitch) * (1 - (slip/100)) * (1.0 / 60); // inches per second
        double xVelocity = speed * Math.cos(heading);
        double yVelocity = speed * Math.sin(heading);
        double xDrag = Math.signum(prevXVelocity) * 0.01 * Math.pow(prevXVelocity, 2);
        double yDrag = Math.signum(prevYVelocity) * 0.01 * Math.pow(prevYVelocity, 2);
        return new double[] {xVelocity * 0.1 /*- xDrag*/, yVelocity * 0.1 /*- yDrag*/};
    }

}
