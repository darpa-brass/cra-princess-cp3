package com.cra.princess.metron.viewer.model;

import java.io.File;
import java.util.List;

import com.cra.princess.metron.viewer.model.components.*;

/**
 * An interface for scenario-specific data required for initialization
 * 
 */

public interface ScenarioFileReader {
	public File getScenarioFile();
	public Origin getRemusOrigin();
	public Destination getRemusDestination();
	public Double getInitialHeading();
	public Double getInitialPitch();
	public Double getInitialSpeed();
	public List<PerturbingCurrent> getPerturbingCurrents();
	public SearchArea getSearchArea();
	public SearchObject getSearchObjectLocation();
	public Double getScenarioPlaybackSpeed();
}
