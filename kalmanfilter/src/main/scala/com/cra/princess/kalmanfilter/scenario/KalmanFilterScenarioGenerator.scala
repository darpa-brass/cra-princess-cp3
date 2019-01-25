package com.cra.princess.kalmanfilter.scenario

import java.io.{File, FileOutputStream, PrintWriter}
import java.util.Random

import com.cra.princess.kalmanfilter.Util.generateRandomSample
import com.cra.princess.kalmanfilter.{KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper}
import com.cra.princess.models.TransformedSingleFunctionKalmanFilter
import com.cra.princess.optimizer.ComponentOptimizer
import org.apache.commons.math3.linear._

/**
  * Generates data by running entire scenarios
  */
object KalmanFilterScenarioGenerator {

  val kf = new TransformedSingleFunctionKalmanFilter
  private val defaultControls = Seq(
    1.0,0.0,0.0,1.0,
    1.0,0.0,0.0,1.0,
    1.0,0.0,0.0,1.0,
    0.3,0.0,0.0,0.3,
    0.1,0.0,0.0,0.2)

  private val seed = new Random((Math.random()*Long.MaxValue).toLong)

  def main(args: Array[String]): Unit = generateTrainingSet(trainingFile = s"kf_training_data_${System.currentTimeMillis()}.csv")

