package com.cra.princess.simulation;

import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.SimulationControlMessage;
import com.cra.princess.messaging.StepMessage;

public class TimeManager {
    private static final Logger LOGGER = Logger.getLogger(TimeManager.class.getName());
    public interface TimeStepped {
        void initialize();

        void update();

        void reset();
        
        void stop();
    }

    private static enum State {
        STARTING, READY, RUNNING, PAUSED, WAITING, STOPPED, STEPPING
    }

    private static State currentState = State.STARTING;
    private static long now = 0L;
    private static final List<TimeStepped> steppers = new ArrayList<>();

    public static void addStepper(TimeStepped stepper) {    	
        if (currentState == State.RUNNING) {
            TimeManager.pause();
        }
        do {
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
            }
        } while (currentState == State.RUNNING);
        steppers.add(stepper);
        TimeManager.resume();
    }

    public static long now() {
        return now;
    }

    static void setTime(long t) {
        switch (currentState) {
        case STARTING:
        case READY:
        case STEPPING :
            now = t;
            break;
        case RUNNING:
        case PAUSED:
        case WAITING:
        case STOPPED:
            throw new RuntimeException("Can't call setTime() until reset() is called.");
        }
    }

    public static void initialize() {
        if (currentState != State.STARTING) {
            throw new RuntimeException("Can't initialize again until reset() is called");
        }
        for (TimeStepped stepper : steppers) {
            stepper.initialize();
        }
        currentState = State.READY;
    }

    private static double speed = 1;    
    public static void setSpeedup(double speed) {
        if (speed <= 0) {
            LOGGER.warning("Speedup must be strictly positive.  Supplied value was '" + speed + "'");
            return;
        }
        TimeManager.speed = speed;
        LOGGER.info("Play speed set to " + speed);
    }
    public static double getSpeedup() {
    	return speed;
    }
    
    private static boolean stopPending = false;

    static void stop() {
    	LOGGER.info("Simulation stopping");
        stopPending = true;
        for (TimeStepped stepper : steppers) {
            stepper.stop();
        }
        currentState = State.STARTING;
    }

    private static boolean pausePending = false;

    static void pause() {
    	if (currentState == State.STEPPING) {
    		LOGGER.info("Pause has no effect in STEPPING mode.");
    		return;
    	}
    	if (currentState != State.PAUSED && !pausePending) {
    		LOGGER.info("Simulation pausing");
    	}
        pausePending = true;
    }

    public static void resume() {
        if (currentState == State.PAUSED) {
        	LOGGER.info("Simulation resuming");
            currentState = State.RUNNING;
        }
        // otherwise ignored
    }

    public static void reset() {
        switch(currentState) {
        case STARTING:        	
            break;
        case READY:
        case STOPPED:
        case STEPPING:
            for (TimeStepped stepper : steppers) {
                stepper.reset();
            }
            break;
        case RUNNING:
        case PAUSED:
        case WAITING:
            stop();
            do {
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                }
            } while (currentState != State.STOPPED && currentState != State.STARTING);
            reset();
            break;
        }
        steppers.clear();
        currentState = State.STARTING;
    }
    
    /**
     * Run the simulation, and block the caller's thread until a certain amount of time has passed, or the simulation is
     * stopped or paused.
     * 
     * @param duration
     *            milliseconds of time to simulate.
     * @param stepSize
     *            time increment between calls to TimeStepped.update();
     */
    static void runAndWait(final long duration, final long stepSize) {
        run(duration, stepSize);
        do {
            try {
                Thread.sleep(stepSize);
            } catch (InterruptedException e) {
            }
        } while (currentState == State.RUNNING || currentState == State.PAUSED);
    }

    /**
     * Start running the simulation, and return to the caller immediately.
     * 
     * @param duration
     *            milliseconds of time to simulate.
     * @param stepSize
     *            time increment between calls to TimeStepped.update();
     */
    static void run(final long duration, final long stepSize) {
        if (currentState == State.READY || currentState == State.WAITING) {
            currentState = State.RUNNING;
        }
        if (currentState != State.RUNNING) {
            throw new RuntimeException("Can't run the simulation now, state is " + currentState);
        }        
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {                                    
                long nSteps = duration / stepSize;
                long sleepDebt = 0;                
                for (int i = 0; i < nSteps; ++i) {
                	boolean unpaused = false;
                	long wallClockStepStart = System.currentTimeMillis();
                    now += stepSize;
                    for (TimeStepped stepper : steppers) {
                        stepper.update();
                    }

                    if (stopPending) {
                        currentState = State.STOPPED;
                        return;
                    }

                    if (pausePending) {
                        pausePending = false;                                            
                        currentState = State.PAUSED;
                        do {
                            try {
                                Thread.sleep(10);
                            } catch (InterruptedException e) {
                            }
                        } while (currentState == State.PAUSED);
                        unpaused = true;
                    }
                    long updateFinished = System.currentTimeMillis();
                    long wallElapsed = updateFinished - wallClockStepStart;
                    long desiredElapsed = (long) (stepSize / speed);
                    long timeToSleep = desiredElapsed - wallElapsed + sleepDebt;
                    LOGGER.finest(String.format("elapsed=%d, desired=%d, sleep=%d, debt=%d\n", wallElapsed, desiredElapsed, timeToSleep, sleepDebt));
                    if (timeToSleep > 5) {
                    	try {
                    		Thread.sleep(timeToSleep);
                    	} catch (InterruptedException e) {
                    	}
                    }
                    long actualSleep = System.currentTimeMillis() - updateFinished;
                    sleepDebt = unpaused? 0 : timeToSleep - actualSleep;                    
                }
                SimulationControlMessage message = SimulationControlMessage.stop();
                message.detail = "Simulation duration complete";
                JmsManager.sendSimulationControlMessage(message);
                currentState = State.WAITING;
                stop();
            }
        }, "TimeManager stepping thread");
        
        t.start();
    }
    
    static void runStepControlled() {        	
    	currentState = State.STEPPING;
    	Thread t = new Thread(new Runnable() {
    		MessageHandler<StepMessage> stepper = new MessageHandler<StepMessage>() {
                public void handleMessage(StepMessage message) {
                	// System.out.format("%d -> %d\n", now, message.timestep_ms);
                	now += message.timestep_ms;                 	
                	for (TimeStepped stepper : steppers) {
                		stepper.update();
                	}            	    
                }
        	};
        	
            @Override
            public void run() {
            	JmsManager.addStepHandler(stepper);
            	LOGGER.info("Starting stepper mode. Awaiting external timestep signal");
            	while(currentState == State.STEPPING) {
            		// ugh. busy wait            		
            		try {
						Thread.sleep(1);
					} catch (InterruptedException e) {
					}					
            	}
            	stop();
            }
    	}, "TimeManager stepping thread");
    	t.start();

    }

}
