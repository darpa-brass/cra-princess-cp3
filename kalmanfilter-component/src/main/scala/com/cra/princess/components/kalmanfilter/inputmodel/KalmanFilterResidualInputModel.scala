package com.cra.princess.components.kalmanfilter.inputmodel

import com.cra.figaro.algorithm.filtering.ParticleFilter
import com.cra.figaro.algorithm.learning.EMWithImportance
import com.cra.figaro.language._
import com.cra.figaro.library.atomic.continuous.{Beta, Normal, Uniform}
import com.cra.figaro.patterns.learning.ModelParameters
import com.cra.princess.inputmodel.UpdateableKernelDensityInputModel
import com.cra.princess.localizationalgorithm.components.ComponentState
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterEnvironment
import com.cra.princess.util.Logs
import com.cra.princess._
import com.cra.princess.componentmodel.LatentEnvironmentInputModel
import com.cra.princess.core.IdentityBuilder
import com.cra.princess.kalmanfilter.{KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper}
import org.apache.commons.math3.linear.ArrayRealVector

class KalmanFilterResidualInputModel (var inputComponents: UpdateableKernelDensityInputModel[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper],
    name:Name[(KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper)], 
    elementCollection:ElementCollection)
  extends LatentEnvironmentInputModel[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper](name, elementCollection) with Logs  {

  // Implementations required by LatentEnvironmentInputModel/Element
  override type Randomness = Null
  override def generateRandomness() = null
  override def args() = List(inputComponents) // bug report (Figaro should check if null)
  
  // Input component model based on updateable kernel density estimator
  // Will be initialized during training
  //var inputComponents: UpdateableKernelDensityInputModel[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper] = null
  
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
  private val alg = ParticleFilter(initialUniverse, nextUniverse, 500)
  
  // Generate sample from P(E, I)
  override def generateValue(rand: Null): (KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper) = {
    // TODO: inference here for env values, or use element values of wcx/wcy?
    //val wcx = alg.currentExpectation("wcX", (i: Double) => i)
    //val wcy = alg.currentExpectation("wcY", (i: Double) => i)
    //log.debug("Inferred value of water current (X): " + wcx)
    //log.debug("Inferred value of water current (Y): " + wcy)
    
    (new KalmanFilterEnvironmentWrapper(new KalmanFilterEnvironment(/*currentUniverse.get[Double]("wcX").value*/ curWcX,
                                                                    /*currentUniverse.get[Double]("wcY").value*/ curWcY)),
      new KalmanFilterInputWrapper(new ComponentState(
        new ArrayRealVector(Array(0.0, 0.0, 0.0, 0.0)), 2),
        new ArrayRealVector(Array(
          inputComponents.value._2.actuatorValues.getEntry(0), inputComponents.value._2.actuatorValues.getEntry(1),
          inputComponents.value._2.actuatorValues.getEntry(2), inputComponents.value._2.actuatorValues.getEntry(3), inputComponents.value._2.actuatorValues.getEntry(4))),
        Seq(new ArrayRealVector(Array(inputComponents.value._2.observations(0).getEntry(0), inputComponents.value._2.observations(0).getEntry(1)))),
      inputComponents.value._2.initialCovarianceDiagonal, inputComponents.value._2.initialCovarianceOffDiagonal, null)
    )
  }
  
  // Convert observation to evidence to pass to particle filter
  private def buildEvidence(obs: KalmanFilterResidualObservation): List[NamedEvidence[_]] = {
    return List(NamedEvidence("rx", Observation(obs.residualX)), NamedEvidence("ry", Observation(obs.residualY)))
  }

  // required update function, only handles updating based on KF inputs
  override def update(time: Double, obs: KalmanFilterInputWrapper): 
  LatentEnvironmentInputModel[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper] = {
    this.inputComponents = this.inputComponents.update(time, (new KalmanFilterEnvironmentWrapper(new KalmanFilterEnvironment()), obs)) 
    if(!this.inputComponents.active) this.inputComponents.activate()
    if(!this.active) this.activate()
    this
  }
  
  var curWcX: Double = 0.0
  var curWcY: Double = 0.0
  
  // Top-level update function: update based on residual and input observations
  def update(time: Double, obs: KalmanFilterInputWrapper, residual_obs: KalmanFilterResidualObservation): 
  LatentEnvironmentInputModel[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper] = {
    log.debug("about to advance time, initialUniverse = " + initialUniverse) 
    alg.advanceTime(buildEvidence(residual_obs))
    curWcX = alg.currentExpectation("wcX", (i: Double) => i)
    curWcY = alg.currentExpectation("wcY", (i: Double) => i)
    log.info("Inferred value of water current (X): " + curWcX)
    log.info("Inferred value of water current (Y): " + curWcY)
    update(time, obs)  
  }
  
  // Model parameters values
  val wxnoiseVar: Double = 0.01 // water current noise variance in x direction
  val wynoiseVar: Double = 0.01 // water current noise variance in y direction
  val wxumin: Double = 0.0 // prior minimum water current in x direction
  val wxumax: Double = 20.0 // prior maximum water current in x direction
  val wyumin: Double = 0.0 // prior minimum water current in y direction
  val wyumax: Double = 20.0 // prior maximum water current in y direction
  val residualNoiseVarX = 0.01 // residual x transition noise variance
  val residualNoiseVarY = 0.01 // residual y transition noise variance
  val weightRx = 0.1
  val weightRy = 0.1
  
  // Model parameter elements
  val params = ModelParameters()
  var pxParam = 0.5 // water current transition probability in x direction
  var pyParam = 0.5 // water current transition probability in y direction
  //val weightRxParam = Beta(3, 1)("weightRxParam", params) // residual x weight
  //val weightRyParam = Beta(3, 1)("weightRyParam", params) // residual y weight
  
  // State transition function
  // Note: parameters may need to be extended to take on more values
  private def stateTransition(elementVals: (Double, Double, Double, Double)): Element[(Double, Double, Double, Double)] = {
    // unpack args
    val (rxp, ryp, wxp, wyp) = elementVals
    
    // calculate next wcDeltaX element
    val wx = Apply(Flip(pxParam), Uniform(wxumin, wxumax), Normal(0, wxnoiseVar), (b: Boolean, u: Double, wxnoise: Double) => {
      if (!b) wxp + wxnoise else u
    })
    
    val wxDelta = Apply(wx, (wxval: Double) => {
      wxval - wxp
    })
    
    // calculate next wcDeltaY element
    val wy = Apply(Flip(pyParam), Uniform(wyumin, wyumax), Normal(0, wynoiseVar), (b: Boolean, u: Double, wynoise: Double) => {
      if (!b) wyp + wynoise else u
    })
    
    val wyDelta = Apply(wy, (wyval: Double) => {
      wyval - wyp
    })
    
    // calculate next residual x element
    val rx = Apply(wxDelta, 
                   //parameters.get("weightRxParam") match { case ParameterDouble(p) => p },  //parameters.get("weightRxParam").asInstanceOf[ParameterDouble].p,
                   Normal(0, residualNoiseVarX), 
                   (wxval: Double, /*weightRx: Double,*/ residualNoise: Double) => {
      weightRx * rxp + (1-weightRx) * wxval + residualNoise
    })
    
    // calculate next residual y element
    val ry = Apply(wyDelta,
                   //parameters.get("weightRyParam") match { case ParameterDouble(p) => p }, //parameters.get("weightRyParam").asInstanceOf[ParameterDouble].p,
                   Normal(0, residualNoiseVarY), 
                   (wyval: Double, /*weightRy: Double,*/ residualNoise: Double) => {
      weightRy * ryp + (1-weightRy) * wyval + residualNoise
    })
    
    // pack elements and return
    Apply(rx, ry, wx, wy,
        (rxval: Double, ryval: Double, wxval: Double, wyval: Double) => (rxval, ryval, wxval, wyval))
  }
  
  // Universe transition function
  def nextUniverse(previous: Universe): Universe = {
    val next = new Universe
    val rxPrev = previous.get[Double]("rx")
    val ryPrev = previous.get[Double]("ry")
    val wcXPrev = previous.get[Double]("wcX")
    val wcYPrev = previous.get[Double]("wcY")
    val packagedVars = Apply(rxPrev, ryPrev, wcXPrev, wcYPrev, 
        (rx: Double, ry: Double, wcX: Double, wcY: Double) => (rx, ry, wcX, wcY))("packagedVars", previous)
    val state = Chain(packagedVars, stateTransition)("state", next)
    Apply(state, (s: (Double, Double, Double, Double)) => s._1)("rx", next)
    Apply(state, (s: (Double, Double, Double, Double)) => s._2)("ry", next)
    Apply(state, (s: (Double, Double, Double, Double)) => s._3)("wcX", next)
    Apply(state, (s: (Double, Double, Double, Double)) => s._4)("wcY", next)
    currentUniverse = next
    next
  }
  
  // Unroll (water current portion) environment model 'timesteps' time steps and train on data
  // Also, initialize other input component elements
  def train(data: List[(Double, Double, Double, Double)], input_data: List[KalmanFilterInputWrapper]) = {
    val timesteps = data.length    
    val u = Universe.createNew()
    
    val px = Beta(1.0, 1.0)
    val py = Beta(1.0, 1.0)
    
    val elemsX = for(i <- 0 until timesteps-1) yield {
      Flip(px)
    }
    
    val elemsY = for(i <- 0 until timesteps-1) yield {
      Flip(py)
    }
    
    // X
    for(i <- 1 until timesteps) {
      //log.debug("X: (" + i + ", " + data(i-1)._3 + ")")
      if(data(i)._3 != data(i-1)._3) {
        elemsX(i-1).observe(true)
      } else {
        elemsX(i-1).observe(false)
      }
    }
    
    // Y
    for(i <- 1 until timesteps) {
      //log.debug("Y: (" + i + ", " + data(i-1)._4 + ")")
      if(data(i)._4 != data(i-1)._4) {
        elemsY(i-1).observe(true)
      } else {
        elemsY(i-1).observe(false)
      }
    }
    
    val numberOfEMIterations = 10
    val numberOfBPIterations = 10
    val learningAlgorithm = EMWithImportance(10, 10, px, py)
    learningAlgorithm.start()
    learningAlgorithm.stop()
    learningAlgorithm.kill()
    pxParam = px.MAPValue
    pyParam = py.MAPValue
    log.info("Environment model trained: X random walk probability param = " + px.MAPValue)
    log.info("Environment model trained: Y random walk probability param = " + py.MAPValue)
    
    val env_data = List.fill(data.length)(new KalmanFilterEnvironmentWrapper(new KalmanFilterEnvironment()))
    // Now, obtain rest of input component distributions
    //this.inputComponents = UpdateableKernelDensityInputModel(env_data, input_data, 0.1, 5,
    //    IdentityBuilder[KalmanFilterEnvironmentWrapper](), IdentityBuilder[KalmanFilterInputWrapper]())
    alg.start()
  }
}

