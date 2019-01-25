package com.cra.princess.metron.remus.state;

public class SystemRuntimeState {
    public static final String RUNTIME_TOPIC = "princess.runtime";

    public static final String DATA_FIELD_MESSAGE_TYPE = "messageType";
    public static final String DATA_FIELD_MESSAGE_CONTENT = "messageContent";

    private String messageType;
    private String messageContent;

    public SystemRuntimeState(String messageType, String messageContent) {
        this.messageType = messageType;
        this.messageContent = messageContent;
    }

	public String getMessageType() {
		return messageType;
	}

	public String getMessageContent() {
		return messageContent;
	}
}
