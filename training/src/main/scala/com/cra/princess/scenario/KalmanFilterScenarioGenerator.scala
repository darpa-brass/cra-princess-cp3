package com.cra.princess.scenario

import java.util.Random

import com.cra.princess.kalmanfilter.KalmanFilterInputWrapper
import com.cra.princess.localizationalgorithm.components.ComponentState
import com.cra.princess.models.TransformedSingleFunctionKalmanFilter
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterOutput
import com.cra.princess.optimizers.TrainableKFOptimizer
import org.apache.commons.math3.linear._

/**
  * Generates data by running entire scenarios
  */
object KalmanFilterScenarioGenerator {

  val kf = new TransformedSingleFunctionKalmanFilter
  private val defaultControls = Seq(1, 1, 0.3, 0.3, 0.1, 0.2)

  private val seed = new Random((Math.random()*Long.MaxValue).toLong)

  /**
    * BaseSigma is in [0.1, 0.6sigma]
    * Assume white noise is uniform in all directions (for now), ignore affine transformation in this case
    */
  def runScenario(maxScenarioLength: Int = 1000,
                  uuvSpeed: Double = 3.2,
                  waterCurrentVector: (Double, Double) = (2,0), // (-2,2) and (-1,1)
                  waterCurrentRegion: ((Double, Double), (Double, Double)) = ((Double.NegativeInfinity,160),(Double.PositiveInfinity, 555.9754)), // (166.79262, 555.9754), (x, 555.9754)
                  sensorNoiseStdev: Double = 4.0, // range (0.0, 8.0)
                  sensorBias: Double = 0.0,
                  start: (Double, Double) = (0,0),
                  end: (Double, Double) = (0, 555.9754),
                  transformedControls: Seq[Double] = defaultControls,
                  optimizerOpt: Option[TrainableKFOptimizer] = None,
                  verdict: Double = 5.0,
                  numResiduals: Int = 10,
                  perturbationThreshold: Double = 1.0): ((Double, Double), (Double, Double), (Double, Double)) = {

//    val writer = new PrintWriter(new File("scenarioData.csv"))
    require(transformedControls.size == 6)

    val ((x1, y1), (x2, y2)) = waterCurrentRegion
    var numReadings = 0
    val originalControls = defaultControls
    var controlsToReturn = originalControls
    var prevInputOpt: Option[KalmanFilterInputWrapper] = None
    var prevOutputOpt: Option[KalmanFilterOutput] = None

    var (pX, pY) = start
    var diff = Math.hypot(end._1 - pX, end._2 - pY)
    var predictedDiff = diff

    var (vX, vY) = (uuvSpeed*(end._1 - pX)/diff, uuvSpeed*(end._2 - pY)/diff) // vehicle velocity
    var (estVX, estVY) = (vX, vY)   // estimated velocity initialized to be vehicle velocity
    var (actualPX, actualPY) = start

    while(predictedDiff > verdict && numReadings < maxScenarioLength){
      val inWaterCurrentRegion = pX >= x1 && pX <= x2 && pY >= y1 && pY <= y2
      val controls =
        if(inWaterCurrentRegion){
          optimizerOpt match {
            case Some(optimizer) =>
              (prevInputOpt, prevOutputOpt) match {
                case (Some(prevInput), Some(prevOutput)) =>
                  optimizer.train(prevInput, prevOutput).toList
                case _ => defaultControls
              }
//              optimizer.optimize(List(pX, pY, estVX, estVY)) // TODO: only call in testing phase
            case _ => defaultControls
          }
        }
        else defaultControls

      val componentState = new ComponentState(new ArrayRealVector(Array.empty[Double]),new ArrayRealVector(Array(pX, pY, estVX, estVY)))
      prevInputOpt = Some(new KalmanFilterInputWrapper(componentState, new ArrayRealVector(Array(0.0)), Seq.empty[RealVector], 0.0, 0.0, null))
      controlsToReturn = controls

      val (cX, cY) = if(inWaterCurrentRegion) waterCurrentVector else (0.0,0.0)
      val random = new Random(seed.nextLong())
      val biasAndNoise = if(pX >= x1 && pX <= x2 && pY >= y1) sensorBias + sensorNoiseStdev*random.nextGaussian() else 0.0

      val sensorVx = vX + cX + biasAndNoise
      val sensorVy = vY + cY + biasAndNoise
      val Zn = new ArrayRealVector(Array(sensorVx, sensorVy))

      val kfOut = generateDataPoint(MatrixUtils.createRealIdentityMatrix(2), new ArrayRealVector(Array(estVX, estVY)),
        Zn, new ArrayRealVector(Array(0.0, 0.0)), controls.head, controls(1), controls(2), controls(3), controls(4),
        controls(5), end)

      val estimatedVelocity = kfOut.getState.getCombinedState
      estVX = estimatedVelocity.getEntry(0)
      estVY = estimatedVelocity.getEntry(1)
      pX += estimatedVelocity.getEntry(0)
      pY += estimatedVelocity.getEntry(1)

      val dist = Math.hypot(actualPX - end._1, actualPY - end._2)
      kfOut.setDistance(dist)
      prevOutputOpt = Some(kfOut)

      predictedDiff = Math.hypot(end._1 - pX, end._2 - pY)
      // update vehicle velocity
      vX = 3.2*(end._1 - pX)/diff
      vY = 3.2*(end._2 - pY)/diff

//      println(s"location: $actualPX, $actualPY, estimation: $pX, $pY}")
      actualPX += (vX + cX)
      actualPY += (vY + cY)
      diff = Math.hypot(actualPX - end._1, actualPY - end._2)
      numReadings += 1
    }
    ((pX, pY), (actualPX, actualPY), end)
  }

