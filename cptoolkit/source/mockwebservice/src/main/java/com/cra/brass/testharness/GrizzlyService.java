package com.cra.brass.testharness;

import java.io.IOException;
import com.sun.grizzly.http.SelectorThread;
import com.sun.jersey.api.container.grizzly.GrizzlyServerFactory;
import com.sun.jersey.api.core.PackagesResourceConfig;

public final class GrizzlyService {
	private static SelectorThread server = null;

	public GrizzlyService() {
	}
	
	public static void main(String args[]) throws IllegalArgumentException, IOException {
		// Create and start a local Grizzly HTTP server
		server = GrizzlyServerFactory.create("http://localhost:8080/", new PackagesResourceConfig("com.cra.brass.testharness"));
	}

	public static SelectorThread getServer() {
		return server;
	}
}
