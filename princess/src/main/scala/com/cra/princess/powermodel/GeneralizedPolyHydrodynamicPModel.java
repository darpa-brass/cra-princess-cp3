package com.cra.princess.powermodel;

import org.apache.commons.lang3.ArrayUtils;
import org.apache.commons.math3.linear.*;

//Uses a polynomial hydrodynamic model: Power = a + a_1*v + a_2*v^2 + ... a_d*v^d
    //where a_i is the polynomial coefficient.
//This model is not probabilistic.

public class GeneralizedPolyHydrodynamicPModel extends BatterPowerModel{

    private double[] powerCoeffs;
    private int d;

    public GeneralizedPolyHydrodynamicPModel(int polyDegree){
        d = polyDegree;
        powerCoeffs = new double[3*d]; //for each x,y,z we have d terms
    }

    @Override
    int getParamSupportSize() {
        return 1;
    }

    @Override
    int getNumParams() {
        return 3; //vE, vN, vU
    }

    @Override //todo check Math.abs
    double getWork(double[] EFECdisplacement, int speed, int[] offsets) {

        double[] velocity = speedToVelocity(EFECdisplacement, speed);
        double[] power = new double[velocity.length];

        for (int i = 0; i < power.length; i++) {
            for (int j = 0; j < d; j++) {
                power[i] += Math.abs(powerCoeffs[i*d + j] * (Math.pow(velocity[i],j)));
            }
        }

        return powerToWork(EFECdisplacement,velocity,power);
    }

    @Override
    double[] getProbabilities(int[] offsets) {
        return new double[]{1};
    }

    @Override   //todo check if Math.abs is needed
    void learnBatch(double[][] ENUvelocity, double[] power) throws ArrayIndexOutOfBoundsException {
        if (ENUvelocity.length != power.length){
            throw new ArrayIndexOutOfBoundsException("ENUvelocity and power are not of the same length");
        }
        if (ArrayUtils.isEmpty(ENUvelocity) || ArrayUtils.isNotEmpty(power)){
            System.out.println("Either the ENUvelocity, or power array is empty!");
            return;
        }

        double[][] kVector = new double[ENUvelocity.length][ENUvelocity[0].length * d]; // <-- size of [...][3*d]

        // P = a + a_1*v + a_2*v^2 + ... a_d*v^d
        for (int i = 0; i < kVector.length; i++) {
            for (int j = 0; j < 3; j++) { // x,y,z
                for (int k = 0; k < d; k++) {   // e.g. x_1, x_2, ..., x_d
                    kVector[i][j*d + k] = Math.pow(ENUvelocity[i][j*d + k],k);
                }
            }
        }

        RealMatrix coefficients = new Array2DRowRealMatrix(kVector);
        DecompositionSolver ds = new LUDecomposition(coefficients).getSolver();
        RealVector constants = new ArrayRealVector(power);
        RealVector newPowerCoeffs = ds.solve(constants);

        this.powerCoeffs = newPowerCoeffs.toArray();
    }

    @Override
    void update(double[][] ENUvelocity, double[] power) throws ArrayIndexOutOfBoundsException {

    }
}
