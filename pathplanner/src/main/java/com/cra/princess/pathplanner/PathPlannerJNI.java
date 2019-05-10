package com.cra.princess.pathplanner;

public class PathPlannerJNI {
    static {
        System.loadLibrary("pathPlannerJNI");
    }
    private final static int MAX_PLAN_PTS = 128;
    private final static double END_MARKER = 179769313486231570000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0;
    private final static double DBL_MAX = 179769313486231570000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0;

    private native Object[] nativeCreatePlan(double ctrlCmp4,
                                             double ctrlCmp3,
                                             double ctrlCmp2,
                                             double ctrlCmp1,
                                             double ctrlCmp0,
                                             double ctrlLoop1,
                                             double ctrlLoop0,
                                             double ctrlConst15,
                                             double ctrlConst14,
                                             double ctrlConst13,
                                             double ctrlConst12,
                                             double ctrlConst11,
                                             double ctrlConst10,
                                             double ctrlConst9,
                                             double ctrlConst8,
                                             double ctrlConst7,
                                             double ctrlConst6,
                                             double ctrlConst5,
                                             double ctrlConst4,
                                             double ctrlConst3,
                                             double ctrlConst2,
                                             double ctrlConst1,
                                             double ctrlConst0,
                                             double startLocationX,
                                             double startLocationY,
                                             double returnLocationX,
                                             double returnLocationY,
                                             Object[] searchArea,
                                             int numPts,
                                             double altitude,
                                             double fovRadians
    );

    public static void main(String[] args) {
        double[][] searchArea = {{0.0, 0.0}, {0.0, 500.0},
                {500.0, 500.0}, {500.0, 0.0}};

        Object[] plan =
                new PathPlannerJNI().nativeCreatePlan(0.0, 0.0, 0.0, 0.0, 0.0, // ctrlCmp
                        0.0, 0.0,                // ctrlLoop
                        END_MARKER, END_MARKER, 0.0, 0.0, 0.0, 2.0, 1.0, 1.0, 1.0,
                        2.0, 2.0, 0.0, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, // ctrlConst
                        0.0, 0.0, 0.0, 0.0, // start and return loc
                        (Object[])searchArea, 4, 90.0, 0.174533);
        double[][] retPlan = new double[MAX_PLAN_PTS][2];
        for(int i = 0; i < MAX_PLAN_PTS; i++) {
            retPlan[i][0] = ((double [])plan[i])[0];
            retPlan[i][1] = ((double [])plan[i])[1];
            if(retPlan[i][0] == END_MARKER || retPlan[i][1] == END_MARKER) {
                break;
            }
            System.out.println("retplan[" + i + "][0] = " + retPlan[i][0]);
            System.out.println("retplan[" + i + "][1] = " + retPlan[i][1]);
        }
    }
}
