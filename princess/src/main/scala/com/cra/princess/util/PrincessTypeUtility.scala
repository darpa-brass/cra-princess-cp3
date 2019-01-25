package com.cra.princess.util

import com.cra.princess.exceptions._
import com.cra.princess._
import com.cra.princess.componentmodel.ComponentModelInput
import com.cra.princess.core._
import org.apache.commons.math3.linear._

/**
  * Helper methods for transforming PrincessFeatures into flat representations (arrays of real values),
  * and back to the structured PrincessFeature types.
  *
  * The flat feature vector representation be readily used by many machine learning algorithms.
  * The PrincessFeature representation has more semantics and structure than the flat representation.
  *
  * Flattening works as follows:
  *   For VectorPrincessFeatures, extract the values as an array
  *   For MatrixPrincessFeatures, serialize to an array in row-major order
  *   For ScalarPrincessFeatures, represent the value into a singleton array
  *   For DiscretePrincessFeatures, represent the value as a d-dimensional binary vector, where d is the size of the feature's domain.
  *     Set one bit representing the choice. Leave all other bits unset. This is referred to as one-hot encoding.
  *   For PrincessFeatureCollections, decompose the collections, apply the rules above, and horizontally stack the resulting arrays
  */
object PrincessTypeUtility {
  
  /**
   * Converts a feature in a flat vector representation to a PrincessFeature
   * @param featureDef Definition of the PrincessFeature type to deserialize into
   * @param sample The content to deserialize  
   * @param startIndex Indicates where in sample deserialization should begin
   * @return The unflattened type and the number of elements consumed
   */
  private def baseUnflatten(featureDef:PrincessFeature, sample:Seq[Double], startIndex:Int = 0) : (PrincessFeature, Int) = {
    featureDef match {
      case (a:PrincessFeatureCollection) => {
        // extract each sub-component from the array
        var newStartIdx = startIndex
        val elts = a.subfeatures.map(s => { 
          val result = baseUnflatten(s, sample, newStartIdx)
          newStartIdx += result._2
          result._1
        })
        (new PrincessFeatureCollection(elts), newStartIdx - startIndex)
      }
      case (a:BoundedScalarPrincessFeature) => (new BoundedScalarPrincessFeature(sample(startIndex), a.lowerBound, a.upperBound), 1)
      case (a:NormalPriorPrincessFeature) => (new NormalPriorPrincessFeature(sample(startIndex), a.mean, a.stdDev), 1)
      case (a:OrdinalPrincessFeature) => (new OrdinalPrincessFeature(sample(startIndex).toInt, a.start, a.bound), 1)
      case (a:ScalarPrincessFeature) => (new ScalarPrincessFeature(sample(startIndex)), 1)

      case (a:VectorPrincessFeature) => {
        var toConsume = sample.toArray.drop(startIndex).take(a.value.getDimension)
        (new VectorPrincessFeature(new ArrayRealVector(toConsume)), a.value.getDimension)
      }
      
      case (a:MatrixPrincessFeature) => {
        // unwrap in row-major order
        val nelts = a.value.getRowDimension * a.value.getColumnDimension
        val toConsume = sample.toArray.drop(startIndex).take(nelts)
        val matricized = (0 until a.value.getRowDimension)
          .map(i => toConsume.slice(a.value.getRowDimension * i, a.value.getRowDimension * i + a.value.getColumnDimension)).toArray
        (new MatrixPrincessFeature(new Array2DRowRealMatrix(matricized)), nelts)
      }

      case (d:DiscretePrincessFeature) => {
        val nelts = d.bound - d.start
        val contents = sample.drop(startIndex).take(nelts)
        val activePosition = (0 until nelts).find(i => contents(i) == 1).get + d.start
        (new DiscretePrincessFeature(activePosition, d.start, d.bound), nelts)
      }

      case _ => throw new UnsupportedTypeException("PrincessTypeUtility cannot handle sample: " + featureDef)
    }
  }
  
  /**
   * Converts an (Env, Input) represented in a flat vector representation back into PrincessFeature form
   * @param origSample An (environment, input) tuple used to recover environment and input metadata
   * @param sample A raw sample to deserialize
   * @param envBuilder Creates an environment type from a PrincessFeature
   * @param inputBuilder Creates an input type from a PrincessFeature 
   */
  def unflatten[Env <: PrincessFeature, Input <: PrincessFeature](
      origSample:(Env, Input),  sample:Seq[Double], envBuilder:InstanceBuilder[Env], inputBuilder:InstanceBuilder[Input]) = {
    
    val numEnvFeatures = flatten(origSample._1).length
    
    (envBuilder.build(baseUnflatten(origSample._1, sample.take(numEnvFeatures))._1), 
        inputBuilder.build(baseUnflatten(origSample._2, sample.drop(numEnvFeatures))._1))
  }
  
  def unflatten(featureDef:PrincessFeature, sample:Seq[Double]) = baseUnflatten(featureDef, sample)._1
  def unflatten(featureDef:ComponentControls, sample:Seq[Double]):ComponentControls = {
    val unflattened = baseUnflatten(new PrincessFeatureCollection(featureDef), sample)._1.asInstanceOf[PrincessFeatureCollection]
    featureDef.keys.toList.sorted.zipWithIndex.map(ki => (ki._1, unflattened.subfeatures(ki._2).asInstanceOf[Control])).toMap
  }

  /**
   *  Flattens PrincessFeatures into a fixed-length vector of real numbers.
   *  @throws UnsupportedTypeException if the PrincessFeature is composed of non-real components.
   */
  def flatten(sample:PrincessFeature):Seq[Double] = {
    sample match { 
      case (a:PrincessFeatureCollection) => a.subfeatures.flatMap(flatten)
      case (a:ScalarPrincessFeature) => Seq(a.value)
      case (a:VectorPrincessFeature) => a.value.toArray()
      case (a:MatrixPrincessFeature) => a.value.getData.flatMap(r => r)
      case (a:DiscretePrincessFeature) => (a.start to a.bound).map(i => if(i == a.value) 1.0 else 0.0)
      case _ => throw new UnsupportedTypeException("PrincessTypeUtility cannot handle sample: " + sample)
    }
  }

  def flatten[T1 <: PrincessFeature, T2 <: PrincessFeature](sample:(T1, T2, ComponentControls)):Seq[Double] = {
    PrincessTypeUtility.flatten(sample._1) ++ PrincessTypeUtility.flatten(sample._2) ++ PrincessTypeUtility.flatten(sample._3)
  }

  def flatten[T1 <: PrincessFeature, T2 <: PrincessFeature, T3 <: PrincessFeature](sample:(T1, T2, T3, ComponentControls)):Seq[Double] = {
    PrincessTypeUtility.flatten(sample._1) ++ PrincessTypeUtility.flatten(sample._2) ++
      PrincessTypeUtility.flatten(sample._3) ++ PrincessTypeUtility.flatten(sample._4)
  }

  def flatten(featureDef:ComponentControls):Seq[Double] = {
    flatten(new PrincessFeatureCollection(featureDef))
  }

  def flatten[Env <: PrincessFeature, Input <: PrincessFeature](t:(Env, Input)):Seq[Double] = {
    flatten(t._1) ++ flatten(t._2)
  }

  def flatten[Env <: PrincessFeature, Input <: PrincessFeature](record:ComponentModelInput[Env, Input]):Seq[Double] = {
    flatten(record.env) ++ flatten(record.input) ++ flatten(new PrincessFeatureCollection(record.controls))
  }
}