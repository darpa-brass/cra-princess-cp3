package com.cra.princess.test.testharness.example
import com.cra.princess.testharness.example.ClusterComponent
import com.cra.princess.testharness.component_interface.ComponentInterface
import scala.collection.JavaConverters._
import org.scalatest.FunSuite

class ClusterComponentTestDriver extends FunSuite {
  
  test("ClusterComponent test driver using ComponentInterface should execute without errors") {  
    // values required for component initialization (passed to constructor)
    val numClusters: Int = 10
    val initMethod: Int = 0
    val maxIters: Int = 100
    val range: Double = 100.0
    val scale: Double = 1.0
    val seed: Int = 13
    val numDataPoints: Integer = new Integer(100)
    
    // Run twice with different control variables, holding input data and truth values constant 
    val  clusterer: ComponentInterface = new ClusterComponent(numClusters, initMethod, maxIters, range, scale, seed) 
 
    // First object in genericProperties list is an Integer specifying the number of data points to generate
    var genericProperties = new java.util.ArrayList[Integer]()
    genericProperties.add(numDataPoints)
    val dataSet = clusterer.generateDataSet(genericProperties.asInstanceOf[java.util.List[Object]])
    val truthValues: java.util.List[Object] = clusterer.generateTruthValues()
    
    // First run    
    val controlVars1: java.util.List[Object] = clusterer.generateControlVars()
    clusterer.setControlVars(controlVars1)    
    val outputValues1: java.util.List[Object] = clusterer.execute(dataSet)
    
    // Second run
    val controlVars2: java.util.List[Object] = clusterer.generateControlVars()
    clusterer.setControlVars(controlVars2)    
    val outputValues2: java.util.List[Object] = clusterer.execute(dataSet)

    // Calculate and output metrics for each run
    val metrics1: java.util.List[Object] = clusterer.calculateMetrics(outputValues1, truthValues)
    val metrics2: java.util.List[Object] = clusterer.calculateMetrics(outputValues2, truthValues)
    
    // Output to console
    println("Data set: ")
    for (x <- dataSet.asScala) {
      print("(")
      x match {
        case arr: Array[java.lang.Double] =>
          for(y <- arr.toList) {
            print(y + ",")
          }
        case _ =>
      }
      print(") ; ")
    }
    print("\n")
    println("Truth values: " + truthValues)
    println("Control vars 1: " + controlVars1) 
    println("Purity 1: " + metrics1)
    println("Control vars 2: " + controlVars2)
    println("Purity 2: " + metrics2)
  }
}