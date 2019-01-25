package com.cra.princess.verifier;

import com.cra.princess.verifierpowermodel.SimplerLinearNoiseModel;
import parser.State;
import parser.VarList;
import parser.ast.Declaration;
import parser.ast.DeclarationBool;
import parser.ast.DeclarationInt;
import parser.ast.Expression;
import parser.type.Type;
import parser.type.TypeBool;
import parser.type.TypeInt;
import prism.DefaultModelGenerator;
import prism.ModelType;
import prism.PrismException;
import prism.PrismLangException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class BatteryModel extends DefaultModelGenerator {

    private int initialBatteryAmount;

    private int batteryAmount;
    private int waypointIndex;
    private List<double[]> displacementVectors;
    private List<Double> rotations;

    private SimplerLinearNoiseModel wm = new SimplerLinearNoiseModel();

    //current state to be explored.
    private State exploreState;
    private boolean end;

    public BatteryModel(int batteryAmount, List<double[]> UTMwaypoints) throws Exception {

        // [Lat ,Lon ,h ]
        int NUM_COODS = 3;
        if (UTMwaypoints.get(0).length != NUM_COODS){
            throw new Exception("GPSwaypoints requires 3 coods (lat,lon,h) per point");
        }

        this.initialBatteryAmount = batteryAmount;
        this.batteryAmount = batteryAmount;
        this.waypointIndex = 0;
        this.displacementVectors = new ArrayList<>();
        this.rotations = new ArrayList<>();
        this.end = false;

        // converts from UTM to geodetic coods
        List<double[]> GPSwaypoints = new ArrayList<>();
        for(double[] wp: UTMwaypoints) GPSwaypoints.add(UTMtoGeodetic(wp[0], wp[1], wp[2]));

        // converts from geodetic coods to ECEF
        List<double[]> ECEFwaypoints = new ArrayList<>();
        for(double[] wp: GPSwaypoints) ECEFwaypoints.add(geodeticToECEF(wp[0], wp[1], wp[2]));

        // todo: consider transforming to ENU coods

        ArrayList<double[]> GPSdisplacementvectors = new ArrayList<>();

        // finds displacements between ECEF waypoints
        for (int i = 0; i < ECEFwaypoints.size() - 1; i++) {
            double[] displacement = new double[NUM_COODS];
            double[] gpsdisplacement = new double[NUM_COODS];
            for (int j = 0; j < displacement.length; j++) {

                //todo: assuming not using a threshold bound & we assume displacement direction is irrelevant
                displacement[j] = Math.abs(ECEFwaypoints.get(i+1)[j] - ECEFwaypoints.get(i)[j]);
                gpsdisplacement[j] = Math.abs(GPSwaypoints.get(i+1)[j] - GPSwaypoints.get(i)[j]);
            }

            displacementVectors.add(displacement);
            GPSdisplacementvectors.add(gpsdisplacement);

            //For the angles (rotations), we assume we are always pointing right to begin.
            //We use the displacements of EFEC waypoints to tell us the angles

            //todo: temporariliy uses GPS frame of reference
            //get the dot product between the displacement_vector and the previous displacement vector
            double[] vectorU = (i == 0) ? new double[]{0,1} //north facing
                    : new double[]{GPSdisplacementvectors.get(i-1)[0], GPSdisplacementvectors.get(i-1)[1]};

            double[] vectorV = new double[]{gpsdisplacement[0],gpsdisplacement[1]};

            double dot_product = 0;
            for (int j = 0; j < vectorU.length; j++) {
                dot_product += vectorU[j]*vectorV[j];
            }

            double dotU = Math.sqrt(Arrays.stream(vectorU).map(value -> Math.pow(value,2)).sum());
            double dotV = Math.sqrt(Arrays.stream(vectorV).map(value -> Math.pow(value,2)).sum());
            double dot_unit = dotU*dotV;

            double rads = Math.acos(dot_product / dot_unit) ; //positive always,
            double degrees = rads * 180 / Math.PI;

            rotations.add(degrees);

        }
    }

    private double[] UTMtoGeodetic(double north, double east, double h) {
        double latDegreeMeter =  180.0 / (Math.PI*6378137.0);
        double lonDegreeMeter =  latDegreeMeter / Math.cos(Math.toRadians(0));
        double lat = 0 + north * latDegreeMeter;
        double lon = 0 + east * lonDegreeMeter;
        return new double[]{lat, lon, 0};
    }

    private double[] geodeticToECEF(double lat, double lon, double h){
        //formula chosen is referenced below.

        lat = Math.toRadians(lat);
        lon = Math.toRadians(lon);

        //assumes the WGS84 model
        double a = 6378137.0;           //semi-major axis in metres
        double flat = 1 / (298.257223563); //flattening
        double b = a * (1 - flat);         //semi-minor axis
        double e = Math.sqrt((2*flat) - Math.pow(flat,2));      //eccentricity of ellipsoid
        double N = a / (Math.sqrt(1 - (Math.pow(e,2)*Math.pow(Math.sin(lat),2)))); //Normal

        double x = (N + h)*Math.cos(lat)*Math.cos(lon);
        double y = (N + h)*Math.cos(lat)*Math.sin(lon);
        double z = (((Math.pow(b,2)/Math.pow(a,2))*N) + h)*Math.sin(lat);

        return new double[]{x/1000,y/1000,z/1000};     //in EFEC Kilometers
    }

    @Override
    public State getInitialState() throws PrismException {
        return new State(3)
                .setValue(0, batteryAmount)
                .setValue(1,end)
                .setValue(2,waypointIndex);
    }

    @Override
    public void exploreState(State state) throws PrismException {

        this.exploreState = state;

        batteryAmount = (Integer) exploreState.varValues[0];
        end = (Boolean) exploreState.varValues[1];
        waypointIndex = (Integer) exploreState.varValues[2];

    }

    @Override
    public State getExploreState() {
        return exploreState;
    }

    @Override
    public int getNumChoices() throws PrismException {
        return 1;   // DTMC has only 1 choice
    }

    @Override
    public int getNumTransitions(int i) throws PrismException {

        //When dead, we self-loop.
        //When moving we might have paramSupportSize^(NUM_COODS) different transitions.
        if(end){
            return 1;
        }
        else {
            //todo: this is a simple hack for now
            return 3    ;
        }
    }

    @Override
    public Object getTransitionAction(int i) throws PrismException {
        return null;    //No action labels in this model
    }

    @Override
    public Object getTransitionAction(int i, int offset) throws PrismException {
        return null;    //No action labels in this model
    }

    @Override
    public double getTransitionProbability(int i, int offset) throws PrismException {

        //When dead, the state loops with prob. 1.0
        //When moving, each transition is the joint probability of each param. of the Power model.
        if(end){
            return 1.0;
        }
        else{
            //todo: this is a simple hack for now
            int[] offsets = new int[]{offset};

            double jointProb = 1;
            for (double prob: wm.getProbabilities(offsets)) {
                jointProb *= prob;
            }
            return jointProb;
        }
    }

    @Override
    public State computeTransitionTarget(int k, int offset) throws PrismException {
        State target = new State(exploreState);

        if(!end){
            if(waypointIndex == displacementVectors.size()){
                System.out.println("COMPLETED MISSION: trajectory completed");
                return target.setValue(0, (batteryAmount))
                        .setValue(1,true).setValue(2,waypointIndex + 1);
            }
            else {

                // threshold not reached & waypoint not final
                System.out.println("CURRENT STATUS: Plan not completed, battery remaining: " + batteryAmount + " wattHrs");
                //todo offset is simple hack for now

                double remainingBattery = batteryAmount;
                remainingBattery  = (int) (remainingBattery - wm.getAngularWork(rotations.get(waypointIndex), new int[]{offset}));
                remainingBattery =  (int) (remainingBattery - wm.getTangentialWork(displacementVectors.get(waypointIndex), new int[]{offset}));
                System.out.println("DEPLETING BATTERY: Remaining battery level after displacement: " + remainingBattery  + " wattHrs \n");


                return target.setValue(0, (remainingBattery < 0 ? -1 : (int) remainingBattery)) //casting to int is important here
                        .setValue(1,remainingBattery < 0)
                        .setValue(2,waypointIndex + 1);
            }
        }
        else {
            System.out.println("CURRENT STATUS: UUV is stationary \n");
            return target;
        }
    }

    @Override
    public ModelType getModelType() {
        return ModelType.DTMC;
    }

    @Override
    public int getNumVars() {
        return 1;   // num probabilistic variables
    }

    @Override
    public List<String> getVarNames() {
        return Arrays.asList("batteryAmount","end","waypointIndex");
    }

    @Override
    public List<Type> getVarTypes() {
        return Arrays.asList(TypeInt.getInstance(), TypeBool.getInstance());
    }

    @Override
    public VarList createVarList() throws PrismException {
        VarList varList = new VarList();
        try {
            varList.addVar(new Declaration("batteryAmount", new DeclarationInt(Expression.Int(-1), Expression.Int(initialBatteryAmount))), 0, null);
            varList.addVar(new Declaration("end", new DeclarationBool()), 0, null);
            varList.addVar(new Declaration("waypointIndex", new DeclarationInt(Expression.Int(0), Expression.Int(displacementVectors.size()))), 0, null);
        } catch (PrismLangException e) {
            e.printStackTrace();
        }
        return varList;
    }

    @Override
    public int getNumLabels()
    {
        return 1;
    }

    @Override
    public List<String> getLabelNames()
    {
        return Arrays.asList("home");
    }

    @Override
    public boolean isLabelTrue(int i) throws PrismException
    {
        switch (i) {
            // "home"
            case 0:
                return (batteryAmount >= 0 & end);
        }
        // Should never happen
        return false;
    }

}


// references: geodetic to EFEC formula - Coordinate systems and units in HiSPARC, http://docs.hisparc.nl/coordinates/HiSPARC_coordinates.pdf