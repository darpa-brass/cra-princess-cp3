package com.cra.princess.componentmodel

import com.cra.figaro.language._
import com.cra.figaro.library.compound._
import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.princess._
import com.cra.princess.core._
import org.scalatest.{FlatSpec, Matchers}

class SimpleComponentDataGeneratorTest extends FlatSpec with Matchers {

  "A SimpleComponentDataGenerator" should "generate values within the support of the supplied distributions" in {
    
    val inputModel = (^^(new UniformScalarPrincessElement(0, 1, "", Universe.universe),
      new UniformScalarPrincessElement(1, 2, "", Universe.universe))).asInstanceOf[InputModel[ScalarPrincessFeature, ScalarPrincessFeature]]
    val controls = List(new BoundedScalarPrincessFeature(2.5, 2, 3), new BoundedScalarPrincessFeature(3.0, 3, 4))
    val controlGenerator = BasicControlGenerator(Map("A" -> controls(0), "B" -> controls(1)))
    
    val component = new OptimizableComponent[ScalarPrincessFeature, ScalarPrincessFeature, Double]() {
      override def intent():Intent = null
      def component(e: ScalarPrincessFeature, i: ScalarPrincessFeature, c: ComponentControls): Double = {
        e.value + i.value + c.values.map( d => d.asInstanceOf[BoundedScalarPrincessFeature].value).sum
      }
      def metricCalculator(e: ScalarPrincessFeature, i: ScalarPrincessFeature, o: Double): ComponentMetrics = {
        List(e.value, i.value, o)
      }
      def runComponent(e: ScalarPrincessFeature, i: ScalarPrincessFeature) : Double = ???
      def updateControls(c: ComponentControls): Unit = ???
    }
    
    // mock code analyzer just does some arithmetic on the environments, inputs, and controls
    val codeAnalyzer = new ComponentCodeAnalyzer[ScalarPrincessFeature, ScalarPrincessFeature] {
      def analyze(componentData:List[(ScalarPrincessFeature, ScalarPrincessFeature, ComponentControls)]):List[PrincessFeature] = {
        componentData.map(c => new ScalarPrincessFeature(c._1.value - c._2.value + c._3.values.map(v => v.asInstanceOf[BoundedScalarPrincessFeature].value).sum)).toList
      }
    }
    
    val dataGenerator = new SimpleComponentDataGenerator[ScalarPrincessFeature, ScalarPrincessFeature, Double](1000)
    val componentData = dataGenerator.generate(inputModel, controlGenerator, component)
    
    var distinctEnvVals = Set[Double]()
    var distinctInputVals = Set[Double]()
    var distinctControl1Vals = Set[Double]()
    var distinctControl2Vals = Set[Double]()
    componentData.foreach(d => {
      var controlSum = d.componentInput.controls.values.map(v => v.asInstanceOf[BoundedScalarPrincessFeature].value).sum
      
      // metric should be environment, input, output tuples
      // output should be linear combination of inputs and controls
      d.metrics should equal(List(d.componentInput.env.value, d.componentInput.input.value, 
          d.componentInput.env.value.value + d.componentInput.input.value.value + controlSum))
      
      distinctEnvVals += d.componentInput.env.value
      distinctInputVals += d.componentInput.input.value
      distinctControl1Vals += d.componentInput.controls("A").asInstanceOf[BoundedScalarPrincessFeature].value
      distinctControl2Vals += d.componentInput.controls("B").asInstanceOf[BoundedScalarPrincessFeature].value
    
      d.componentInput.env.value should be(0.5 +- 0.5)
      d.componentInput.input.value should be(1.5 +- 0.5)
      d.componentInput.controls.size should equal(2)
      d.componentInput.controls("A").asInstanceOf[BoundedScalarPrincessFeature].value should be(2.5 +- 0.5)
      d.componentInput.controls("B").asInstanceOf[BoundedScalarPrincessFeature].value should be(3.5 +- 0.5)
    })
    
    // with minute probability, some of the elements will be the same
    distinctEnvVals.size should be > 990
    distinctInputVals.size should be > 990
    distinctControl1Vals.size should be > 990
    distinctControl2Vals.size should be > 990
  }
}
