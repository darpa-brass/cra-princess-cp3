package com.cra.princess.metron.remus.state;

public class SystemRuntimeError {
    public static final String ERROR_TOPIC = "princess.error";

    public static final String DATA_FIELD_MESSAGE_TYPE = "messageType";
    public static final String DATA_FIELD_MESSAGE_CONTENT = "messageContent";

    private String errorType;
    private String errorContent;

    public SystemRuntimeError(String messageType, String messageContent) {
        this.errorType = messageType;
        this.errorContent = messageContent;
    }

	public String getErrorType() {
		return errorType;
	}

	public String getErrorContent() {
		return errorContent;
	}
}
