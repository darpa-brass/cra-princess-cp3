package com.cra.princess.monitor

class MonitorException(message: String = null, cause: Throwable = null) extends Exception {
  def this() = this("", null)
  def this(message: String) = this(message, null)
  def this(cause: Throwable) = this("", cause)
}