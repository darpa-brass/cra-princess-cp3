package com.cra.princess.inputmodel.constructor

import com.cra.princess._

trait InputModelReader[Env, Input]{
  def readInputModel(modelData: String) : InputModel[Env, Input]
}
