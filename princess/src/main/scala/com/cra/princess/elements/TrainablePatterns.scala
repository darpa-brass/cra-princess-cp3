package com.cra.princess.elements

import com.cra.figaro.language.Element

/**
 * A model which is trained based on observed data.
 * This may belong in Figaro.
 * @author Dan Garant
 * @tparam Input Type of one instance of the input data
 * @tparam Output Type of one instance of the output data
 */
trait TrainableModel[Input, Output] {
  
  /** Produce an output corresponding to the specified input */
  def model(input:Input):Element[Output]
  
  /** Fit the parameters of the model given a set of inputs */
  def train(data:List[(Input, Output)])
  
}