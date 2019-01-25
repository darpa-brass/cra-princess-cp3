package com.cra.princess.exceptions

/** Signals that a PRINCESS type has been applied in an unsupported context */
class UnsupportedTypeException(message:String, cause:Exception = null) extends RuntimeException(message, cause)