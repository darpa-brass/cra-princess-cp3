package com.cra.princess.messaging;

/**
 * The simplest possible round-trip test of message send/receive.
 * @author chagnon
 *
 */
public class SimulationControlTest {
	public static void main(String[] args) {
		boolean doPlayControlTest = true;
		if (doPlayControlTest) {
			SimulationControlMessage pause = SimulationControlMessage.pause();
			SimulationControlMessage play = SimulationControlMessage.play();
			SimulationControlMessage stop = SimulationControlMessage.stop();
			try {
				Thread.sleep(2000);
				System.out.println("Pausing...");
				JmsManager.sendSimulationControlMessage(pause);
				Thread.sleep(2000);
				System.out.println("Playing...");
				JmsManager.sendSimulationControlMessage(play);
				Thread.sleep(2000);
				System.out.println("Pausing...");
				JmsManager.sendSimulationControlMessage(pause);
				Thread.sleep(2000);
				System.out.println("Playing...");
				JmsManager.sendSimulationControlMessage(play);
				Thread.sleep(2000);
				System.out.println("Stopping...");
				JmsManager.sendSimulationControlMessage(stop);
			}
			catch (Exception e) {
				System.err.println(e.getMessage());
			}
		} else { // speed control
			SimulationControlMessage speed = SimulationControlMessage.play(2.0);			
			try {
				Thread.sleep(2000);
				System.out.println("Speed up!");
				JmsManager.sendSimulationControlMessage(speed);
				Thread.sleep(2000);
				speed.simSpeed = 0.5;
				System.out.println("Slow down.");
				JmsManager.sendSimulationControlMessage(speed);						
			} catch (Exception e) {
				System.err.println(e.getMessage());
			}
		}
		JmsManager.stop();
    }
}