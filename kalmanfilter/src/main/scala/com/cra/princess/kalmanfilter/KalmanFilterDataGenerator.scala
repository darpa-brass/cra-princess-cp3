package com.cra.princess.kalmanfilter

import java.io.{File, FileOutputStream, PrintWriter}

import com.cra.princess.models.TransformedSingleFunctionKalmanFilter
import com.cra.princess.kalmanfilter.Util.generateRandomSample
import org.apache.commons.math3.linear.{SingularMatrixException, _}

object KalmanFilterDataGenerator {

  private val kf = new TransformedSingleFunctionKalmanFilter
  private val dim = 2

  //TODO: another function that generates data starting from baseline controls and randomly perturbs them

  def generateDataWithUniformSamples(iRangePos: (Double, Double) = (0.001, 0.005),
                                     iRangeVel: (Double, Double) = (-10.0, 10.0),
                                     iRangeAct: (Double, Double) = (-3.2, 3.2),  // these are vel limits on actuator
                                     cRange: (Double, Double) = (-5.0, 5.0),
                                     outfile: String = "kfData.csv",
                                     numInputSamples: Int = 100000,
                                     numControlSamples: Int = 1000, append: Boolean = true): Seq[(Seq[Double], Seq[Double])] = {
    val outputFile = new PrintWriter(new FileOutputStream(new File(outfile), append))
    //val header = s"${(1 to 12).map(i => s"input$i").mkString(",")},${(1 to 10).map(i => s"control$i").mkString(",")}, metric"
    //val header = s"p22,p33,prevPos1,prevPos2,prevPos3,prevPos4,meas1,meas2,act1,act2,act3,act4,ctrlDiag10,ctrlDiag11,ctrlDiag12,ctrlDiag13,ctrlDiag30,ctrlDiag31,ctrlDiag32,ctrlDiag33,ctrlDiag40,ctrlDiag41,residual"

    //outputFile.println(header)
    val (min, max) = iRangePos // TODO: do this for other ranges
    require(min < max)
    val retval = for(_ <- 1 to numInputSamples) yield {
      val p22 = generateRandomSample(iRangeVel)
      val p33 = generateRandomSample(iRangeVel)

      val x1 = generateRandomSample(iRangeVel)
      val x2 = generateRandomSample(iRangeVel)

      val z1 = generateRandomSample(iRangeVel)
      val z2 = generateRandomSample(iRangeVel)

      val u1 = generateRandomSample(iRangeAct)
      val u2 = generateRandomSample(iRangeAct)

      var currentResidual: Option[RealVector] = None
      var optimalControls = Seq.empty[Double]

      var residualMetric = Double.MaxValue

      // Only randomizing entries 2,2 and 3,3
      val prevP = MatrixUtils.createRealIdentityMatrix(dim)
      prevP.setEntry(0,0,p22)
      prevP.setEntry(1,1,p33)

      val X: RealVector = new ArrayRealVector(Array(/*x1, x2,*/ x1 ,x2))
      val Zn: RealVector = new ArrayRealVector(Array(z1, z2))
      val Un: RealVector = new ArrayRealVector(Array(/*u1, u2,*/ u1, u2))

      // original controls - was using to generate data that at least did "better" than the fixed initial controls
      val (_, origResidual) = generateDataPoint(prevP, X, Zn, Un, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.3, 0.3, 0.1, 0.2, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.3, 0.3, 0.1, 0.2)
      if(origResidual.nonEmpty) {
        residualMetric = origResidual.get.getNorm
        currentResidual = origResidual
        optimalControls = Seq(0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.3, 0.3, 0.1, 0.2, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.3, 0.3, 0.1, 0.2)
      }
      //var residualTarget = 1.6
      //while(/*(numControls < numControlSamples) &&*/ (residualMetric >= residualTarget)) {
      for(_ <- 1 to numControlSamples){

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

        val (_, residual) = generateDataPoint(prevP, X, Zn, Un,
          diag00, diag01, diag02, diag03,
          diag10, diag11, diag12, diag13,
          diag20, diag21, diag22, diag23,
          diag30, diag31, diag32, diag33,
          diag40, diag41, diag42, diag43)
        if(currentResidual.isEmpty || (/*origResidual.nonEmpty &&*/ residual.nonEmpty && currentResidual.get.getNorm > residual.get.getNorm)){
          if(residual.nonEmpty) residualMetric = residual.get.getNorm
          currentResidual = residual
//          println(s"currentResidual = ${currentResidual.get.getNorm}, numInputSamples = $inputIdx")
          optimalControls = Seq(
            diag00, diag01, diag02, diag03,
            diag10, diag11, diag12, diag13,
            diag20, diag21, diag22, diag23,
            diag30, diag31, diag32, diag33,
            diag40, diag41, diag42, diag43)
        }
      }
      //if(residualMetric < residualTarget) {
        outputFile.println(s"${Seq(p22, p33, /*x1, x2,*/ x1, x2, z1, z2, /*u1, u2,*/ u1, u2).mkString(",")},${optimalControls.mkString(",")},${currentResidual.get.getNorm}")
        outputFile.flush()
      //}
      (Seq(p22, p33, x1, x2, z1, z2, u1, u2), optimalControls)
    }
    outputFile.close()
    retval
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
//        val newP = Some(arr(1).asInstanceOf[RealMatrix])
        val res = Some(arr(2).asInstanceOf[RealVector])
        (newX, res)
      case None =>
        (None, None)
    }
  }
}
