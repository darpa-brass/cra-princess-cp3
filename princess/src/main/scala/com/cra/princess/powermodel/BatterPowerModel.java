package com.cra.princess.powermodel;

 abstract class BatterPowerModel {

    abstract int getParamSupportSize();
    abstract int getNumParams();
//    abstract double getPower(double[] EFECdisplacement, int speed, int[] offsets);

    abstract double getWork(double[] EFECdisplacement,int speed, int[] offsets);
    abstract double[] getProbabilities(int[] offsets);

    abstract void learnBatch(double[][] ENUvelocity, double[] power) throws ArrayIndexOutOfBoundsException;
    abstract void update(double[][] ENUvelocity, double[] power) throws ArrayIndexOutOfBoundsException;


    double[] speedToVelocity(double[] ECEFdisplacement, int speed){
        //Find magnitude of displacement
        int sqrd_displacement = 0;
        for (double displacement : ECEFdisplacement) {
        sqrd_displacement += Math.pow(displacement, 2);
        }
        double mag = Math.sqrt(sqrd_displacement);

        // Find velocity
        double[] velocity = new double[ECEFdisplacement.length];
        for (int i = 0; i < ECEFdisplacement.length; i++) {
        // The sign (direction) on the displacement is required to be preserved. // (speed * unit displacement) = velocity
        velocity[i] =  (speed * ((double)ECEFdisplacement[i] /mag));
        }

        return velocity;
        }


    double powerToWork(double[] EFECdisplacement, double[] velocity, double[] power){
        //Calculate work as power * time
        double work = 0;
        for (int i = 0; i < EFECdisplacement.length; i++) {
            work += power[i] * (EFECdisplacement[i]/ velocity[i]);
        }

        return work;
     }



 }

