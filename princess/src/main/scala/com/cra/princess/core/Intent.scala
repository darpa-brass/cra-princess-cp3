package com.cra.princess.core

import java.lang

import com.cra.princess.util.Logs
import com.cra.princess.{Metric, Threshold}

/**
 *
 * Abstraction of software intent. Contains the following: <p>
 * subIntents (operational requirements )
 * 	- List of intents that must be satisfied or completed <br>
 * 						  In order to satisfy or complete the current intent
 *
 * thresholds
 * 	- Map from intent metric variables to double  <br>
 * 	- State variables must be less than respective threshold to satisfy intent
 */

class Intent protected(val componentId: Int, val description : String, val subIntents : List[Intent],
											 thresholdData: List[ThresholdData])extends Serializable with Logs {

  private val thresholds_ = thresholdData.toBuffer

	/**
	 * Defines an evaluation metric for if an intent is completed/satisfied
		*
		* @param currentMetrics - the current values of the object performing the intent
	 * @return true if each state variable is below its intent threshold, otherwise false
	 */
	def evaluateIntentState(currentMetrics : List[Metric]): IntentResult = {
	  if(currentMetrics == null)
	    log.error("currentMetrics is null")
	  else if(currentMetrics.size == 0){
	    log.warn("current metrics is empty list")
	  }
		// TODO: intent listening...
		if(subIntents.size > 0)
			for(req <- this.subIntents) {
        val result = req.evaluateIntentState(currentMetrics)
        if (!result.pass)
          return result
      }

		for(i <- currentMetrics.indices){
      val t = thresholds_(i)
			t.relation match {
				case tr:LessThan => if (currentMetrics(i) > t.threshold) return IntentResult(componentId, false, Some(FailureData(t.name, currentMetrics(i), t.threshold, tr)))
				case tr:GreaterThan => if (currentMetrics(i) < t.threshold) return IntentResult(componentId, false, Some(FailureData(t.name, currentMetrics(i), t.threshold, tr)))
				case _ => {
					val message = String.format("illegal threshold relation, should be " +
            "greater than or less than, but was %s", t.relation)
					log.error(message)
					throw new IllegalStateException(message)
				}
			}
		}

		return IntentResult(componentId, true)
	}

  def updateThreshold(name: String, value: Threshold): Unit = {
    val index = thresholds_.indexWhere(td => td.name.equals(name))
    if (-1 == index) {
      val errMsg = s"""Cannot update threshold for metric "$name" -- Metric not found in Intent"""
      log.error(errMsg)
      throw new IllegalArgumentException(errMsg)
    }
    else updateThreshold(index, value)
  }

  def updateThreshold(index: Int, value: Threshold): Unit = {
    if (thresholds_.isDefinedAt(index)) this.thresholds_.update(index, thresholds_(index).withValue(value))
    else {
      val errMsg = s"Invalid metric index: $index"
      log.error(errMsg)
      throw new IllegalArgumentException(errMsg)
    }
  }

  def thresholds: List[Threshold] = this.thresholds_.toList.map(_.threshold)

	override def toString() : String = {
		return this.description;
	}

	def equals(that : Intent) : Boolean = {
		return this.thresholds_.equals(that.thresholds_) && this.subIntents.equals(that.subIntents);
	}
}

object Intent extends Logs{
    def apply(componentId: Int, description : String, subIntents : List[Intent],
              thresholdData: List[ThresholdData]) = {
      if(description == null){
        log.error("description is null")
        throw new NullPointerException("Failed to create intent, description was null")
      }
      if(subIntents == null){
        log.error("subIntents is null")
        throw new NullPointerException("Failed to create intent, subIntents was null")
      }
      for(m <- thresholdData){
        if(m.threshold == Double.NaN){
           log.error("threshold is NaN")
           throw new IllegalArgumentException(" Failed to create intent, one of the thresholds was NaN")
        }
      }
      new Intent(componentId, description, subIntents, thresholdData)
    }
}
abstract class ThresholdPurpose
case class SingleInstance() extends ThresholdPurpose
case class AggregateInstances() extends ThresholdPurpose

abstract class ThresholdRelation
case class GreaterThan() extends ThresholdRelation
case class LessThan() extends ThresholdRelation
