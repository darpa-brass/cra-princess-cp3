package com.cra.princess.testharness.component_interface;

/**
 * PRINCESS Intent Lab test harness interface
 * 
 * @author Gerald Fry
 */
public interface ComponentInterface {
	
	/** 
	   * Execute component once and calculate metric values
	   * 
	   * @param inputData Input data set
	   * @return List of Objects containing component outputs
	   */
	  public java.util.List<Object> execute(java.util.List<Object> inputData);
	  
	  /** 
	   * Calculate metrics
	   * 
	   * @param outputValues Output values of component execution
	   *  @param truthValues Component-generated truth values
	   * @return List of Objects containing computed values of metrics
	   */
	  public java.util.List<Object> calculateMetrics(java.util.List<Object> outputValues, java.util.List<Object> truthValues);
	  
	  /**
	   * Generate an input data set
	   * @param genericProperties Generic parameters for data set generation (e.g., number of data points)
	   * @return List of Objects containing generated input values
	   */
	  public java.util.List<Object> generateDataSet(java.util.List<Object> genericProperties);
	  
	  /**
	   * Generate truth values 
	   * 
	   * @return List of Objects containing generated truth values
	   */
	  public java.util.List<Object> generateTruthValues();
	  
	  /**
	   * Generate values for control variables
	   * 
	   * @return List of Objects containing generated control variable values
	   */
	  public java.util.List<Object> generateControlVars();
	  
	  /**
	   *  Set control variable values to use in subsequent executions
	   * 
	   * @param controlValues Values for control variables
	   */
	  public void setControlVars(java.util.List<Object> controlValues);

}
