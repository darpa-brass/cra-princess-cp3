package com.cra.princess.componentmodel

import com.cra.princess._
import com.cra.princess.core._
import com.cra.princess.exceptions.UnsupportedTypeException
import com.cra.princess.util._
import org.apache.commons.math3.linear.{Array2DRowRealMatrix, RealMatrix}

//TODO: Many classes and functions in this file are unused and can be deleted (see deprecation annotations)
//TODO: If they are needed in the future, we can restore them via version control.
/**
 * General form of a covariance function, taking two items of type T and producing a measure
 */
trait CovarianceFunction[T] {

  /** Compute covariance between two instances */
  def apply(v1: T, v2: T): Double

  /**
    * Identify the number of nested kernels used in the computation.
    * When we do multiple kernel learning, this is necessary to appropriately normalize the result.
    */
  def numBaseKernels(): Double

  /**
    * General-purpose helper method to construct a kernel
    * matrix from two sample sets of equal dimension
    */
  def outer(samples1:Seq[T], samples2:Seq[T]):RealMatrix = {
    val cov = new Array2DRowRealMatrix(samples1.length, samples2.length)
    (0 until samples1.length).foreach(i => {
      val range2 = if(samples1 eq samples2) (i until samples2.length) else (0 until samples2.length)
      range2.foreach(j => {
        val covVal = apply(samples1(i), samples2(j))
        cov.setEntry(i, j, covVal)
        if(samples1 eq samples2)
          cov.setEntry(j, i, covVal)
      })
    })
    cov
  }
}

/**
 * Supports distance computation between values of the same type
 */
object DistanceUtil {

  /** Computes Euclidean distance between two vectors of the same dimension */
  def distance(v1:Seq[Double], v2:Seq[Double]):Double = {
    math.sqrt((0 until v1.length).map(i => math.pow(v1(i) - v2(i), 2)).sum)
  }

  /** Computes distance between two PRINCESS features. */
  def distance[T <: PrincessFeature](v1: T, v2: T): Double = {
    (v1, v2) match {
      case (a: ScalarPrincessFeature, b: ScalarPrincessFeature) => Math.abs(a.value - b.value)
      case (a: VectorPrincessFeature, b: VectorPrincessFeature) => {
        a.value.subtract(b.value).getNorm
      }
      case (a: MatrixPrincessFeature, b: MatrixPrincessFeature) => a.value.subtract(b.value).getNorm
      case (a: PrincessFeatureCollection, b: PrincessFeatureCollection) => 
        (0 until b.subfeatures.length).map(i => distance(a.subfeatures(i), b.subfeatures(i))).sum
      case _ => throw new UnsupportedTypeException("Don't know how to compute distance between " + v1 + " and " + v2);
    }
  }
}

/**
  * A covariance function for objects with no dimension.
  * This can be useful when adherence to a common API is necessary, even when some features are not present.
  * The feature assigns covariance one to all pairs objects, but has no weight when used in a combination of covariances.
  * @deprecated not being used in PRINCESS pipeline
  *
 */
class EmptyCovarianceFunction[T <: PrincessFeature](combinationType:KernelCombinationType.Value) extends CovarianceFunction[T] {
  override def apply(v1: T, v2: T): Double = 1
  override def numBaseKernels(): Double = combinationType match { case KernelCombinationType.Additive => 0 case KernelCombinationType.Multiplicative => 1}
  override def toString = "EmptyCovarianceFunction"
}

/** The Gaussian, or radial basis function kernel / covariance function
  * @deprecated not being used in PRINCESS pipeline
  */
class GaussianCovarianceFunction[T <: PrincessFeature](var bandwidth: Double) extends CovarianceFunction[T] {

  /** Computes covariance using the L2 norm */
  override def apply(v1: T, v2: T): Double = {
    if(bandwidth == 0) {
      if(DistanceUtil.distance(v1, v2) < 1e-10) 1 else 0
    } else {
      Math.exp(-Math.pow(DistanceUtil.distance(v1, v2), 2) / bandwidth)
    }
  }

  override def toString = "GaussianCovarianceFunction(bandwidth=" + bandwidth + ")"
  
  override def numBaseKernels() = 1.0
}

/**
  *  A Gaussian covariance function that handles scaling/unscaling arrays of data
  *
  * @param bandwidth The kernel bandwidth (sigma)
  * @param scaler Utility which will apply the scaling
  * @deprecated not being used in PRINCESS pipeline
  */
