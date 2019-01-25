package com.cra.princess.localizationalgorithm.components;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.math3.linear.ArrayRealVector;
import org.apache.commons.math3.linear.RealVector;
import org.apache.commons.math3.util.Pair;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;


/**
 * Wrapper around the predicted state vector of the Kalman Filter <p> 
 * Contains the following: <br> 
 * <b>stateDeltas</b> - Components affected directly by sampling period  <br>
 * <b>stateComponents </b>- Components that are updated by the delta components<br>
 * <b>componentDimension</b> - equivalent to half the total dimension of entire state<br>
 * since values for both must be submitted as pairs, indices will match! <br>
 */
public class ComponentState implements Serializable{

    private static final long serialVersionUID = 1L;

    private RealVector stateDeltas;

    private RealVector stateComponents;
    private int componentDimension;

    /** For serialization only */
    public ComponentState() {

    }
    public ComponentState(RealVector stateComponents, RealVector stateDeltas){
        this.stateComponents = stateComponents;
        this.stateDeltas = stateDeltas;
        if(stateComponents.getDimension() != stateDeltas.getDimension())
            throw new IllegalArgumentException("Dimensions of state and deltas should be equal!");
        this.componentDimension = stateComponents.getDimension();
    }
    public ComponentState(List<Pair<Double,Double>> stateAndDeltaValues){
        this.setStateAndDeltaComponents(stateAndDeltaValues);
        this.componentDimension = stateAndDeltaValues.size();
    }

    public ComponentState(RealVector newState, int componentDim){
        this.setStateAndDeltaComponents(newState, componentDim);
        this.componentDimension = componentDim;
    }
    /**
     * Helper function for the constructor and for updating the state
     * Note that if a state doesn't change, its delta should be zero
     * @param stateAndDeltaValues - list of pairs(state value, delta value)
     */
    public void setStateAndDeltaComponents(List<Pair<Double,Double>> stateAndDeltaValues) {
        double[] states = new double[stateAndDeltaValues.size()];
        double[] deltas = new double[stateAndDeltaValues.size()];
        for(int i=0;i<stateAndDeltaValues.size();i++){
            states[i] = stateAndDeltaValues.get(i).getFirst();
            deltas[i] = stateAndDeltaValues.get(i).getSecond();
        }
        this.stateComponents = new ArrayRealVector(states);
        this.stateDeltas = new ArrayRealVector(deltas);
    }
    /**
     * If taking in a vector, we convert it into a list of pairs 
     * Then we run setStateAndDeltaComponents on the list of pairs
     * @param newState the vector
     * @param componentDim dimensions
     */
    public void setStateAndDeltaComponents(RealVector newState, int componentDim) {
        this.setStateAndDeltaComponents(this.convertToStateUpdateInputs(newState, componentDim));
    }
    /**
     * @param newState - Xn 
     * @param componentDim - dimension of state/delta component 
     * @return reformatted input for updating currentState
     */
    private List<Pair<Double, Double>> convertToStateUpdateInputs(RealVector newState, int componentDim){
        if(newState.getDimension() != 2*componentDim)
            throw new IllegalArgumentException(String.format("newState dim is %s but needs to be 2*ComponentDim, component dim is %s!", newState.getDimension(), componentDim));
        List<Pair<Double, Double>> toReturn = new ArrayList<Pair<Double, Double>>();
        for(int i=0;i<componentDim; i++){
            toReturn.add(new Pair<Double,Double>(newState.getEntry(i), newState.getEntry(i + componentDim)));
        }
        return toReturn;
    }


    public RealVector getCombinedState(){
        return this.stateComponents.append(stateDeltas);
    }

    /** Retrieves a copy of the state / position components
     * @return a vector of state components
     */
    public RealVector getStateComponents() {
        return this.stateComponents.copy();
    }

    public RealVector getDeltaComponents() {
        return this.stateDeltas.copy();
    }

    public int getComponentDimension() {
        return componentDimension;
    }

    @Override
    public String toString() {
        return "ComponentState(states=[" + StringUtils.join(this.stateComponents.toArray(), ',') + "], " +
                "deltas=[" + StringUtils.join(this.stateDeltas.toArray(), ',') + "])";
    }

    public void updateStateComponent(int index, double value) {
        this.stateComponents.setEntry(index, value);
    }

}
