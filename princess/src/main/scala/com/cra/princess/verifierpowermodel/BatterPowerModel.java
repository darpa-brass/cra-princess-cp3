package com.cra.princess.verifierpowermodel;
import java.util.Arrays;

abstract class BatterPowerModel {

    abstract int getParamSupportSize();
    abstract int getNumRvs();

    abstract double getWork(double[] ENUvelocity, double[] EFECdisplacement, int[] offsets);
    abstract double getAngularWork(double[] angularVelocity, int[] offsets);

    public double getTangentialWork(double[] EFECdisplacement, int[] offsets) {

        Arrays.setAll(EFECdisplacement, i -> Math.abs(EFECdisplacement[i]));

//        String[] xyz = new String[]{"x","y","z"};
//        System.out.println("Printing calculations...");

        //check for movement
//        for (int i = 0; i < EFECdisplacement.length; i++) System.out.print("- displacement_"+xyz[i]+": " + EFECdisplacement[i]+ "; ");
//        System.out.println();
        if(Arrays.stream(EFECdisplacement).sum() == 0){
            return 0;   // no movement found
        }

        double[] velocity = getTangentialVelocity(EFECdisplacement);
//        for (int i = 0; i < velocity.length; i++) System.out.print("- velocity_"+xyz[i]+": " + velocity[i]+ "; ");

        return getWork(velocity, EFECdisplacement, offsets);
    }

    abstract double[] getProbabilities(int[] offsets);
    abstract void learnBatch(double[][] ENUvelocityData, double[] powerData) throws ArrayIndexOutOfBoundsException;
    abstract void update(double[][] ENUvelocityData, double[] powerData) throws ArrayIndexOutOfBoundsException;


    private double getSpeed(){
        return 3.2/1000;   //in Km/s
    }

    private double[] getTangentialVelocity(double[] ECEFdisplacement){
        double distance = Math.sqrt(Arrays.stream(ECEFdisplacement).map((disp) -> Math.pow(disp,2)).sum());
        // The sign (direction) on the displacement is required to be preserved.
        return Arrays.stream(ECEFdisplacement).map((disp) -> getSpeed() * (disp/ distance)).toArray();
    }


    public double getAngularWork(Double degrees, int[] offsets){
        //calculate work
        return getAngularWork(new double[]{degrees}, offsets);
    }
}