class ScalingGaussianCovarianceFunction(bandwidth:Double, scaler:FeatureScaler) extends CovarianceFunction[Seq[Double]] {

  override def apply(v1:Seq[Double], v2:Seq[Double]) = {
    Math.exp(-Math.pow(DistanceUtil.distance(scaler.scale(v1), scaler.scale(v2)), 2) / bandwidth)
  }

  override def numBaseKernels() = 1
}

object ScalingGaussianCovarianceFunction {

  /** Creates a Gaussian covariance function which automatically scales features */
  def apply(samples:Seq[Seq[Double]], quantile:Double=0.1) = {
    // sampling with replacement
    val sample1 = com.cra.figaro.util.random.shuffle[Int, IndexedSeq](0 until samples.length).map(samples(_))
    val sample2 = com.cra.figaro.util.random.shuffle[Int, IndexedSeq](0 until samples.length).map(samples(_))
    val scaler = new UnitFeatureScaler(samples)

    val deviations = (0 until samples.length).map(i => Math.pow(DistanceUtil.distance(scaler.scale(sample1(i)), scaler.scale(sample2(i))), 2)).sorted
    val bandwidth = deviations(math.ceil((deviations.length - 1) * quantile).toInt)
    new ScalingGaussianCovarianceFunction(bandwidth, scaler)
  }
}

/**
  * @deprecated not being used in PRINCESS pipeline
  */
object GaussianCovarianceFunction {
  /**
   * Constructs a GaussianCovarianceFunction using the specified bandwidth hyperparameter
    *
    * @param bandwidth Hyperparameter used to tune similarity between points. High bandwidth values yield higher similarity between distant points.
   */
  def apply[T <: PrincessFeature](bandwidth: Double) = new GaussianCovarianceFunction[T](bandwidth)

  /**
   * Constructs a GaussianCovarianceFunction, first estimating bandwidth as median of squared deviations of randomly sampled input rows.
    *
    * @param inputs Sequence of inputs, each input being a vector space member
   * @param bandwidthEstFraction Optional fraction of the training data to use when estimating the bandwidth
   * @param quantile Optional quantile of deviations to use when estimating sigma, should be within (0, 1)
   */
  def apply[T <: PrincessFeature](inputs: Seq[T], bandwidthEstFraction: Double = 1, quantile: Double = 0.1): GaussianCovarianceFunction[T] = {
    val sampleNum = math.floor(inputs.length * bandwidthEstFraction).toInt

    // sampling with replacement
    val sample1 = com.cra.figaro.util.random.shuffle[Int, IndexedSeq](0 until inputs.length).take(sampleNum).map(inputs(_))
    val sample2 = com.cra.figaro.util.random.shuffle[Int, IndexedSeq](0 until inputs.length).take(sampleNum).map(inputs(_))

    val sortedDevs = (0 until sampleNum).map(i => Math.pow(DistanceUtil.distance(sample1(i), sample2(i)), 2)).sorted
    val highIndex = math.ceil((sortedDevs.length - 1) * quantile).toInt
    val lowIndex = math.floor((sortedDevs.length - 1) * quantile).toInt
    if(highIndex == lowIndex) {
      val sigma = sortedDevs(highIndex)
      apply(sigma)
    } else {
      val balance = ((sortedDevs.length - 1) * quantile) % 1
      val sigma = balance * sortedDevs(highIndex) + (1 - balance) * sortedDevs(lowIndex)
      apply(sigma)
    }
  }
}

object KernelCombinationType extends Enumeration {
  val Additive, Multiplicative = Value
}

/**
  * A uniform linear combination of kernels
  * @param covariances The covariance functions to combine
  * @param combinationType Specifies the mechanism by which the covariances will be combined (i.e. additively or multiplicatively)
  */
class LinearlyNestedCovarianceFunction(covariances: Seq[CovarianceFunction[PrincessFeature]], combinationType:KernelCombinationType.Value)
  extends CovarianceFunction[Seq[PrincessFeature]] {

  def apply(v1: Seq[PrincessFeature], v2: Seq[PrincessFeature]): Double = {
    combinationType match {
      case KernelCombinationType.Multiplicative => {
        val elts = ((0 until covariances.length) map { i => covariances(i).apply(v1(i), v2(i)) })
        elts.foldLeft(1.0)((v, n) => v * n)
      }
      case KernelCombinationType.Additive => {
        ((0 until covariances.length) map { i => covariances(i).numBaseKernels * covariances(i).apply(v1(i), v2(i)) } sum) / numBaseKernels
      }
    }
  }

  override def numBaseKernels() = covariances map { c => c.numBaseKernels() } sum
}

