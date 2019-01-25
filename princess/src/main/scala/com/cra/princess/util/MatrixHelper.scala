package com.cra.princess.util

import org.apache.commons.math3.linear.{Array2DRowRealMatrix, LUDecomposition, RealMatrix}

/** Several common matrix operations not found in matrix libraries */
object MatrixHelper {

  /**
    * Performs element-wise multiplication of two matrices and returns the result as a new matrix
    */
  def elementWiseMultiply(mat1:RealMatrix, mat2:RealMatrix):RealMatrix = {
    new Array2DRowRealMatrix((0 until mat1.getRowDimension).map(i =>
      (0 until mat1.getColumnDimension).map(j =>
        mat1.getEntry(i, j) * mat2.getEntry(i, j)
      ).toArray
    ).toArray)
  }

  /** Calculates the determinant of a matrix in log-space. More numerically stable than getDeterminant() */
  def getLogDeterminant(decomp:LUDecomposition):Double = {
    val m: Int = decomp.getPivot().length

    // dangerous but necessary
    val f = decomp.getClass().getDeclaredField("even");
    f.setAccessible(true);
    val isEven:Boolean = f.get(decomp).asInstanceOf[Boolean]

    val parity = if (isEven) 1 else -1
    val lmat = decomp.getL
    val umat = decomp.getU
    val lterms = (0 until lmat.getRowDimension).map(i => math.log(lmat.getEntry(i, i))).sum
    val uterms = (0 until lmat.getRowDimension).map(i => math.log(umat.getEntry(i, i))).sum

    lterms + uterms + math.log(parity)
  }

}
