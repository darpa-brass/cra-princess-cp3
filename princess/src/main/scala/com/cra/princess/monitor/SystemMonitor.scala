package com.cra.princess.monitor

import com.cra.princess.Metric
import com.cra.princess.core.{FailureData, Intent, IntentResult}
import com.cra.princess.util.Logs

import scala.collection.mutable
import scala.collection.mutable.ListBuffer

class SystemMonitor(metricNames: List[String], intent: Intent) extends Logs {

  private val listeners: mutable.ListBuffer[IntentResultListener] = ListBuffer.empty
  def addListener(listener: IntentResultListener) = listeners += listener

  private val map: mutable.Map[String, Metric] = mutable.Map.empty

  private def currentState: List[Metric] = metricNames.map(s => map(s))

  def updateMetric(name: String, value: Metric) = {
    if (!metricNames.contains(name)) throw new IllegalArgumentException(s"Illegal metric: $name")
    map(name) = value
    log.debug(s"System monitor received metric: $name = $value")

    val result = intent.evaluateIntentState(this.currentState)

    // For now, we're only notifying if there's a failure, but the code is set up so that we can notify on
    // any kind of Intent result
    if (!result.pass) {
      log.info("System intent violation detected")
      notifyListeners(result)
    }
  }

  private def notifyListeners(result: IntentResult) = listeners.foreach(_(result))
}