  private def generateDataPoint(pPrev: RealMatrix, xPrev: RealVector, Zn: RealVector, Un: RealVector,
                                ctrlVar0: Double, ctrlVar1: Double, ctrlVar2: Double, ctrlVar3: Double,
                                ctrlVar4: Double, ctrlVar5: Double, destination: (Double, Double)): KalmanFilterOutput = {
    // FIXED CONTROLS
    val A: RealMatrix = MatrixUtils.createRealIdentityMatrix(2) // state transition is always identity
    val H: RealMatrix = MatrixUtils.createRealIdentityMatrix(2) // observation matrix (no controls)

    // CONTROLS
    val bDiag0 = ctrlVar0
    val bDiag1 = ctrlVar1
    val B: RealMatrix = MatrixUtils.createRealDiagonalMatrix(Array(bDiag0, bDiag1)) // control (has controls)
    val qDiag0 = ctrlVar2
    val qDiag1 = ctrlVar3
    val Q: RealMatrix = MatrixUtils.createRealDiagonalMatrix(Array(qDiag0, qDiag1)) // process noise covariance (has controls)
    val rDiag0 = ctrlVar4
    val rDiag1 = ctrlVar5
    val R: RealMatrix = MatrixUtils.createRealDiagonalMatrix(Array(rDiag0, rDiag1))
    val output: Array[AnyRef] = kf.autoTransformedrunAlgorithm(xPrev, Zn, Un, pPrev,
      A.getEntry(0,0), 0, 0, A.getEntry(1,1),
      B.getEntry(0,0), 0, 0, B.getEntry(1,1),
      H.getEntry(0,0), 0, 0, H.getEntry(1,1),
      Q.getEntry(0,0), 0, 0, Q.getEntry(1,1),
      R.getEntry(0,0), 0, 0, R.getEntry(1,1))

    val stateVec = output(0).asInstanceOf[RealVector]
    val covariance = output(1).asInstanceOf[RealMatrix]
    val residual = output(2).asInstanceOf[RealVector]
    val componentState = new ComponentState(new ArrayRealVector(Array.empty[Double]), stateVec)
    new KalmanFilterOutput(componentState, covariance, residual)
  }
}
