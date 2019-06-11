package com.cra.princess.metron.remus.perturbation;

import com.cra.princess.messaging.RemusBatteryPerturbation;

public interface BatteryPerturbationListener {
	public void batteryPerturbationUpdate(RemusBatteryPerturbation perturbation);
}
