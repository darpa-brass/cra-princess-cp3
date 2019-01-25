/*
 * KalmanFilterResidualInputModel.scala
 * A model used to infer water current from KF residual observations
 *
 * Created By:      Gerald Fry (gfry@cra.com)
 * Creation Date:   Feb 9, 2017
 */
package com.cra.princess.components.kalmanfilter.inputmodel

import com.cra.figaro.algorithm.filtering.ParticleFilter
import com.cra.figaro.language.Apply
import com.cra.figaro.language.Chain
import com.cra.figaro.language.Constant
import com.cra.figaro.language.Element
import com.cra.figaro.language.LogConstraint
import com.cra.figaro.language.NamedEvidence
import com.cra.figaro.language.Universe
import com.cra.figaro.library.atomic.continuous.Uniform
import com.cra.princess.core.PrincessFeature

class KalmanFilterResidualEnvironmentModel extends PrincessFeature{

  // Initial universe for environment model
  // 1) initial residual, r: Double
  // 2) initial water current delta in x direction, wcDeltaX: Double
  // 3) initial water current delta in y direction, wcDeltaY: Double
  private val initialUniverse: Universe = {
    val (rx, ry, wcX, wcY, wcDeltaX, wcDeltaY) = (0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    val u = new Universe
    Constant(rx)("rx", u)
    Constant(ry)("ry", u)
    Constant(wcX)("wcX", u)
    Constant(wcY)("wcY", u)
    Constant(wcDeltaX)("wcDeltaX", u)
    Constant(wcDeltaY)("wcDeltaY", u)
    u
  }

  // Current universe
  private var currentUniverse: Universe = initialUniverse

  // Inference Alg
  private val alg = ParticleFilter(initialUniverse, nextUniverse, 1000)
  alg.start

  var curWcX: Double = 0.0
  var curWcY: Double = 0.0
  var curData: Int = 0

  // Convert observation to evidence to pass to particle filter
  private def buildEvidence(obs: KalmanFilterResidualObservation): 
    List[NamedEvidence[_]] = {
    val constraintX = LogConstraint((v: Double) => -math.pow(v - obs.residualX, 2))
    val constraintY = LogConstraint((v: Double) => -math.pow(v - obs.residualY, 2))

    return List(NamedEvidence("rx", constraintX), 
                NamedEvidence("ry", constraintY))
  }

  def update(time: Double, 
             residual_obs: KalmanFilterResidualObservation): Unit = {

    //log.debug("about to advance time, initialUniverse = " + initialUniverse) 
    alg.advanceTime(buildEvidence(residual_obs))

    val deltaX = alg.currentExpectation("wcX", (i: Double) => i)
    val deltaY = alg.currentExpectation("wcY", (i: Double) => i)
    if (math.abs(deltaX) >= xThresh)
      curWcX = curWcX + deltaX
    if (math.abs(deltaY) >= yThresh)
      curWcY = curWcY + deltaY
  }

  // Parameters
  var xThresh: Double = 5.0
  var yThresh: Double = 5.0
  var wcMin: Double = -10.0
  var wcMax: Double = 10.0

  // State transition function
  // Note: parameters may need to be extended to take on more values
  private def stateTransition(elementVals: (Double, Double, Double, Double)): 
    Element[(Double, Double, Double, Double)] = {
    // unpack args
    val (rxp, ryp, wxp, wyp) = elementVals

    val wx = Uniform(wcMin, wcMax)
    val wy = Uniform(wcMin, wcMax)
    
    // calculate next residual x element
    val rx = Apply(wx,  
                   (wxval: Double) => {
      wxval
    })
    
    // calculate next residual y element
    val ry = Apply(wy,
                   (wyval: Double) => {
      wyval
    })
    
    // pack elements and return
    Apply(rx, ry, wx, wy,
        (rxval: Double, ryval: Double, wxval: Double, wyval: Double) => 
          (rxval, ryval, wxval, wyval))
  }

  // Universe transition function
  def nextUniverse(previous: Universe): Universe = {
    val next = new Universe
    val rxPrev = previous.get[Double]("rx")
    val ryPrev = previous.get[Double]("ry")
    val wcXPrev = previous.get[Double]("wcX")
    val wcYPrev = previous.get[Double]("wcY")
    val packagedVars = Apply(rxPrev, ryPrev, wcXPrev, wcYPrev, 
        (rx: Double, ry: Double, wcX: Double, wcY: Double) => 
          (rx, ry, wcX, wcY))("packagedVars", previous)
    val state = Chain(packagedVars, stateTransition)("state", next)
    Apply(state, (s: (Double, Double, Double, Double)) => s._1)("rx", next)
    Apply(state, (s: (Double, Double, Double, Double)) => s._2)("ry", next)
    Apply(state, (s: (Double, Double, Double, Double)) => s._3)("wcX", next)
    Apply(state, (s: (Double, Double, Double, Double)) => s._4)("wcY", next)
    currentUniverse = next
    next
  }
  
  // train on data
  def train(data: List[(Double, Double, Double, Double)]) = {
    // find minimum thresholds on residuals associated with wc change
    for(i <- 1 until data.length) {
      if(data(i)._3 != data(i-1)._3) {
        if(math.abs(data(i)._1) < xThresh) {
          xThresh = math.abs(data(i)._1)
        }
      }
      if(data(i)._4 != data(i-1)._4) {
        if(math.abs(data(i)._2) < yThresh) {
          yThresh = math.abs(data(i)._2)
        }
      }
    }
  }

}