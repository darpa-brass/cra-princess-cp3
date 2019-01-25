package com.cra.princess.core

import com.cra.figaro.language._
import com.cra.figaro.library.atomic._
import com.cra.figaro.util._
import com.cra.princess.Control
import org.apache.commons.math3.linear._

import scala.collection.JavaConverters._
import scala.language.implicitConversions


trait PrincessFeature extends Serializable

/** A PrincessFeature that can create a prior element */
trait PriorPrincessFeature extends PrincessFeature {
  /**
    * @param name - Figaro Name
    * @param collection - Figaro ElementCollection
    * @return prior probability distribution of this PrincessFeature
    */
  def prior(name:Name[PriorPrincessFeature], collection:ElementCollection):Element[PriorPrincessFeature]
}

/** A PrincessFeature which is a container of other features
  * @param subfeatures - Sequence of PrincessFeatures
  */
class PrincessFeatureCollection(val subfeatures: Seq[PrincessFeature]) extends PrincessFeature with Serializable {
  // for convenience in mapping controls
  def this(subfeatures: List[PriorPrincessFeature]) =
    this(subfeatures.map(s => s.asInstanceOf[PrincessFeature]))
  def this(subfeatures: Map[String, Control]) =
    this(subfeatures.toSeq.sortBy(_._1).map(s => s._2.asInstanceOf[PrincessFeature]))
}

object PrincessFeatureCollection {
  def apply(subfeatures: PrincessFeature*) = new PrincessFeatureCollection(subfeatures)
}

/** Represents a selection from a finite set of choices
  * @param value - Some integer value
  * @param start - Lower bound
  * @param bound - Upper bound
  */
class DiscretePrincessFeature(val value: Int, val start:Int, val bound: Int)
  extends PrincessFeature with PriorPrincessFeature  with Serializable {
  override def toString = "DiscretePrincessFeature(" + value.toString + ")"
  
  override def prior(name:Name[PriorPrincessFeature], collection:ElementCollection) = {
    discrete.Uniform((start to bound).map(v =>
      new DiscretePrincessFeature(v, bound, start).asInstanceOf[PriorPrincessFeature]):_*)(name, collection)
  }
}

/** Represents a selection from an finite set of distinct integers.
  * Mechanically identical to DiscretePrincessFeature but with different semantics.
  * DiscretePrincessFeature has no ordering.
  * @param value - Some integer value
  * @param start - Lower bound
  * @param bound - Upper bound
  */
class OrdinalPrincessFeature(value:Int, val start:Int, val bound:Int)
  extends ScalarPrincessFeature(value) with PriorPrincessFeature {
  override def toString = "OrdinalPrincessFeature(" + value.toString + ")"
  override def prior(name: Name[Control], collection: ElementCollection): Element[Control] =
    discrete.Uniform((start to bound).map(v =>
      new OrdinalPrincessFeature(v, bound, start).asInstanceOf[PriorPrincessFeature]):_*)(name, collection)

  val intValue = value
}

/** Represents a real valued variable in an infinite sample space
  * @param value - Double value to be used in PRINCESS
  */
class ScalarPrincessFeature(val value: Double) extends PrincessFeature with Serializable {
  override def toString = s"ScalarPrincessFeature($value)"
}

/** A real-valued Princess feature with a (possibly truncated) normal prior
  * @param value - Double value to be used in PRINCESS
  * @param mean - mean
  * @param stdDev - standard deviation
  * @param lowBound - lower truncation (default negative infinity)
  * @param upperBound - upper truncation (default positive infinity)
  */
class NormalPriorPrincessFeature(value:Double,
                                 val mean:Double,
                                 val stdDev:Double,
                                 val lowBound:Double=Double.NegativeInfinity,
                                 val upperBound:Double=Double.PositiveInfinity)
  extends ScalarPrincessFeature(value) with PriorPrincessFeature with Serializable {
  override def prior(name: Name[Control], collection: ElementCollection): Element[Control] =
      new NormalScalarPrincessElement(mean, stdDev, lowBound, upperBound, name, collection)
}

/** A real-valued Princess feature with an inclusive lower and upper bound
  * @param value - Double value to be used in PRINCESS
  * @param lowerBound - some lower bound
  * @param upperBound - some upper bound
  */
class BoundedScalarPrincessFeature(value: Double, val lowerBound: Double, val upperBound: Double)
  extends ScalarPrincessFeature(value) with PriorPrincessFeature with Serializable {
  
  override def prior(name:Name[PriorPrincessFeature], collection:ElementCollection) =
    new UniformScalarPrincessElement(lowerBound, upperBound, name, collection)
  override def toString = s"BoundedScalarPrincessFeature($value, lower=$lowerBound, upper=$upperBound)"
}

/** Represents a vector-valued feature
  * @param value - RealVector to be used in PRINCESS
  */
class VectorPrincessFeature(val value: RealVector) extends PrincessFeature with Serializable {
  def this(val0: Seq[Double]) = this(new ArrayRealVector(val0 toArray))
  val x = value.iterator().asScala.map(e => e.getValue)
  override def toString = "VectorPrincessFeature" +
    "(" + value.iterator().asScala.map(e => e.getValue).mkString(", ") + ")"
}