  def generateTrainingSet(numControls: Int = 200, numScenarios: Int = 70000,
                          cRange: (Double, Double) = (-2, 2),
                          wcXRange: (Double, Double) = (-2, 2),
                          wcYRange: (Double, Double) = (-1, 1),
                          wcRegionRange: (Double, Double) = (166.79262, 555.9754 - 100),
                          sensorNoiseStdevRange: (Double, Double) = (0, 8),
                          perturbationThresholdRange: (Double, Double) = (0.5, 1.5), append: Boolean = true,
                          trainingFile: String): Unit ={
    val pw = new PrintWriter(new FileOutputStream(new File(trainingFile), append))
    for(i <- 0 until numScenarios) yield {
      val wcX = generateRandomSample(wcXRange)
      val wcY = generateRandomSample(wcYRange)
      val wcRegionLower = generateRandomSample(wcRegionRange)
      val wcRegionUpper = generateRandomSample((wcRegionLower + 100, wcRegionRange._2 + 100))
      val sensorNoiseStdev = generateRandomSample(sensorNoiseStdevRange)
      val numResiduals = 10
//      val perturbationThreshold = 0.0

      var currentControls = defaultControls
      var currentMinNoise = Double.MaxValue
      var (currentInputs, _, _, (baselineAvgX, baselineAvgY)) = runScenario(
        waterCurrentVector = (wcX, wcY),
        waterCurrentRegion = ((Double.NegativeInfinity, wcRegionLower), (Double.PositiveInfinity, wcRegionUpper)),
        transformedControls = currentControls,
        sensorNoiseStdev = sensorNoiseStdev,
        numResiduals = numResiduals)
//      println(currentDiff, wcRegionLower, wcRegionUpper, wcX, wcY, sensorNoiseStdev)
      val t1 = System.currentTimeMillis()
      for(_ <- 0 until numControls){
        val diag00 = generateRandomSample(cRange)
        val diag01 = generateRandomSample(cRange)
        val diag02 = generateRandomSample(cRange)
        val diag03 = generateRandomSample(cRange)

        val diag10 = generateRandomSample(cRange)
        val diag11 = generateRandomSample(cRange)
        val diag12 = generateRandomSample(cRange)
        val diag13 = generateRandomSample(cRange)

        val diag20 = generateRandomSample(cRange)
        val diag21 = generateRandomSample(cRange)
        val diag22 = generateRandomSample(cRange)
        val diag23 = generateRandomSample(cRange)

        val diag30 = generateRandomSample(cRange)
        val diag31 = generateRandomSample(cRange)
        val diag32 = generateRandomSample(cRange)
        val diag33 = generateRandomSample(cRange)

        val diag40 = generateRandomSample(cRange)
        val diag41 = generateRandomSample(cRange)
        val diag42 = generateRandomSample(cRange)
        val diag43 = generateRandomSample(cRange)

        val controls = Seq(
          diag00, diag01, diag02, diag03,
          diag10, diag11, diag12, diag13,
          diag20, diag21, diag22, diag23,
          diag30, diag31, diag32, diag33,
          diag40, diag41, diag42, diag43)
        val (residuals, _, _, (avgX, avgY)) = runScenario(
          waterCurrentVector = (wcX, wcY),
          waterCurrentRegion = ((Double.NegativeInfinity, wcRegionLower), (Double.PositiveInfinity, wcRegionUpper)),
          transformedControls = controls,
          sensorNoiseStdev = sensorNoiseStdev,
          numResiduals = numResiduals
        )
        val totalNoise = Math.hypot(baselineAvgX - avgX, baselineAvgY - avgY)
        if(totalNoise < currentMinNoise) {
          currentMinNoise = totalNoise
          currentControls = controls
          currentInputs = residuals
        }
      }
      val t2 = System.currentTimeMillis()
      println(s"${(t2 - t1)/1000.0}, scenarios run: $i")
      pw.println(s"${currentInputs.mkString(",")},${currentControls.mkString(",")}")
    }
    pw.close()
  }

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
                  optimizerOpt: Option[ComponentOptimizer[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper]] = None,
                  verdict: Double = 5.0,
                  numResiduals: Int = 10,
                  perturbationThreshold: Double = 1.0): (Seq[Double], Double, Seq[Double], (Double, Double)) = {

//    val writer = new PrintWriter(new File("scenarioData.csv"))
    require(transformedControls.size == 20)

    var residuals = Seq.empty[(Double, Double)]
    var noiseVectors = Seq.empty[(Double, Double)] // first N velocities after hitting current region

    val ((x1, y1), (x2, y2)) = waterCurrentRegion
    var numReadings = 0
    val originalControls = defaultControls
    var controlsToReturn = originalControls

    var (pX, pY) = start
    var diff = Math.hypot(end._1 - pX, end._2 - pY)
    var predictedDiff = diff

    var (vX, vY) = (uuvSpeed*(end._1 - pX)/diff, uuvSpeed*(end._2 - pY)/diff) // vehicle velocity
    var (estVX, estVY) = (vX, vY)   // estimated velocity initialized to be vehicle velocity
    var (actualPX, actualPY) = start
    var hitRegion = false
    while(predictedDiff > verdict && numReadings < maxScenarioLength){
//      writer.println(s"$actualPX, $actualPY")
      val inWaterCurrentRegion = pX >= x1 && pX <= x2 && pY >= y1 && pY <= y2
      val hitWaterCurrentRegion = pX >= x1 && pX <= x2 && pY >= y1
      val controls =
        if(hitWaterCurrentRegion && residuals.size == numResiduals && !hitRegion){
          hitRegion = true
          optimizerOpt match {
            case None => transformedControls
            case Some(optimizer) =>
              optimizer.optimize(residuals.flatMap{case (a,b) => Seq(a,b)}.toList)
          }
        }
        else if(hitRegion) controlsToReturn
        else  originalControls

      controlsToReturn = controls

      val (cX, cY) = if(inWaterCurrentRegion) waterCurrentVector else (0.0,0.0)
      val random = new Random(seed.nextLong())
      val biasAndNoise = if(pX >= x1 && pX <= x2 && pY >= y1) sensorBias + sensorNoiseStdev*random.nextGaussian() else 0.0

      val sensorVx = vX + cX + biasAndNoise
      val sensorVy = vY + cY + biasAndNoise
      val Zn = new ArrayRealVector(Array(sensorVx, sensorVy))

      val (velocityOpt, resOpt) = generateDataPoint(MatrixUtils.createRealIdentityMatrix(2), new ArrayRealVector(Array(estVX, estVY)),
        Zn, new ArrayRealVector(Array(0.0, 0.0)), controls.head, controls(1), controls(2), controls(3), controls(4),
        controls(5), controls(6), controls(7), controls(8), controls(9), controls(10), controls(11), controls(12),
        controls(13), controls(14), controls(15), controls(16), controls(17), controls(18), controls(19))

      val residual = resOpt.getOrElse(new ArrayRealVector(Array(Double.PositiveInfinity, Double.PositiveInfinity)))
      if(residual.getEntry(0) == Double.PositiveInfinity) {
        val avgX = noiseVectors.map(_._1).sum/noiseVectors.size.toDouble
        val avgY = noiseVectors.map(_._2).sum/noiseVectors.size.toDouble
        return (residuals.flatMap { case (a, b) => Seq(a, b) }, Double.PositiveInfinity, controlsToReturn, (avgX, avgY))
      }

      if(residuals.size < numResiduals && hitWaterCurrentRegion) {
        residuals = residuals :+ (residual.getEntry(0), residual.getEntry(1))
        noiseVectors = noiseVectors :+ (biasAndNoise, biasAndNoise)
      }

      val estimatedVelocity = velocityOpt.getOrElse(new ArrayRealVector(Array(estVX, estVY)))
      estVX = estimatedVelocity.getEntry(0)
      estVY = estimatedVelocity.getEntry(1)
      pX += estimatedVelocity.getEntry(0)
      pY += estimatedVelocity.getEntry(1)

      predictedDiff = Math.hypot(end._1 - pX, end._2 - pY)
      // update vehicle velocity
      vX = 3.2*(end._1 - pX)/diff
      vY = 3.2*(end._2 - pY)/diff

      //      println(s"location: $actualPX, $actualPY, $numReadings")
      actualPX += (vX + cX)
      actualPY += (vY + cY)
      diff = Math.hypot(actualPX - end._1, actualPY - end._2)
      numReadings += 1
    }
//    writer.close()
//    println(diff)

    // TODO: also return noise vector sum
    val avgX = noiseVectors.map(_._1).sum
    val avgY = noiseVectors.map(_._2).sum
    (residuals.flatMap{case (a,b) => Seq(a,b)}, diff, controlsToReturn, (avgX, avgY))
  }

  private def generateDataPoint(pPrev: RealMatrix, xPrev: RealVector, Zn: RealVector, Un: RealVector,
                                ctrlVar0: Double, ctrlVar1: Double, ctrlVar2: Double, ctrlVar3: Double,
                                ctrlVar4: Double, ctrlVar5: Double, ctrlVar6: Double, ctrlVar7: Double,
                                ctrlVar8: Double, ctrlVar9: Double, ctrlVar10: Double, ctrlVar11: Double,
                                ctrlVar12: Double, ctrlVar13: Double, ctrlVar14: Double, ctrlVar15: Double,
                                ctrlVar16: Double, ctrlVar17: Double, ctrlVar18: Double, ctrlVar19: Double): (Option[RealVector], Option[RealVector]) = {
    val output: Option[Array[AnyRef]] =
      try {
        Some(kf.autoTransformedrunAlgorithm(xPrev, Zn, Un, pPrev, ctrlVar0, ctrlVar1, ctrlVar2, ctrlVar3, ctrlVar4,
          ctrlVar5, ctrlVar6, ctrlVar7, ctrlVar8, ctrlVar9, ctrlVar10, ctrlVar11, ctrlVar12, ctrlVar13, ctrlVar14,
          ctrlVar15, ctrlVar16, ctrlVar17, ctrlVar18, ctrlVar19))
      }
      catch {
        case _: SingularMatrixException => None
      }
    output match {
      case Some(arr) =>
        val newX = Some(arr(0).asInstanceOf[RealVector])
        val res = Some(arr(2).asInstanceOf[RealVector])
        (newX, res)
      case None =>
        (None, None)
    }
  }

  def generateDataPoint(inputs: Array[Double], controls: Array[Double]): (Option[RealVector], Option[RealVector]) = {
    // Marshal inputs
    val (p00, p11) = (inputs(0), inputs(1))
    val (x1, x2) = (inputs(2), inputs(3))
    val (z1, z2) = (inputs(4), inputs(5))
    val (u1, u2) = (inputs(6), inputs(7))

    val prevP = MatrixUtils.createRealIdentityMatrix(2)
    prevP.setEntry(0,0,p00)
    prevP.setEntry(1,1,p11)
    val X: RealVector = new ArrayRealVector(Array(x1 ,x2))
    val Zn: RealVector = new ArrayRealVector(Array(z1, z2))
    val Un: RealVector = new ArrayRealVector(Array(u1, u2))

    val output: Option[Array[AnyRef]] = try {
      Some(kf.autoTransformedrunAlgorithm(X, Zn, Un, prevP, controls(0), controls(1), controls(2), controls(3), controls(4),
        controls(5), controls(6), controls(7), controls(8), controls(9), controls(10), controls(11), controls(12), controls(13),
        controls(14), controls(15), controls(16), controls(17), controls(18), controls(19)))
    } catch {
      case _: SingularMatrixException => None
    }
    output match {
      case Some(arr) =>
        val newX = Some(arr(0).asInstanceOf[RealVector])
        val res = Some(arr(2).asInstanceOf[RealVector])
        (newX, res)
      case None =>
        (None, None)
    }
  }
}
