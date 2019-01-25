package com.cra.princess.core

import com.cra.princess.util.Logs

import scala.collection.mutable

case class FaultData(dimension: String, timestamp: Long) {}
case class TransformationData(dimension: String, timestamp: Long) {} // TODO these are the same for now, but that will change

trait SensorEventListener {

  def faultDetected(data: FaultData, st: SensorTransformer): Unit
  def transformationStarted(data: TransformationData): Unit
  def transformationComplete(data: TransformationData): Unit

}

abstract class SensorTransformer extends Logs {

  def doTransform(dimension: String): Unit

  private val listeners: mutable.ListBuffer[SensorEventListener] = mutable.ListBuffer.empty
  def addListener(l: SensorEventListener): Unit = listeners += l

  final protected def fireFaultDetected(data: FaultData): Unit = listeners.foreach(_.faultDetected(data, this))
  final protected def fireTransformationStarted(data: TransformationData): Unit = listeners.foreach(_.transformationStarted(data))
  final protected def fireTransformationComplete(data: TransformationData): Unit = listeners.foreach(_.transformationComplete(data))
}