/**
  * Constructors for various nested kernels
  * @deprecated object not used in PRINCESS pipeline
  */
object LinearlyNestedCovarianceFunction {

  /**
   * Builds a covariance function for a PrincessFeature,
   * possibly estimating the hyperparameters of that function from data
   * @deprecated not being used in PRINCESS pipeline
   */
  def buildCovariance[T <: PrincessFeature](values: Seq[T])(implicit combinationType:KernelCombinationType.Value): CovarianceFunction[T] = {
    values(0) match {
      case (d: ScalarPrincessFeature) => GaussianCovarianceFunction(values)

      // zero-length vectors are okay (for convenience), these get fixed covariance 1 and no weight
      case (d: VectorPrincessFeature) => if (d.value.getDimension == 0) new EmptyCovarianceFunction(combinationType) else GaussianCovarianceFunction(values)

      case (d: MatrixPrincessFeature) => GaussianCovarianceFunction(values)
      case (d: PrincessFeatureCollection) => {
        val nfeatures = d.subfeatures.length
        // empty collections are okay, these get a zero-weight covariance
        if (nfeatures == 0) {
          new EmptyCovarianceFunction[T](combinationType)
        } else {
          val covariances = (0 until nfeatures).map(i => buildCovariance(values.map(v => v.asInstanceOf[PrincessFeatureCollection].subfeatures(i)))(combinationType))
          val backingFun = new LinearlyNestedCovarianceFunction(covariances, combinationType)

          // converting from Seq[PrincessElement] to PrincessFeatureCollection
          new CovarianceFunction[T] {
            override def apply(v1: T, v2: T) = {
              val features1 = v1.asInstanceOf[PrincessFeatureCollection]
              val features2 = v2.asInstanceOf[PrincessFeatureCollection]
              backingFun(features1.subfeatures, features2.subfeatures)
            }
            
            override def numBaseKernels() = backingFun.numBaseKernels()
          }
        }
      }
      case _ => throw new UnsupportedTypeException("Don't know how to choose a covariance function for " + values(0).getClass)
    }
  }

  /**@deprecated not being used in PRINCESS pipeline*/
  def apply(table: Seq[PrincessFeature]*)(implicit combinationType:KernelCombinationType.Value) = {
    val covFuns = table map { featureData =>
      LinearlyNestedCovarianceFunction.buildCovariance(featureData)(combinationType)
    }

    new LinearlyNestedCovarianceFunction(covFuns, combinationType)
  }
}

/**
  * A uniform linear combination of three kernels.
  * This gets a lot of use in modeling (Env, Input, Control) tuples.
  * @deprecated class not being used in PRINCESS pipeline
  */
class LinearlyNestedCovarianceFunction3[T1 <: PrincessFeature, T2 <: PrincessFeature, T3 <: PrincessFeature]
  (covariance1: CovarianceFunction[T1], covariance2: CovarianceFunction[T2], covariance3: CovarianceFunction[T3],
   combinationType:KernelCombinationType.Value)
  extends CovarianceFunction[(T1, T2, T3)] {

  /**@deprecated not being used in PRINCESS pipeline*/
  def apply(v1: (T1, T2, T3), v2: (T1, T2, T3)): Double = {
    combinationType match {
      case KernelCombinationType.Multiplicative => {
        (covariance1.apply(v1._1, v2._1) *
         covariance2.apply(v1._2, v2._2) *
          covariance3.apply(v1._3, v2._3))
      }
      case KernelCombinationType.Additive => {
        (covariance1.numBaseKernels() * covariance1.apply(v1._1, v2._1) +
          covariance2.numBaseKernels() * covariance2.apply(v1._2, v2._2) +
          covariance3.numBaseKernels() * covariance3.apply(v1._3, v2._3)) / numBaseKernels()
      }
    }
  }
  /**@deprecated not being used in PRINCESS pipeline*/
  override def numBaseKernels() = covariance1.numBaseKernels() + covariance2.numBaseKernels() + covariance3.numBaseKernels()
}

/**
  * Constructors for various nested kernels
  * @deprecated object not being used in PRINCESS pipeline
  */
