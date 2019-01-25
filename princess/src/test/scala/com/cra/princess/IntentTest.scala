package com.cra.princess

import com.cra.princess.core._
import org.scalatest.Matchers
import org.scalatest.WordSpec

class IntentTest extends WordSpec with Matchers {

  "Intent defined with two metrics" should {

    // component where the metric is (env + input) * controls
    val component = new OptimizableComponent[ScalarPrincessFeature, ScalarPrincessFeature, Double] {
      override def intent(): Intent = {
        val intentMetrics = List(Double.MinPositiveValue, -Double.MinPositiveValue)
        val thresholds = List(ThresholdData("var1", Double.MinPositiveValue, LessThan()),
          ThresholdData("var2", -Double.MinPositiveValue, GreaterThan()))
        Intent(0, "should be exactly zero", List.empty[Intent], thresholds)
      }

      override def component(e: ScalarPrincessFeature, i: ScalarPrincessFeature, c: ComponentControls): Double = {
        (e.value + i.value) * c("A").asInstanceOf[ScalarPrincessFeature].value
      }

      override def metricCalculator(e: ScalarPrincessFeature, i: ScalarPrincessFeature, o: Double): ComponentMetrics = {
        List(o)
      }
      def runComponent(e: ScalarPrincessFeature, i: ScalarPrincessFeature) : Double = ???
      def updateControls(c: ComponentControls): Unit = ???
    }

    "satisfy intent for a simple component with good controls" in {
      component.satisfiesIntent(new ScalarPrincessFeature(1), new ScalarPrincessFeature(1),
        Map("A" -> new BoundedScalarPrincessFeature(1, 0, 1)))
    }

    "fail to satisfy intent for a simple component with bad controls" in {
      component.satisfiesIntent(new ScalarPrincessFeature(1), new ScalarPrincessFeature(1),
        Map("A" -> new BoundedScalarPrincessFeature(0, 0, 1)))
    }

    "evaluate square root" in {
      val sqrtIntent = Intent.apply(0, "must be square root", List.empty[Intent], List(ThresholdData("val", 0.001, LessThan())))
      val currentMetrics = List[Metric](Math.abs(9.1 - 9));
      sqrtIntent.evaluateIntentState(currentMetrics)
    }
  }
  
  
}