class KalmanFilterResidualObservation(val residualX: Double, val residualY: Double)

object KalmanFilterResidualInputModel {
  def apply(curModel: KalmanFilterResidualInputModel, obs:KalmanFilterInputWrapper, residual_obs: KalmanFilterResidualObservation, obsTime:Double) = {
    curModel.update(obsTime, obs, residual_obs)
  }
  
  def apply(samples:Seq[(KalmanFilterInputWrapper, KalmanFilterEnvironmentWrapper, KalmanFilterResidualObservation)], decayRate:Double=0.1)(
      implicit eltname:Name[(KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper)],
      elementCollection: ElementCollection) = {    

    val (input_data, env_data, res_data) = samples.unzip3[KalmanFilterInputWrapper, KalmanFilterEnvironmentWrapper, KalmanFilterResidualObservation]

    // Create new input model instance and train
    val inputComponents = UpdateableKernelDensityInputModel(env_data.toList, input_data.toList, 0.1, 5,
        IdentityBuilder[KalmanFilterEnvironmentWrapper](), IdentityBuilder[KalmanFilterInputWrapper]())
    val newInputModel = new KalmanFilterResidualInputModel(inputComponents, eltname, elementCollection)
    
    val data = (res_data zip env_data).map(x => (x._1.residualX, x._1.residualY, x._2.env.getxCurrent.doubleValue(), x._2.env.getyCurrent.doubleValue()))
    newInputModel.train(data.toList, input_data.toList)
    newInputModel
  }
}