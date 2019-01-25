package com.cra.princess.simulation.events;

public interface Consumer<T> {
    public void consume(T message);
}
