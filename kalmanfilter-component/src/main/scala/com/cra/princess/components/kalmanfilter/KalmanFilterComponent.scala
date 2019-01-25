package com.cra.princess.components.kalmanfilter

import com.cra.princess._
import com.cra.princess.models.kalmanfiltercomponents._
import java.io.PrintWriter
import java.util.concurrent.atomic.AtomicBoolean

import com.cra.princess.core.OptimizableComponent
import com.cra.princess.kalmanfilter.{KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper}

trait KalmanFilterComponent 
      extends OptimizableComponent[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper, KalmanFilterOutput] with Serializable
{
  def getInitialControls(): ComponentControls
}

object KalmanFilterComponentUtils
{
  private val writer = new PrintWriter("cp3_kf_out_" + System.currentTimeMillis() + ".csv")
  private var _isAdapting: AtomicBoolean = new AtomicBoolean(false)
  
  def isAdapting: Boolean = _isAdapting.get
  def isAdapting_=(other: Boolean) = this._isAdapting.set(other) 
  
  def writeToFile(timestamp: Long, lat: Double, lon: Double, trueLatLon: (Double, Double), residual: (Double, Double), estVel: (Double, Double), trueVel: (Double, Double)): Unit = {
    val outString = Array(timestamp,
                          lat,
                          lon,
                          (if (isAdapting) "1" else "0"),
                          trueLatLon._1,
                          trueLatLon._2,
                          residual._1,
                          residual._2,
                          estVel._1,
                          estVel._2,
                          trueVel._1,
                          trueVel._2).mkString(",")
    writer.write(outString + "\r\n")
    writer.flush()
  }

  def writeToFile(timestamp: Long, trueVel: (Double, Double), dvlVel: (Double, Double), kfVel: (Double, Double)): Unit = {
    val outString = Array(timestamp,
      trueVel._1, trueVel._2, dvlVel._1, dvlVel._2, kfVel._1, kfVel._2).mkString(",")
    writer.write(outString + "\r\n")
    writer.flush()
  }
}