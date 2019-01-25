package com.cra.princess.inputmodel.constructor

import com.cra.princess._

trait InputModelWriter {
  /**
    * @param model
    * @tparam Env
    * @tparam Input
    * @return - Serialized format of model
    */
  def writeInputModel[Env, Input](model:  InputModel[Env, Input]): String
}
