package com.cra.princess.componentmodel.asm.testprograms;

/**
 * A suite of simple procedures used to test analysis of looping constructs
 */
public class LoopingTestProgram {

    /** Arithmetic series, result is (in * (in+1)) / 2*/
    public int simpleLoop(int in) {
        int a = in;
        int total = 0;
        while(a > 0) {
            total += a;
            a--;
        }
        return total;
    }


    /** Sum of Arithmetic series, result is Sum(a from 1 to in) of (a * (a + 1))/2 */
    public int nestedLoop(int in){
        int a = in;
        int total = 0;
        while(a > 0){
            int b = a;
            while(b > 0) {
                total += a;
                b--;
            }
            a--;
        }
        return total;
    }

    public int loopWithFunctionCall(int in){
        int a = in;
        int total = 0;
        while(a > 0){
            total += simpleLoop(a);
            a--;
        }
        return total;
    }

    public int loopWithBreak(int in){
        int a = in;
        int total = 0;
        int count = 0;
        while(a > 0){
            total += a;
            a--;
            if(count > 5)
                break;
            count++;
        }
        return total;
    }
}
