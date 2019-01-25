package com.cra.princess.inputmodel.constructor

import com.cra.princess.InputModel

trait InputModelBuilder[Env, Input]{
  def buildInputModel(trainingData: List[(Env, Input)]) : InputModel[Env, Input]
}
