package com.cra.princess.messaging;

import javax.jms.MapMessage;

public interface MappableMessage {
    void set(MapMessage message);
    MapMessage toMapMessage();
}
