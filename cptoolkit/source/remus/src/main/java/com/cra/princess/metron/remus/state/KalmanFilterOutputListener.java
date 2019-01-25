package com.cra.princess.metron.remus.state;

public interface KalmanFilterOutputListener {
	public void kalmanFilterOutputUpdate(com.cra.princess.messaging.types.Location location);
}
