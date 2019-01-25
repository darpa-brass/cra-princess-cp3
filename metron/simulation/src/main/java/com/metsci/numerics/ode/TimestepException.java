package com.metsci.numerics.ode;

public class TimestepException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public TimestepException() {
	}

	public TimestepException(String arg0) {
		super(arg0);
	}

	public TimestepException(Throwable arg0) {
		super(arg0);
	}

	public TimestepException(String arg0, Throwable arg1) {
		super(arg0, arg1);
	}

}
