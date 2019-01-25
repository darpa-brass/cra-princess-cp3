package com.cra.princess.componentmodel.asm.testprograms;

public class SubroutineTestProgram {

    public double sine(double in) {
        return Math.sin(in);
    }

    public double linear(double in) {
        return 2 * in + 5;
    }

    public double testPiecewise(double in) {
        boolean roundsEven = Math.round((float) in) % 2 == 0;
        if(roundsEven) {
            return sine(in);
        } else {
            return linear(in);
        }
    }

    public int testFactorial(int in) {
        if(in == 0) {
            return 1;
        } else {
            return testFactorial(in - 1) * in;
        }
    }


    // TODO: currently a fixed size array!!
    public double testLagrangeInterpolation(){
        double [][] points = {{1,1}, {2,2}};
        return lagrangeInterpolation2D(points, 1.0);
    }

    private double lagrangeInterpolation2D(double[][] pts, double x){
        return (x - pts[1][0])/(pts[0][0]- pts[1][0]) * pts[0][1]
                + (x - pts[0][0])/(pts[1][0]- pts[0][0]) * pts[1][1];
    }

    private double lagrangeInterpolation(double[][] pts, double x){

        return (x - pts[1][0])/(pts[0][0]- pts[1][0]) * pts[0][1]
                + (x - pts[0][0])/(pts[1][0]- pts[0][0]) * pts[1][1];
    }

    private double sumOfBasis(double[][] pts, int currentIndex, double x){
        if(currentIndex >= pts.length) return 0.0;
        double basisProd = basisProduct(pts, 0, currentIndex, x)* pts[currentIndex][1];
        return basisProd + sumOfBasis(pts, currentIndex + 1, x);
    }

    private double basisProduct(double[][] pts, int currentIndex, int ignoreIndex, double x){
        if(currentIndex >= pts.length || currentIndex == ignoreIndex)
            return 1.0;
        double prod = (x - pts[currentIndex][0])/(pts[ignoreIndex][0]- pts[currentIndex][0]) ;
        return prod * basisProduct(pts, currentIndex + 1, ignoreIndex, x);
    }
}
