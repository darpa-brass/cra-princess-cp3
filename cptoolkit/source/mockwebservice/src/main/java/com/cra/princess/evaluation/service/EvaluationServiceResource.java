package com.cra.princess.evaluation.service;

import org.apache.log4j.Logger;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

/**
 * The implementation of the ReSTful interface for PRINCESS Evaluation service
 * <br><br>
 * @author Michael Reposa (mreposa@cra.com)
 */

@Path("/princess")
public class EvaluationServiceResource {
	private final static Logger LOG = Logger.getLogger(EvaluationServiceResource.class.getName());

	private static Boolean alive = true;

	public EvaluationServiceResource() {
	}

	@Path("/alive")
	@GET
	@Produces(MediaType.TEXT_PLAIN)
	public Response getAlive() {
		LOG.debug("Alive = " + alive.toString().toUpperCase());
		return Response.ok(alive.toString().toUpperCase(), MediaType.TEXT_PLAIN).build();
	}
	
	@Path("/setAlive/{aliveValue}")
	@GET
	@Consumes(MediaType.TEXT_PLAIN)
	public Response setAlive(@PathParam("aliveValue") Boolean aliveValue)
	{
		LOG.debug("Setting Alive = " + aliveValue);

		alive = aliveValue.booleanValue();

		LOG.debug("Alive = " + alive.toString().toUpperCase());

		return Response.ok().build();
	}
}