object LinearlyNestedCovarianceFunction3 {
  /**@deprecated not being used in PRINCESS pipeline*/
  def apply[T1 <: PrincessFeature, T2 <: PrincessFeature, T3 <: PrincessFeature](input1: Seq[T1], input2: Seq[T2], input3: Seq[T3])
                                                                                (implicit combinationType:KernelCombinationType.Value) = {
    new LinearlyNestedCovarianceFunction3(
      LinearlyNestedCovarianceFunction.buildCovariance(input1)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input2)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input3)(combinationType), combinationType)
  }

  /**@deprecated not being used in PRINCESS pipeline*/
  def apply[T1 <: PrincessFeature, T2 <: PrincessFeature](input1: Seq[T1], input2: Seq[T2], input3: Seq[ComponentControls])
                                                         (implicit combinationType:KernelCombinationType.Value) = {
    val baseFun = new LinearlyNestedCovarianceFunction3(
      LinearlyNestedCovarianceFunction.buildCovariance(input1)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input2)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input3.map(c => new PrincessFeatureCollection(c)))(combinationType), combinationType)
    
        // wrap calls for covariance into feature collections
    new CovarianceFunction[(T1, T2, ComponentControls)] {
      override def apply(v1: (T1, T2, ComponentControls), v2: (T1, T2, ComponentControls)) = 
          baseFun((v1._1, v1._2, new PrincessFeatureCollection(v1._3)), (v2._1, v2._2, new PrincessFeatureCollection(v2._3)))
          
      override def numBaseKernels() = baseFun.numBaseKernels()
    }
  }
}

/**
  * A uniform linear combination of four kernels
  * @deprecated Class not being used in PRINCESS pipeline
  */
class LinearlyNestedCovarianceFunction4[T1 <: PrincessFeature, T2 <: PrincessFeature, T3 <: PrincessFeature, T4 <: PrincessFeature]
  (covariance1: CovarianceFunction[T1], covariance2: CovarianceFunction[T2],
    covariance3: CovarianceFunction[T3], covariance4: CovarianceFunction[T4], combinationType: KernelCombinationType.Value)
  extends CovarianceFunction[(T1, T2, T3, T4)] {

  def apply(v1: (T1, T2, T3, T4), v2: (T1, T2, T3, T4)): Double = {
    combinationType match {
      case KernelCombinationType.Multiplicative => {
        (covariance1.apply(v1._1, v2._1) *  covariance2.apply(v1._2, v2._2) *
          covariance3.apply(v1._3, v2._3) * covariance4.apply(v1._4, v2._4))
      }
      case KernelCombinationType.Additive => {
        (covariance1.numBaseKernels() * covariance1.apply(v1._1, v2._1) +
          covariance2.numBaseKernels() * covariance2.apply(v1._2, v2._2) +
          covariance3.numBaseKernels() * covariance3.apply(v1._3, v2._3) +
          covariance4.numBaseKernels() * covariance4.apply(v1._4, v2._4)) / numBaseKernels()
      }
    }
  }

  override def numBaseKernels() = covariance1.numBaseKernels() + covariance2.numBaseKernels() + covariance3.numBaseKernels() +  covariance4.numBaseKernels()
}

/**@deprecated Object not being used in PRINCESS pipeline*/
object LinearlyNestedCovarianceFunction4 {
  
  def apply[T1 <: PrincessFeature, T2 <: PrincessFeature, T3 <: PrincessFeature, T4 <: PrincessFeature](
      input1: Seq[T1], input2: Seq[T2], input3: Seq[T3], input4: Seq[T4])(implicit combinationType:KernelCombinationType.Value) = {
    new LinearlyNestedCovarianceFunction4(
      LinearlyNestedCovarianceFunction.buildCovariance(input1)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input2)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input3)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input4)(combinationType), combinationType)
  }  
  
  def apply[T1 <: PrincessFeature, T2 <: PrincessFeature, T3 <: PrincessFeature]
        (input1: Seq[T1], input2: Seq[T2], input3:Seq[T3], input4: Seq[ComponentControls])(implicit combinationType:KernelCombinationType.Value) = {
    val baseFun = new LinearlyNestedCovarianceFunction4(
      LinearlyNestedCovarianceFunction.buildCovariance(input1)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input2)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input3)(combinationType),
      LinearlyNestedCovarianceFunction.buildCovariance(input4.map(c => new PrincessFeatureCollection(c)))(combinationType), combinationType)
    
        // wrap calls for covariance into feature collections
    new CovarianceFunction[(T1, T2, T3, ComponentControls)] {
      override def apply(v1: (T1, T2, T3, ComponentControls), v2: (T1, T2, T3, ComponentControls)) = 
          baseFun((v1._1, v1._2, v1._3, new PrincessFeatureCollection(v1._4)), (v2._1, v2._2, v2._3, new PrincessFeatureCollection(v2._4)))
          
      override def numBaseKernels() = 1 
    }
  }
}

