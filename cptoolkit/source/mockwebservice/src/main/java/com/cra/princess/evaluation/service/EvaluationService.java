package com.cra.princess.evaluation.service;

import com.sun.grizzly.http.SelectorThread;
import com.sun.jersey.api.container.grizzly.GrizzlyServerFactory;
import com.sun.jersey.api.core.PackagesResourceConfig;

import java.io.IOException;

public final class EvaluationService {
	private static SelectorThread server = null;

	public EvaluationService() {
	}
	
	public static void main(String args[]) throws IllegalArgumentException, IOException {
		// Create and start a local Grizzly HTTP server
		server = GrizzlyServerFactory.create("http://localhost:8081/", new PackagesResourceConfig("com.cra.princess.evaluation.service"));
	}

	public static SelectorThread getServer() {
		return server;
	}
}
