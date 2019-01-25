package com.cra.brass.testharness;

import javax.json.*;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import com.cra.princess.evaluation.messages.*;
import org.apache.log4j.Logger;

import com.cra.princess.evaluation.util.EvaluationUtils;
import scala.collection.immutable.List;
import scala.collection.immutable.List$;

import java.io.*;
import java.net.URL;

/**
 * The implementation of the ReSTful interface for the CP3 mock BRASS Test Harness service
 * <br><br>
 * @author Michael Reposa (mreposa@cra.com)
 */

@Path("/brass-th/cp3")
public class CP3TestHarnessServiceResource {
	private final static Logger LOG = Logger.getLogger(CP3TestHarnessServiceResource.class.getName());

	private final static String VERSION_TITLE = "BRASS CP3 Mock Test Harness Service";
	private final static String VERSION_NUMBER = "1.2.0";
	private final static String VERSION_MESSAGE = VERSION_TITLE + " " + VERSION_NUMBER;

	private final static String JSON_CONFIG_DIR = "config";
	private final static String DEFAULT_CONFIG = "default";

	private final static String INITIAL_PARAMS_FILE = "cp3-initialParams.json";
	private final static String BATTERY_PERTURBATIONS_FILE = "cp3-batteryPerturbations.json";

	private String configPath = JSON_CONFIG_DIR + "/" + DEFAULT_CONFIG;

	public CP3TestHarnessServiceResource() {
	}

	@Path("/version")
	@GET
	@Produces(MediaType.TEXT_PLAIN)
	public Response getVersionAsText() {
		LOG.info("Service version requested as text");
		return Response.ok(VERSION_MESSAGE, MediaType.TEXT_PLAIN).build();
	}
	