/** Represents a matrix-valued feature
  * @param value - RealMatrix to be used in PRINCESS
  */
class MatrixPrincessFeature(val value: RealMatrix) extends PriorPrincessFeature with Serializable {
  def this(val0: Seq[Seq[Double]]) = this(new Array2DRowRealMatrix(val0 map { r => r toArray } toArray))
  override def toString = {
    val contents = (0 until value.getRowDimension) map { r =>
      (0 until value.getColumnDimension) map { c =>
        value.getEntry(r, c)
      } mkString " "
    } mkString "; "
    s"MatrixPrincessFeature($contents)"
  }

  /**
    * @param name       - Figaro Name
    * @param collection - Figaro ElementCollection
    * @return prior probability distribution of this PrincessFeature
    */
  override def prior(name: Name[Control], collection: ElementCollection): Element[Control] =
    Constant(new MatrixPrincessFeature(value).asInstanceOf[PriorPrincessFeature])(name, collection)
}

/** An atomic distribution over Princess features backed by a (possibly truncated) normal
  * @param mean - Double value
  * @param stdDev - Double Value
  * @param lowBound - Double Value
  * @param upperBound - Double Value
  * @param name - Figaro Name
  * @param elementCollection - Figaro Element Collection
  */
class NormalScalarPrincessElement(val mean: Double,
                                  val stdDev: Double,
                                  lowBound: Double,
                                  upperBound: Double,
                                  name: Name[PriorPrincessFeature],
                                  elementCollection: ElementCollection)
  extends Element[Control](name, elementCollection) with HasDensity[PriorPrincessFeature] with Atomic[Control] {
  type Randomness = Double

  def normalDensity(v:Double) = {
    1.0 / Math.sqrt(2 * Math.pow(stdDev, 2)) * Math.exp(- math.pow(v - mean, 2) / (2 * Math.pow(stdDev, 2)))
  }
  override def density(elt:PriorPrincessFeature) = {
    val normFeature = elt.asInstanceOf[ScalarPrincessFeature]
    normalDensity(normFeature.value)
  }
  override def nextRandomness(rand: Randomness) = {
    val next = Math.max(lowBound, Math.min(upperBound, rand + random.nextGaussian() * stdDev + mean))
    (next, 1.0, normalDensity(next) / normalDensity(rand))
  }

  def generateRandomness() = random.nextGaussian()

  /**samples from distribution*/
  def generateValue(rand: Randomness) = {
    val boundedVal = Math.max(lowBound, Math.min(upperBound, rand * stdDev + mean))
    new NormalPriorPrincessFeature(boundedVal, mean, stdDev, lowBound, upperBound)
  }
  override def toString = s"NormalScalarPrincessElement(${value.toString}, mean=$mean, stddev=$stdDev)"
}

/** Represents a uniform distribution over Princess features backed by a uniform */
class UniformScalarPrincessElement(val lowerBound:Double, val upperBound:Double,
                                   name:Name[PriorPrincessFeature], elementCollection: ElementCollection)
  extends Element[Control](name, elementCollection) with Atomic[Control] {

  type Randomness = Double
  val proposalStdDev = (upperBound - lowerBound) / 20.0

  // rough but better than proposing uniformly
  override def nextRandomness(rand: Randomness) = {
    val next = Math.min(upperBound, Math.max(lowerBound, rand + random.nextGaussian() * proposalStdDev))
    (next, 1.0, 1.0)
  }

  val constantDensity = 1.0 / (upperBound - lowerBound)
  override def density(t: Control): Double = constantDensity
  def generateRandomness() = random.nextDouble() * (upperBound - lowerBound) + lowerBound
  def generateValue(rand: Randomness) = {
    new BoundedScalarPrincessFeature(rand, lowerBound, upperBound)
  }
  override def toString = s"UniformScalarPrincessElement(${value.toString}, lower=$lowerBound, upper=$upperBound)"
}

// TODO: Instance and Identity builders may be adding unnecessary complexity -Klu

/** A pattern used to build instances from Princess Features */
trait InstanceBuilder[Build] {
  def build(feature:PrincessFeature):Build
}

/** A simple variant of the instance builder which simply casts the PrincessFeature to the target type */
class IdentityBuilder[Build] extends InstanceBuilder[Build] {
  def build(feature:PrincessFeature) = feature.asInstanceOf[Build]
}

object IdentityBuilder {
  def apply[T]() = new IdentityBuilder[T]()
}


object PrincessTypeImplicits {
  implicit def toPrincessType(v: Seq[Double]):    VectorPrincessFeature = new VectorPrincessFeature(v)
  implicit def toPrincessType(v: Array[Double]):  VectorPrincessFeature = new VectorPrincessFeature(v.toSeq)
  implicit def toPrincessType(v: List[Double]):   VectorPrincessFeature = new VectorPrincessFeature(v)
  implicit def toPrincessType(v: RealVector):     VectorPrincessFeature = new VectorPrincessFeature(v)
  implicit def toPrincessType(v: Double):         ScalarPrincessFeature = new ScalarPrincessFeature(v)
  implicit def toPrincessType(v: RealMatrix):     MatrixPrincessFeature = new MatrixPrincessFeature(v)
}