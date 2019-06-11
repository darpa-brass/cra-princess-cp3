package com.cra.princess.simulation.events;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.cra.princess.messaging.JmsManager.MessageHandler;

public class EventDispatcher {
	private static Map<Class<?>, List<MessageHandler<?>>> consumers = new HashMap<>();
    
    @SuppressWarnings("unchecked")
    public static synchronized <T> void publishEvent(T o) {
        List<MessageHandler<?>> list = consumers.get(o.getClass());
        if (list == null) {
            return;
        }
        for (MessageHandler<?> consumer : list) {
            ((MessageHandler<T>) consumer).handleMessage(o);
        }
    }
    
    public static synchronized <T> void registerConsumer(Class<T> clazz, MessageHandler<T> consumer) {
        List<MessageHandler<?>> list = consumers.get(clazz);
        if (list == null) {
            list = new ArrayList<MessageHandler<?>>();
            consumers.put(clazz, list);
        }
        list.add(consumer);
    }
    
    public static synchronized void clearConsumers() {
        for (List<MessageHandler<?>> consumerList : consumers.values()) {
            consumerList.clear();
        }
    }
} 
