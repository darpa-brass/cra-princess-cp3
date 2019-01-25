package com.cra.princess.components.kalmanfilter

import com.cra.figaro.language.{Apply, Constant, Element}
import com.cra.figaro.library.atomic.continuous.Normal
import com.cra.figaro.library.compound.{Reduce, ^^}
import com.cra.princess.componentmodel.{ComponentModel, ComponentModelInput}
import com.cra.princess.core.PrincessFeature
import com.cra.princess.ComponentModelMetrics
import org.apache.commons.math3.linear._

class KalmanFilterComponentModel(unrollSize: Int) extends ComponentModel[KFEnv, KalmanFilterInput]{

  //sliding time window of sensor measurements
  override def numMetrics: Int = 1

  override def apply(cmInput: ComponentModelInput[KFEnv, KalmanFilterInput]): ComponentModelMetrics = {
    val currentState = cmInput.input.currentEstimatedState
    val stateDist = ^^(
      Constant(currentState.getEntry(0)),
      Constant(currentState.getEntry(1)),
      Constant(currentState.getEntry(2)),
      Constant(currentState.getEntry(3)))
    val kfmc: KFMarkovChain = new KFMarkovChain(stateDist, unrollSize, cmInput.env)
    List(kfmc.getMetric)
  }
}

protected sealed case class KFEnv(wx: Normal, wy: Normal) extends PrincessFeature //partial stub

protected sealed class KalmanFilterInput(val currentEstimatedState: RealVector,
                                         val acceleration: RealVector,
                                         val dvlReading: RealVector) extends PrincessFeature

sealed protected class KFMarkovChain(val startingState: Element[(Double, Double, Double, Double)],
                                     val unrollSize: Int,
                                     val env: KFEnv) {

  // state = [x-position, y-position, x-velocity, y-velocity]
  val states: Array[Element[(Double, Double, Double, Double)]] = Array.fill(unrollSize)(^^(Constant(0.0), Constant(0.0), Constant(0.0), Constant(0.0)))
  val residuals: Array[Element[(Double, Double)]] = Array.fill(unrollSize)(^^(Constant(0.0), Constant(0.0)))
  private val (wcX, wcY) = (env.wx, env.wy)
  states(0) = startingState

  private val transition: (Double, Double) => Array2DRowRealMatrix = //state transition
    (xVel: Double, yVel: Double) =>
      new Array2DRowRealMatrix(Array[Array[Double]](
        Array(1, 0, xVel, 0),
        Array(0, 1, 0, yVel),
        Array(0, 0, 1, 0),
        Array(0, 0, 0, 1)))
  private val Q: RealMatrix = new Array2DRowRealMatrix(Array[Array[Double]]( // process noise
    Array(wcX.varianceValue, 0, 0, 0),
    Array(0, wcY.varianceValue, 0, 0),
    Array(0, 0, 0, 0),
    Array(0, 0, 0, 0)))
  private val R: RealMatrix = MatrixUtils.createRealDiagonalMatrix(Array(0.1, 0.1, 0.1, 0.1)) //measurement noise
  private val H: RealMatrix = new Array2DRowRealMatrix(Array[Array[Double]](
    Array(0, 0),
    Array(0, 0),
    Array(1, 0),
    Array(0, 1)))
  private val I: RealMatrix = MatrixUtils.createRealIdentityMatrix(H.getColumnDimension)
  private var P: RealMatrix = MatrixUtils.createRealIdentityMatrix(4) // covariance
  private var priorEst: RealVector = new ArrayRealVector(Array[Double](0, 0, 0, 0))
  private var currentState: Element[(Double, Double, Double, Double)] = startingState

  for (i <- 1 until unrollSize) {
    // computing new residual
    var A = transition(0,0)
    val newResidual: Element[(Double, Double)] = Apply(currentState, wcX, wcY, (state: (Double, Double, Double, Double), wX: Double, wY: Double) => {
      val (xpos, ypos, xvel, yvel) = state
      A = transition(xvel, yvel)
      val stateVector = new ArrayRealVector(Array[Double](xpos, ypos, xvel, yvel))
      val newMeasurement = new ArrayRealVector(Array[Double](xvel + wX, yvel + wY))
      priorEst = A.operate(stateVector)
      val residual = priorEst.subtract(H.operate(newMeasurement))
      (residual.getEntry(0), residual.getEntry(1))
    })
    residuals(i) = newResidual


    // computing new state
    currentState = Apply(newResidual, (r: (Double, Double)) => {
      val pPredicted = A.multiply(P).multiply(A.transpose).add(Q)
      val residual = new ArrayRealVector(Array[Double](r._1, r._2))
      val S = H.multiply(pPredicted).multiply(H.transpose).add(R)
      val K = pPredicted.multiply(H.transpose).multiply(MatrixUtils.inverse(S))
      val pPosterior = I.subtract(K.multiply(H)).multiply(pPredicted)
      P = pPosterior
      val postEst = priorEst.add(K.operate(residual))
      (postEst.getEntry(0), postEst.getEntry(1), postEst.getEntry(2), postEst.getEntry(3))
    })
    states(i) = currentState
  }

  def getMetric: Element[Double] = {
    val norms = residuals.map(rDist => Apply(rDist, (r: (Double, Double)) => Math.hypot(r._1, r._2)/residuals.length))
    Reduce((x: Double,y: Double) => x + y)(norms :_*)
  }
}