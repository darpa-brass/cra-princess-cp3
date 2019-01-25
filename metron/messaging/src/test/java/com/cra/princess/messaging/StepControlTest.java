package com.cra.princess.messaging;

/**
 * Test time stepping
 * @author gratton
 *
 */
public class StepControlTest {
	public static void main(String[] args) {		
		StepMessage hundred = new StepMessage(100L);
		StepMessage twoHundred = new StepMessage(200L);			
		try {
			JmsManager.sendStepMessage(hundred);			
			JmsManager.sendStepMessage(hundred);
			JmsManager.sendStepMessage(hundred);
			
			Thread.sleep(1000);
			JmsManager.sendStepMessage(hundred);
			JmsManager.sendStepMessage(hundred);
			JmsManager.sendStepMessage(hundred);				
			Thread.sleep(1000);
			for (int i=0; i<50; i++) {
				JmsManager.sendStepMessage(twoHundred);
			}						
		}
		catch (Exception e) {
			System.err.println(e.getMessage());
		}		
		JmsManager.stop();
	}
}