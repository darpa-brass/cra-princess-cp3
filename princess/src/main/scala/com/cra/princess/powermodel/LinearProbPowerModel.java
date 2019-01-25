package com.cra.princess.powermodel;

//This power model assumes and describes a linear relationship between velocity(N,E,U) and power rate.

import org.apache.commons.math3.linear.*;

import java.util.Arrays;

public class LinearProbPowerModel extends BatterPowerModel {

    private int numParams;
    private int paramSupportSize;
    private double[][] modelParams;
    private double[][] modelParamProbabilities;


    public LinearProbPowerModel(int numCoods){

        this.numParams = numCoods;

        //todo generalize later by allowing admissable range sizes to vary across different R.V.s
        this.paramSupportSize = 3;   //each random (variable) coefficient has this as the size of it's admissible range.

        modelParams = new double[numCoods][paramSupportSize];
        modelParamProbabilities = new double[numCoods][paramSupportSize];

        //Random initialization for the parameters
        for (int i = 0; i < numCoods; i++) {
            for (int j = 0; j < paramSupportSize; j++) {
                modelParams[i][j] = Math.random()*5;
                modelParamProbabilities[i][j] = 1.0 / paramSupportSize;
            }
        }
    }

    //todo
    public void learnBatch(double[][] ENUvelocity, double[] power)  {
        //left blank for now
    }

    //todo
    public void update(double[][] ENUvelocity, double[] power){
        //left blank for now
    }




    public int getParamSupportSize() {
        return paramSupportSize;
    }

    public int getNumParams(){
        return numParams;
    }

    //todo check
    public double getWork(double[] EFECdisplacement,int speed, int[] offsets) {

        double[] velocity = speedToVelocity(EFECdisplacement, speed);
        double[] power = getPowerHelper(velocity, offsets);

        return powerToWork(EFECdisplacement, velocity, power);
    }

    private double[] getPowerHelper(double[] velocityVector, int[] offsets) {
        double[] power = new double[velocityVector.length];

        for (int i = 0; i < numParams; i++) {
            power[i] = Math.abs(modelParams[i][offsets[i]] * velocityVector[i]);
        }
        return power;
    }

//    public double getPower(double[] EFECdisplacement, int speed, int[] offsets){
//
//        double[] velocity = speedToVelocity(EFECdisplacement, speed);
//        double[] power = getPowerHelper(velocity, offsets);
//        return Arrays.stream(power).sum();
//    }




    public double[] getProbabilities(int[] offsets){
        double [] probabilities = new double[numParams];
        for (int i = 0; i < probabilities.length; i++) {
            probabilities[i] = modelParamProbabilities[i][offsets[i]];
        }
        return probabilities;
    }


    //Test
    public static void main(String[] args){

        LinearProbPowerModel pm = new LinearProbPowerModel(2);

        double[] displacements = new double[]{10,100,20};

        System.out.println(pm.getWork(displacements, 5,new int[]{0,0,0}));
        System.out.println(pm.getWork(displacements,5, new int[]{0,0,1}));
        System.out.println(pm.getWork(displacements, 5,new int[]{1,0,0}));
        System.out.println(pm.getWork(displacements, 5,new int[]{0,1,0}));

        for (int i = 0; i < pm.getNumParams(); i++) {
            for (int j = 0; j < pm.getParamSupportSize(); j++) {
                System.out.println("params vals: "+ pm.modelParams[i][j]);
                System.out.println("params probs: "+ pm.modelParamProbabilities[i][j]);
            }
        }
    }



}
