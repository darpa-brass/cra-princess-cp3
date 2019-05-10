package com.cra.princess.remusclient

import com.cra.princess.util.Logs

class FinishedSignaller(handler: () => Unit) extends Logs {

  private var analysisFinished = false
  private var runFinished = false

  def setRunFinished(): Unit = {
    this.synchronized {
      log.debug("setting run finished")
      runFinished = true
      if (this.analysisFinished && this.runFinished) {
        this.analysisFinished = false
        this.runFinished = false
        log.debug("invoking handler")
        handler()
      }
    }
  }

  def setAnalysisFinished(): Unit = {
    this.synchronized {
      log.debug("setting analysis finished")
      analysisFinished = true
      if (this.analysisFinished && this.runFinished) {
        this.analysisFinished = false
        this.runFinished = false
        log.debug("invoking handler")
        handler()
      }
    }
  }

}
