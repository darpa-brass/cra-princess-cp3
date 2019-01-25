package com.cra.princess.util

import org.apache.log4j._

trait Logs {

  @transient lazy val log = Logger.getLogger(getClass().getName());

}