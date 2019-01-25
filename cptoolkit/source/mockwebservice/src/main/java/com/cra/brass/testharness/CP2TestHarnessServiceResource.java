package com.cra.brass.testharness;

import com.cra.princess.evaluation.util.EvaluationUtils;
import org.apache.log4j.Logger;

import javax.json.*;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.io.*;
import java.net.URL;

/**
 * The implementation of the ReSTful interface for the CP2 mock BRASS Test Harness service
 * <br><br>
 * @author Michael Reposa (mreposa@cra.com)
 */

@Path("/brass-th/cp2")
public class CP2TestHarnessServiceResource {
	private final static Logger LOG = Logger.getLogger(CP2TestHarnessServiceResource.class.getName());

	private final static String VERSION_TITLE = "BRASS CP2 Mock Test Harness Service";
	private final static String VERSION_NUMBER = "1.2.0";
	private final static String VERSION_MESSAGE = VERSION_TITLE + " " + VERSION_NUMBER;

	private final static String JSON_CONFIG_DIR = "config";
	private final static String DEFAULT_CONFIG = "default";

	private final static String INITIAL_PARAMS_FILE = "cp2-initialParams.json";

	private String configPath = JSON_CONFIG_DIR + File.separator + DEFAULT_CONFIG + File.separator;

	public CP2TestHarnessServiceResource() {
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
		JsonReader reader = null;
		try {
			reader = Json.createReader(new StringReader(json));
			JsonObject object = reader.readObject();
			String timestamp = object.getString(EvaluationUtils.FIELD_TIME);
			if (EvaluationUtils.validateTimestamp(timestamp) == false) {
				response = Response.status(400).build();
			}
			String errorType = object.getString(EvaluationUtils.FIELD_ERROR);
			if (EvaluationUtils.validateErrorType(errorType) == false) {
				response = Response.status(400).build();
			}
		}
		catch(JsonException e) {
			LOG.error(e);
			response = Response.status(400).build();
		}
		finally {
			reader.close();			
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
			LOG.info("Setting CP1 JSON Configuration to " + config);
			this.configPath = JSON_CONFIG_DIR + File.separator + config + File.separator;
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
		LOG.info("DAS CP2 Ready");
		LOG.info("JSON Content = " + json);

		Response response = Response.ok().build();
		JsonReader reader = null;
		try {
			reader = Json.createReader(new StringReader(json));
			JsonObject object = reader.readObject();
			String timestamp = object.getString(EvaluationUtils.FIELD_TIME);
			if (EvaluationUtils.validateTimestamp(timestamp) == false) {
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
					JsonReader ipReader = null;
					try {
						ipReader = Json.createReader(fr);
						JsonObject initialParamsObj = ipReader.readObject();
						String initialParams = initialParamsObj.toString();

						LOG.debug(initialParams);

						response = Response.ok().entity(initialParams).build();
					} finally {
						if (ipReader != null) {
							ipReader.close();
						}
					}
				}
				else {
					LOG.error("Config file could not be loaded: " + path);
					response = Response.status(400).build();
				}
			}
		}
		catch(JsonException e) {
			LOG.error(e);
			response = Response.status(400).build();
		}
		finally {
			reader.close();			
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
		JsonReader reader = null;
		try {
			reader = Json.createReader(new StringReader(json));
			JsonObject object = reader.readObject();
			String timestamp = object.getString(EvaluationUtils.FIELD_TIME);
			if (EvaluationUtils.validateTimestamp(timestamp) == false) {
				response = Response.status(400).build();
			}
			String statusType = object.getString(EvaluationUtils.FIELD_STATUS);
			if (EvaluationUtils.validateStatusType(statusType) == false) {
				response = Response.status(400).build();
			}
		}
		catch(JsonException e) {
			LOG.error(e);
			response = Response.status(400).build();
		}
		finally {
			reader.close();			
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
		LOG.info("DAS Results");
		LOG.info("JSON Content = " + json);

		Response response = Response.ok().build();
		JsonReader reader = null;
		try {
			reader = Json.createReader(new StringReader(json));
			JsonObject object = reader.readObject();
			String timestamp = object.getString(EvaluationUtils.FIELD_TIME);
			if (EvaluationUtils.validateTimestamp(timestamp) == false) {
				response = Response.status(400).build();
			}
			JsonObject results = object.getJsonObject("Results");
			if (results == null || results.isEmpty()) {
				response = Response.status(400).build();
			}
		}
		catch(JsonException e) {
			LOG.error(e);
			response = Response.status(400).build();
		}
		finally {
			reader.close();			
		}

		// Send the Response
		return response;
	}
}