/**
  * An adaptor which flattens princess features into numeric representations,
  * and applies a Gaussian covariance function to the flattened representation
  */
object FlatteningGaussianCovarianceFunction3 {
  def apply[T1 <: PrincessFeature, T2 <: PrincessFeature]
  (input1: Seq[T1], input2: Seq[T2], input3: Seq[ComponentControls],
   sigmaEstQuantile:Double=0.1) = {
    def flatten(r: (T1, T2, ComponentControls)): Seq[Double] = {
      PrincessTypeUtility.flatten(r._1) ++ PrincessTypeUtility.flatten(r._2) ++
        PrincessTypeUtility.flatten(r._3)
    }

    val samples = (0 until input1.size).map(i => {
      flatten((input1(i), input2(i), input3(i)))
    })
    val baseCov = ScalingGaussianCovarianceFunction(samples)

    // wrap calls for covariance into feature collections
    new CovarianceFunction[(T1, T2, ComponentControls)] with Logs {
      override def apply(v1: (T1, T2, ComponentControls), v2: (T1, T2, ComponentControls)) =
        baseCov(flatten(v1), flatten(v2))

      /** more efficiently creates a covariance by first flattening all instances */
      override def outer(samp1: Seq[(T1, T2, ComponentControls)], samp2: Seq[(T1, T2, ComponentControls)]): RealMatrix = {
        val inputs1 = samp1.map(s => flatten(s))
        if (samp1 eq samp2) {
          baseCov.outer(inputs1, inputs1)
        } else {
          val inputs2 = samp2.map(s => flatten(s))
          baseCov.outer(inputs1, inputs2)
        }
      }

      override def numBaseKernels() = 1
    }
  }
}

/**
  * An adaptor which flattens princess features into numeric representations,
  * and applies a product Gaussian covariance functions, one function for controls and one function for env/input
  */
object FlatteningGaussianProductCovarianceFunction3 {

  def apply[T1 <: PrincessFeature, T2 <: PrincessFeature]
  (input1: Seq[T1], input2: Seq[T2], input3: Seq[ComponentControls],
    sigmaEstQuantile:Double=0.1) = {

    def flatten(r : (T1, T2)): Seq[Double] = {
      PrincessTypeUtility.flatten(r._1) ++ PrincessTypeUtility.flatten(r._2)
    }

    val inputSamples = (0 until input1.size).map(i => { flatten((input1(i), input2(i))) })
    val controlSamples = (0 until input1.size).map(i => { PrincessTypeUtility.flatten(input3(i)) })

    val inputCov = ScalingGaussianCovarianceFunction(inputSamples)
    val controlCov = ScalingGaussianCovarianceFunction(controlSamples)

    // wrap calls for covariance into feature collections
    new CovarianceFunction[(T1, T2, ComponentControls)] with Logs {
      override def apply(v1: (T1, T2, ComponentControls), v2: (T1, T2, ComponentControls)) =
            inputCov(flatten((v1._1, v1._2)), flatten(v2._1, v2._2)) *
              controlCov(PrincessTypeUtility.flatten(v1._3), PrincessTypeUtility.flatten(v2._3))

      /** more efficiently creates a covariance by first flattening all instances */
      override def outer(samp1:Seq[(T1, T2, ComponentControls)], samp2:Seq[(T1, T2, ComponentControls)]):RealMatrix = {
        val flatInputs1 = samp1.map(s => flatten((s._1, s._2)))
        val flatControls1 = samp1.map(s => PrincessTypeUtility.flatten(s._3))
        if(samp1 eq samp2) {
          MatrixHelper.elementWiseMultiply(inputCov.outer(flatInputs1, flatInputs1), controlCov.outer(flatControls1, flatControls1))
        } else {
          val flatInputs2 = samp2.map(s => flatten((s._1, s._2)))
          val flatControls2 = samp2.map(s => PrincessTypeUtility.flatten(s._3))
          MatrixHelper.elementWiseMultiply(inputCov.outer(flatInputs1, flatInputs2), controlCov.outer(flatControls1, flatControls2))
        }
      }

      override def numBaseKernels() = 1
    }
  }
}
