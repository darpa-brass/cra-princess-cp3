package com.cra.princess.models.kalmanfiltercomponents;

import java.io.Serializable;

public class KalmanFilterEnvironment implements Serializable {

  	private static final long serialVersionUID = 1L;
    private Double xCurrent;
    private Double yCurrent;
	
	public KalmanFilterEnvironment(Double xCurrent, Double yCurrent)
	{
	  this.xCurrent = xCurrent;
	  this.yCurrent = yCurrent;
	}
	
	public KalmanFilterEnvironment()
	{
	  this(0.0, 0.0);
	}

    public Double getxCurrent()
    {
      return xCurrent;
    }
  
    public Double getyCurrent()
    {
      return yCurrent;
    }

}
