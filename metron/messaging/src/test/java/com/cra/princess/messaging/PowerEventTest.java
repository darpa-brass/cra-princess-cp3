package com.cra.princess.messaging;

/**
 * Test time stepping
 * @author gratton
 *
 */
public class PowerEventTest {
	public static void main(String[] args) {		
		StepMessage hundred = new StepMessage(100L);
		StepMessage twoHundred = new StepMessage(200L);			
		try {
			JmsManager.sendStepMessage(hundred);			
			JmsManager.sendStepMessage(hundred);
			JmsManager.sendStepMessage(hundred);
			JmsManager.sendPowerPerturbation(new RemusBatteryPerturbation(0.99, 0, 1100));						
			Thread.sleep(1000);
			for (int i=0; i<60; i++) {
				JmsManager.sendStepMessage(twoHundred);
			}						
		}
		catch (Exception e) {
			System.err.println(e.getMessage());
		}		
		JmsManager.stop();
	}
}