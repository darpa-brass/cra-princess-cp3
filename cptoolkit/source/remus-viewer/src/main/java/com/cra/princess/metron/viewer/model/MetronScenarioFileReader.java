package com.cra.princess.metron.viewer.model;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonException;
import javax.json.JsonObject;
import javax.json.JsonReader;

import com.cra.princess.metron.viewer.model.components.*;

public class MetronScenarioFileReader implements ScenarioFileReader {
	private File scenarioFile = null;
	
	private JsonObject origin = null;
	private JsonObject destination = null;
	private JsonArray regions = null;
	private JsonObject searchArea = null;
	private JsonArray searchObjectLocations = null;
	private JsonObject initialConfig = null;
	private JsonObject time = null;
	private double oceanDepth = 100.0;

	public MetronScenarioFileReader(File scenarioFile) throws IOException
	{
		this.scenarioFile = scenarioFile;
		FileReader fr = new FileReader(scenarioFile);
		JsonReader reader = Json.createReader(fr);
		try {
			JsonObject scenarioObject = reader.readObject();
			validateScenarioFile(scenarioObject);
		}
		catch(JsonException e) {
			// Re-throw as IOException so client doesn't need to be aware of JSON
			throw new IOException(e);
		}
		finally {
			reader.close();
		}
	}

	private void validateScenarioFile(JsonObject scenarioObject) throws IOException {
		String message = "Invalid Metron REMUS scenario file";

		if (scenarioObject == null) {
			throw new IOException(message);
		}

		try {
			this.origin = scenarioObject.getJsonObject("vehicle").getJsonObject("config").getJsonObject("origin");
			this.destination = scenarioObject.getJsonObject("mission").getJsonObject("destination");
			this.regions = scenarioObject.getJsonObject("world").getJsonObject("current").getJsonObject("config").getJsonArray("regions");
			this.searchArea = scenarioObject.getJsonObject("mission").getJsonObject("searcharea");
			this.searchObjectLocations = scenarioObject.getJsonObject("world").getJsonObject("object").getJsonObject("config").getJsonArray("objects");
			this.oceanDepth = scenarioObject.getJsonObject("world").getJsonObject("bathymetry").getJsonObject("config").getJsonNumber("defaultDepth").doubleValue();
			this.initialConfig = scenarioObject.getJsonObject("vehicle").getJsonObject("config").getJsonObject("ic");
			this.time = scenarioObject.getJsonObject("time");
		}
		catch (NullPointerException e) {
			throw new IOException(message);
		}
	}
	
	@Override
	public File getScenarioFile() {
		return scenarioFile;
	}
	
	@Override
	public Origin getRemusOrigin() {
		Origin location = null;
		
		if (origin != null) {
			location = new Origin(origin.getJsonNumber("lat").doubleValue(),
				origin.getJsonNumber("lon").doubleValue(),
				origin.getJsonNumber("depth").doubleValue());			
		} else {
			throw new RuntimeException("ERROR: scenario does not contain a REMUS origin");
		}

		return location;
	}

	@Override
	public Destination getRemusDestination() {
		Destination location = null;
		
		if (destination != null) {
			location = new Destination(destination.getJsonNumber("lat").doubleValue(),
				destination.getJsonNumber("lon").doubleValue(),
				destination.getJsonNumber("depth").doubleValue());
		} else {
			throw new RuntimeException("ERROR: scenario does not contain a REMUS destination");
		}

		return location;
	}

	@Override
	public List<PerturbingCurrent> getPerturbingCurrents() {
		List<PerturbingCurrent> regionList = new ArrayList<PerturbingCurrent>();

		if (regions.isEmpty() == false) {
			for (int i = 0; i < regions.size(); i++) {
				JsonObject region = regions.getJsonObject(i);
				PerturbingCurrent perturbingCurrent = new PerturbingCurrent(region.getJsonNumber("sLat").doubleValue(),
					region.getJsonNumber("wLon").doubleValue(),
					region.getJsonNumber("nLat").doubleValue(),
					region.getJsonNumber("eLon").doubleValue(),
					region.getJsonNumber("vE").doubleValue(),
					region.getJsonNumber("vN").doubleValue());
				regionList.add(perturbingCurrent);
			}
		}
		
		return regionList;
	}

	public SearchArea getSearchArea() {
		SearchArea area = null;

		if (searchArea != null) {
			area = new SearchArea(searchArea.getJsonNumber("sLat").doubleValue(),
				searchArea.getJsonNumber("wLon").doubleValue(),
				searchArea.getJsonNumber("nLat").doubleValue(),
				searchArea.getJsonNumber("eLon").doubleValue());
		}

		return area;
	}

	public SearchObject getSearchObjectLocation() {
		SearchObject location = null;

		if (searchObjectLocations.isEmpty() == false) {
			// Use the first location in the list
			JsonObject object = searchObjectLocations.getJsonObject(0);

			if (object != null) {
				location = new SearchObject(object.getJsonNumber("lat").doubleValue(), object.getJsonNumber("lon").doubleValue(), oceanDepth);
			}
		}

		return location;
	}

	public Double getInitialHeading() {
		Double value = 0.0;
		if (initialConfig != null) {
			value = initialConfig.getJsonNumber("heading").doubleValue();
		}
		return value;
	}

	public Double getInitialPitch() {
		Double value = 0.0;
		if (initialConfig != null) {
			value = initialConfig.getJsonNumber("pitch").doubleValue();
		}
		return value;
	}

	public Double getInitialSpeed() {
		Double value = 0.0;
		if (initialConfig != null) {
			value = initialConfig.getJsonNumber("speed").doubleValue();
		}
		return value;
	}

	public Double getScenarioPlaybackSpeed() {
		Double value = 1.0;
		if (time != null) {
			value = time.getJsonNumber("acceleration").doubleValue();
		}
		return value;
	}
}
