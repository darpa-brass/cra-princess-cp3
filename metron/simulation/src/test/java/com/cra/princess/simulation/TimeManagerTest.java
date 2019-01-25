package com.cra.princess.simulation;

import java.util.Date;

import com.cra.princess.simulation.TimeManager.TimeStepped;

public class TimeManagerTest {
    public static void main(String[] args) {
        TimeStepped timeLogger = new TimeStepped() {
            long initialTime = 0;
            @Override
            public void initialize() {
                initialTime = TimeManager.now();
                System.out.println("Initialized at time " + new Date(initialTime));
            }

            @Override
            public void update() {
                long elapsed = TimeManager.now() - initialTime;
                long wallElapsed = System.currentTimeMillis() - initialTime;
                System.out.println(elapsed + "ms have passed in simulation, " + wallElapsed + " ms actual");
            }

            @Override
            public void reset() {
                System.out.println("Reset called.");
                initialTime = 0;
            }

            @Override
            public void stop() {
            }
        };
        
        
        TimeManager.addStepper(timeLogger);
        TimeManager.setTime(new Date().getTime());
        TimeManager.initialize();
        TimeManager.setSpeedup(0.5);
        TimeManager.run(10000, 200);
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
        }
        TimeManager.pause();
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
        }
        TimeManager.resume();
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
        }
        TimeManager.stop();
    }
}