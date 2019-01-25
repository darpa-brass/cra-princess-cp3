package com.cra.princess.evaluation.service;

import javax.ws.rs.core.Application;
import java.util.HashSet;
import java.util.Set;

/**
 * The Jersey application for the PRINCESS Evaluation service
 * <br><br>
 * @author Michael Reposa (mreposa@cra.com)
 */

public final class EvaluationServiceApplication extends Application {
	@Override
	public Set<Class<?>> getClasses() {
		Set<Class<?>> s = new HashSet<Class<?>>();

		s.add(EvaluationServiceResource.class);

		return s;
	}
}
