package com.cra.princess.test.testharness.example

import com.cra.princess.testharness.example.ClusterData
import com.cra.princess.testharness.example.TestDataGenerator

object ExampleTest {

  val range: Double = 100
  val scale: Double = 0.4
    
  val numClusters = 5
  val dim = 2
  val numData = 100
  
  def main(args: Array[String]) {
      
    val generator = new TestDataGenerator(range, scale)
    val (data, truth) = generator.generate(numClusters, dim, numData, true)
    
    val start = System.currentTimeMillis()
    val clusterer = new ClusterData(numClusters, 0, Int.MaxValue )  
    val assigns = (clusterer.cluster(data, dim)).zipWithIndex
    val clusters = assigns.groupBy(f => f._1).mapValues(f => f.unzip._2) 
      
    val purity = ClusterPurity.metric(clusters, truth)
    println("Purity: " + purity)
    println("Time: " + (System.currentTimeMillis()-start))
    
  }
  
}