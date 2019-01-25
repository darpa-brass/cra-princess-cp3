package com.cra.brass.testharness;

import java.util.HashSet;
import java.util.Set;

import javax.ws.rs.core.Application;

/**
 * The Jersey application for the CP1 mock BRASS Test Harness service
 * <br><br>
 * @author Michael Reposa (mreposa@cra.com)
 */

public final class TestHarnessService extends Application {
	@Override
	public Set<Class<?>> getClasses() {
		Set<Class<?>> s = new HashSet<Class<?>>();

		s.add(CP2TestHarnessServiceResource.class);
		s.add(CP3TestHarnessServiceResource.class);

		return s;
	}
}
