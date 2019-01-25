package com.cra.princess.core

/**
  * Specifies the entry point for static analysis of a component
 *
  * @param className The VM signature of the class
  * @param method The VM signature of the method
  */
class StaticAnalysisEntryPoint(val className:String, val method:String)

/**
  * An optimizable component that supports static code analysis
  */
trait StaticallyAnalyzableComponent[Env <: PrincessFeature, Input <: PrincessFeature, Output] extends OptimizableComponent[Env, Input, Output] {
  def entryPoint():StaticAnalysisEntryPoint

  // may want to put other things here, like input field mapping information
}
