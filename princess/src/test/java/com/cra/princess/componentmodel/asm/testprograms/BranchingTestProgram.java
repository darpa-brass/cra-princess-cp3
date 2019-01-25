package com.cra.princess.componentmodel.asm.testprograms;

/** Contains a set of methods used to test analysis of branching code */
public class BranchingTestProgram {

    /** Solution to triangle classification problem from "Probabilistic Symbolic Execution" by Geldenhuys et al. */
    int classify(int a, int b, int c) {
        if(a <= 0 || b <= 0 || c <= 0) return 4;

        int type = 0;
        if(a == b) type += 1;
        if(a == c) type += 2;
        if(b == c) type += 3;
        if(type == 0) {
            if(a+c <= c || b+c <= a || a+c >= b) type = 4;
            else type = 1;
            return type;
        }
        if(type > 3) type = 3;
        else if(type == 1 && a+b > c) type = 2;
        else if(type == 2 && a+c > b) type = 2;
        else if(type == 3 && b+c > a) type = 2;
        else type = 4;
        return type;
    }

    public double testPiecewise(double in) {
        boolean roundsEven = Math.round((float) in) % 2 == 0;
        if(roundsEven) {
            return Math.sin(in);
        } else {
            return 2 * in + 5;
        }
    }

    public int testRecursion(int in) {
        if(in == 0) {
            return 0;
        } else {
            return in + testRecursion(in-1);
        }
    }

    /** A test for resolution of a local variable which is assigned different values in different branches */
    public int testBranchResolution(int in) {
        int a;
        if(in < 0) {
            a = 0;
        } else {
            a = in;
        }
        return a;
    }

    /** A test for resolution of a local variable which is assigned different values in different nested branches.
     * One branch bypasses the second level for some inputs and proceeds directly to the phi node*/
    public int testNestedBranchResolutionWithBypass(int in) {
        int a = 0;
        if(in < 0) {
            if(in < -5) {
                a = -2;
            } else {
                a = -1;
            }
        } else {
            if(in > 5) {
                a = 2;
            }
        }

        return a;
    }

    /** A test for resolution of a local variable which is assigned different values in different nested branches */
    public int testNestedBranchResolution(int in) {
        int a;
        if(in < 0) {
            if(in < -5) {
                a = 0;
            } else {
                a = 1;
            }
        } else {
            if(in > 5) {
                a = 2;
            } else {
                a = 3;
            }
        }

        return a;
    }

    public int testReturnsInBranch(int in) {
        int a = 0;
        int b;
        if(in < 0) {
            a = in+5;
        }

        if(a < 0) {
            return in+1;
        } else {
            if(a > 3) {
                b = a * -1;
            } else {
                return in-1;
            }
        }

        return b;
    }

    /** A test for function calls within branches */
    public int testFunctionCallInBranch(int in) {
        int result;
        if(in < 0) {
            return addOne(in);
        } else {
            result = in;
        }
        return result;
    }

    public int addOne(int in) {
        return in + 1;
    }
}
