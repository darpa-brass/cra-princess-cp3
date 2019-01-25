package com.cra.princess.monitor

import com.cra.princess.componentmodel.{ComponentModel, ControlGenerator}
import com.cra.princess.{ComponentControls, ComponentMetrics, InputModel}
import com.cra.princess.core._
import org.scalatest.{FlatSpec, Matchers}
import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.princess.optimizer.ComponentOptimizer
import scala.reflect._

class ComponentMonitorTest extends FlatSpec with Matchers {

  // Enforce that the handleComponentIO method on the CAM gets called
  // Enforce that the original method got properly called

  "A ComponentMonitor" should "monitor calls to the 'component' method on an OptimizableComponent" in {
    val thing = new SimpleThing((d: Double) => d * d)
    val comp = new SimpleThingComponentImpl(thing)
    val cam = new DummyComponentAdaptationManager(comp, new SimpleThingOptimizer)
    val monitor = new ComponentMonitor(cam)
    val wrapped = java.lang.reflect.Proxy.newProxyInstance(
      this.getClass.getClassLoader,
      Array[Class[_]](classTag[SimpleThingComponent].runtimeClass),
      new MonitorProxy[SimpleThingEnvironment, SimpleThingInput, Double](comp, monitor)) match {
      case good: SimpleThingComponent => good
      case _ => throw new IllegalStateException()
    }

    cam.invoked should equal (false)
    thing.doThing(4) should equal (16)
    thing.doThing(-5) should equal (25)

    cam.invoked should equal (false)
    comp.component(new SimpleThingEnvironment, new SimpleThingInput(5), null) should equal (25)
    cam.invoked should equal (false)

    wrapped.component(new SimpleThingEnvironment, new SimpleThingInput(-4), null) should equal (16)
    Thread.sleep(500) // wait for asynchronous business to finish up
    cam.invoked should equal (true)

  }
}

// Create a dummy object
// Create an OptimizableComponent to encapsulate that object
// Create EIO types for the OC
// Create a dummy object for the ComponentAdaptationManager

class SimpleThing(f: Double => Double) {
  def doThing(d: Double): Double = f(d)
}

class SimpleThingEnvironment extends PrincessFeatureCollection(List.empty)
class SimpleThingInput(val d: Double) extends PrincessFeatureCollection(List[PrincessFeature](d))
trait SimpleThingComponent extends OptimizableComponent[SimpleThingEnvironment, SimpleThingInput, Double] with Serializable {}
class SimpleThingIntent extends Intent(0, "empty intent", List.empty, List.empty) {}
class SimpleThingComponentImpl(thing: SimpleThing) extends SimpleThingComponent {
  private val _intent = new SimpleThingIntent
  override def intent(): Intent = _intent
  override def component(e: SimpleThingEnvironment, i: SimpleThingInput, c: ComponentControls): Double = {
    updateControls(c)
    runComponent(e, i)
  }
  override def runComponent(e: SimpleThingEnvironment, i: SimpleThingInput): Double = thing.doThing(i.d)
  override def updateControls(c: ComponentControls): Unit = {}
  override def metricCalculator(e: SimpleThingEnvironment, i: SimpleThingInput, o: Double): ComponentMetrics = List(0.0)
}
class SimpleThingOptimizer extends ComponentOptimizer[SimpleThingEnvironment, SimpleThingInput] {
  override def apply(v1: SimpleThingEnvironment, v2: SimpleThingInput): ComponentControls = Map.empty
}

class DummyComponentAdaptationManager[Env <: PrincessFeature, Input <: PrincessFeature, Output]
  (val c: OptimizableComponent[Env, Input, Output],
   optimizer: ComponentOptimizer[Env, Input]) extends ComponentAdaptationManager[Env, Input, Output](c, optimizer) {

  private var _invoked = false
  def invoked = _invoked

  override def handleComponentIO(env: Env, in: Input, out: Output): Unit = {
    _invoked = true
    super.handleComponentIO(env, in, out)
  }

}