	@Path("/error")
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.TEXT_PLAIN)
	public Response processError(String json)
	{
		LOG.info("DAS Error");
		LOG.info("JSON Content = " + json);
		
		Response response = Response.ok().build();
		try {
			ErrorMessage errMsg = ErrorMessage$.MODULE$.fromJson(json);
			String timestamp = errMsg.Timestamp();
			if (!EvaluationUtils.validateTimestamp(timestamp)) {
				response = Response.status(400).build();
			}
			String errorType = errMsg.Error();
			if (!EvaluationUtils.validateErrorType(errorType)) {
				response = Response.status(400).build();
			}
		}
		catch(SerializationException e) {
			LOG.error(e);
			response = Response.status(400).build();
		}

		// Send the Response
		return response;
	}

	@Path("/config")
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.TEXT_PLAIN)
	public Response processConfig(String config)
	{
		Response response = Response.ok().build();
		if (config != null && config.isEmpty() == false) {
			LOG.info("Setting CP3 JSON Configuration to " + config);
			this.configPath = JSON_CONFIG_DIR + File.separator + config;
		}

		// Send the Response
		return response;
	}

	@Path("/ready")
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.APPLICATION_JSON)
	public Response processReady(String json)
	{
		LOG.info("DAS CP3 Ready");
		LOG.info("JSON Content = " + json);

		Response response;
		try {
			ReadyMessage rMsg = ReadyMessage$.MODULE$.fromJson(json);
			String timestamp = rMsg.Timestamp();
			if (!EvaluationUtils.validateTimestamp(timestamp)) {
				response = Response.status(400).build();
			}
			else {
				// Load the config file
				FileReader fr = null;
				String path = this.configPath + "/" + INITIAL_PARAMS_FILE;
				try {
					fr = new FileReader(path);
				} catch (IOException e) {
					LOG.warn(e.getMessage());
					fr = null;

					URL url = this.getClass().getClassLoader().getResource(path);
					if (url != null) {
						path = url.getFile();
						try {
							fr = new FileReader(new File(path));
						} catch (IOException e1) {
							fr = null;
						}
					}
					else {
						LOG.error("Invalid URL: " + path);
					}
				}

				// Read and return JSON InitialParams
				if (fr != null) {
					JsonReader reader = null;
					try {
						reader = Json.createReader(fr);
						JsonObject initialParamsObj = reader.readObject();
						String initialParams = initialParamsObj.toString();

						LOG.debug(initialParams);

						response = Response.ok().entity(initialParams).build();
					} finally {
						if (reader != null) {
							reader.close();
						}
					}
				}
				else {
					LOG.error("Config file could not be loaded: " + path);
					response = Response.status(400).build();
				}
			}
		}
		catch(SerializationException e) {
			LOG.error(e);
			response = Response.status(400).build();
		}

		// Send the Response
		return response;
	}

	@Path("/status")
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.TEXT_PLAIN)
	public Response processStatus(String json)
	{
		LOG.info("DAS Status");
		LOG.info("JSON Content = " + json);

		Response response = Response.ok().build();
		//JsonReader reader = null;
		try (JsonReader reader = Json.createReader(new StringReader(json))) {
			JsonObject object = reader.readObject();
			String timestamp = object.getString(EvaluationUtils.FIELD_TIME);
			if (!EvaluationUtils.validateTimestamp(timestamp)) {
				response = Response.status(400).build();
			}
			String statusType = object.getString(EvaluationUtils.FIELD_STATUS);
			if (!EvaluationUtils.validateStatusType(statusType)) {
				response = Response.status(400).build();
			}
		}
		catch(JsonException e) {
			LOG.error(e);
			response = Response.status(400).build();
		}

		// Send the Response
		return response;
	}

	@Path("/done")
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.TEXT_PLAIN)
	public Response processResults(String json)
	{
		LOG.info("DAS Done");
		LOG.info("JSON Content = " + json);

		Response response = Response.ok().build();
		try {
            CP3SutFinishedStatus finished = CP3SutFinishedStatus$.MODULE$.fromJson(json);
			String timestamp = finished.Timestamp();
			if (!EvaluationUtils.validateTimestamp(timestamp)) {
				response = Response.status(400).build();
			}
			else {
				CP3ResultsType results = finished.Results();
				if (results == null) {
					response = Response.status(400).build();
				}
			}
		}
		catch(SerializationException e) {
			LOG.error(e);
			response = Response.status(400).build();
		}

		// Send the Response
		return response;
	}
	
    @Path("/path")
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response processPathMessage(String json)
    {
        LOG.info("DAS Path");
        LOG.info("JSON Content = " + json);

        Response response = Response.ok().build();
        try {
            SearchPath searchPath = SearchPath$.MODULE$.fromJson(json);
            String timestamp = searchPath.Timestamp();
            if (!EvaluationUtils.validateTimestamp(timestamp)) {
                response = Response.status(400).build();
            }
            else {
                double maxSpeed = Double.parseDouble(searchPath.MaxSpeed());
                List waypoints = searchPath.Waypoints();
                if (waypoints == null) {
                    response = Response.status(400).build();
                }
                else {
					// Load the config file
					FileReader fr = null;
					String path = this.configPath + "/" + BATTERY_PERTURBATIONS_FILE;
					try {
						fr = new FileReader(path);
					} catch (IOException e) {
						LOG.warn(e.getMessage());
						fr = null;

						URL url = this.getClass().getClassLoader().getResource(path);
						if (url != null) {
							path = url.getFile();
							try {
								fr = new FileReader(new File(path));
							} catch (IOException e1) {
								fr = null;
							}
						}
						else {
							LOG.error("Invalid URL: " + path);
						}
					}

					// Read and return JSON InitialParams
					if (fr != null) {
						JsonReader reader = null;
						try {
							reader = Json.createReader(fr);
							JsonObject batteryPerturbationsObj = reader.readObject();
							String batteryPerturbations = batteryPerturbationsObj.toString();

							LOG.debug(batteryPerturbations);

							response = Response.ok().entity(batteryPerturbations).build();
						} finally {
							if (reader != null) {
								reader.close();
							}
						}
					}
					else {
						LOG.error("Config file could not be loaded: " + path);
						response = Response.status(400).build();
					}
                }
            }
        }
        catch(SerializationException e) {
            LOG.error(e);
            response = Response.status(400).build();
        }

        // Send the Response
        return response;
    }
}
