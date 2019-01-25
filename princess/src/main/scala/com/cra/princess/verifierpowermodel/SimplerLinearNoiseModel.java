package com.cra.princess.verifierpowermodel;

import java.util.Arrays;

//A  linear model W = FD = RD = (av)D, where the coefficients a are to be learnt.
public class SimplerLinearNoiseModel extends BatterPowerModel {

    private double[] tangentialEnergyModel;
    private double[] angularEnergyModel;
    private double[] noiseProbabilities;
    private double[] noiseDistribution;

    public SimplerLinearNoiseModel(){

        tangentialEnergyModel = new double[]{     0.        , 223907.62578185, 281320.54746558};
        angularEnergyModel = new double[]{0.14604648};

        // Work = RD + e
        //Assumes a gaussian distribution for battery measurement noise e (for no good reason yet)
        //truncated up to 3 std of the true distribution
        //uses only 3 values, via the equal-bracket median technique

        double variance =  0.12979615795038224;  //mean zero
        noiseDistribution = new double[3];
        noiseDistribution[0] = -2*variance;
        noiseDistribution[1] = 0;
        noiseDistribution[2] = 2*variance;

        noiseProbabilities = new double[3];
        noiseProbabilities[0] = (0.136 + 0.021) / 0.9973;   //divided by normalizing constant
        noiseProbabilities[1] = 0.682 / 0.9973;
        noiseProbabilities[2] = noiseProbabilities[0];

        for (int i = 0; i < noiseProbabilities.length; i++) {
            noiseProbabilities[i] /= 0.9986964804973429;    // just to ensure that each sums to one
        }


        System.out.println("Printing model parameters...");
        for (int i = 0; i < tangentialEnergyModel.length; i++) System.out.print("param_"+i+ ": " + tangentialEnergyModel[i]+". ");
        System.out.println("\nPrinting noise parameters...");
        for (int i = 0; i < noiseDistribution.length; i++) System.out.print("noise_"+i+ ": " +noiseDistribution[i]+". ");
        System.out.println("\nPrinting noise probabilities...");
        for (int i = 0; i < noiseDistribution.length; i++) System.out.print("noise_"+i+ ": " +noiseProbabilities[i]+". ");
        System.out.println("\n");
    }



    public void learnBatch(double[][] ENUvelocityData, double[] powerData)  {
        //left blank for now
    }

    public void update(double[][] ENUvelocityData, double[] powerData){
        //left blank for now
    }

    public int getParamSupportSize() {
        return noiseDistribution.length ;
    }
    public int getNumRvs(){
        return 1; //todo: we don't really need more than 1 parameter for this model at this time
    }

    public double getWork(double[] ENUvelocity, double[] EFECdisplacement, int[] offsets) {
        //Calculate work as : FD = RD ~ AvD = A(vD).

        double work = 0;
        for (int i = 0; i < tangentialEnergyModel.length; i++)
            work += tangentialEnergyModel[i] * (ENUvelocity[i] * EFECdisplacement[i]);


        // the noise is just the gaussian variable.
        // we add the variable to the work

        return work + noiseDistribution[offsets[0]];
    }

    @Override
    double getAngularWork(double[] angularVelocity, int[] offsets) {
        return angularEnergyModel[0]* angularVelocity[0];
    }

    public double[] getProbabilities(int[] offsets){
        return new double[]{noiseProbabilities[offsets[0]]};
    }

    public static void main(String[] args){
    }

}
