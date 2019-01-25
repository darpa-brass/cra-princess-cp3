package com.cra.princess.monitor

import com.cra.princess.ComponentControls
import com.cra.princess.core.{ComponentAdaptationManager, PrincessFeature}
import com.cra.princess.util.{Logs, Recognizer}

import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.Future
import scala.reflect.ClassTag
import scala.reflect.runtime.universe._

class ComponentMonitor[Env <: PrincessFeature: ClassTag, Input <: PrincessFeature: ClassTag, Output](componentAdaptationManager: ComponentAdaptationManager[Env, Input, Output]) extends Logs {

  def component = componentAdaptationManager.component

  def passToComponent(args: Array[Any]): Output = {
    // Turn args into Input, Env, and ComponentControls
    if (args.length != 3) throw new IllegalArgumentException("Incorrect number of arguments to component method: " + args.length)
    args match {
      case Array(env: Env, input: Input, p3) => {
        val controls: ComponentControls = p3 match {
          case null => null
          case _ => if (Recognizer.recognize[ComponentControls](p3)) {
            val c: ComponentControls = p3.asInstanceOf[ComponentControls]
            c
          } else {
            log.error("Control variable argument is wrong type")
            throw new IllegalArgumentException("Control variable argument is wrong type")
          }
        }
        val result = try {
          component.component(env, input, controls)
        } catch {
          case e: Exception => {
            //tha.sendErrorMessage(TestHarnessAdapterConstants.ERROR_ADAPTATION_FAILURE, e.getMessage)
            e.printStackTrace()
            throw new MonitorException(e)
          }
        }

        Future[Unit] {
          componentAdaptationManager.handleComponentIO(env, input, result)
        }

        result
      }
    }
  }
}
