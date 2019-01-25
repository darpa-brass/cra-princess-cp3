package com.cra.princess.testharness.example
import com.cra.princess.testharness.component_interface.ComponentInterface

import scala.collection.JavaConverters._

class ClusterComponent(numClusters: Int, initMethod: Int, maxIters: Int, range: Double, scale: Double, seed: Int = 13) extends ComponentInterface {

  // constructor
  def this(numClusters: java.lang.Integer, initMethod: java.lang.Integer, maxIters: java.lang.Integer, range: Double, scale: Double, seed: Int) = {
    this(numClusters.toInt, initMethod.toInt, maxIters.toInt, range, scale, seed)
  }  
  private val random = new scala.util.Random(seed)
  
  // internal data members
  private var testDataGenerator: TestDataGenerator = new TestDataGenerator(range, scale, seed)
  private var dim: Integer = new Integer(2)
  private var dataGenerated: Boolean = false
  private var generatedData: List[Array[Double]] = null
  private var generatedTruthValues: List[Int] = null
  
  // constants - bounds for randomly generated control variables
  private val MAX_CLUSTERS = 10
  private val MAX_INITMETHOD = 3
  private val MAX_MAXITERS = 1000
  
  // control variables - initially assign defaults from instantiation
  var numClustersCtrl: Int = numClusters
  var initMethodCtrl: Int = initMethod
  var maxItersCtrl: Int = maxIters
  
  def execute(inputData: java.util.List[Object]): java.util.List[Object] = {
    var clusterData: ClusterData = new ClusterData(numClustersCtrl, initMethodCtrl, maxItersCtrl)
    val retData =  clusterData.cluster(inputData.asInstanceOf[java.util.ArrayList[Array[java.lang.Double]]], dim)
    new java.util.ArrayList(retData)
  }
  
  def calculateMetrics(outputValues: java.util.List[Object], truthValues: java.util.List[Object]): java.util.List[Object] = {
    val assigns = outputValues.asScala.map(i => i.asInstanceOf[Integer].intValue()).toList.zipWithIndex
    val clusters = assigns.groupBy(f => f._1).mapValues(f => f.unzip._2) 
    val sTruthValues = truthValues.asScala.toList.map(_.asInstanceOf[Integer].intValue())
    val retval = ClusterPurity.metric(clusters, sTruthValues)
    new java.util.ArrayList[Object](List(retval.asInstanceOf[Object]).asJava)
  }
  
  def generateDataSet(genericProperties: java.util.List[Object]): java.util.List[Object] = { 
    val (data, truthValues) = testDataGenerator.generate(numClusters, dim, genericProperties.get(0).asInstanceOf[Int], true)
    this.generatedData = data
    this.generatedTruthValues = truthValues
    this.dataGenerated = true
    val inputData = generatedData.map(_.map(new java.lang.Double(_)))
    new java.util.ArrayList(inputData.asJava)
  }
  
  def generateTruthValues(): java.util.List[Object] = {
    if (dataGenerated) {
      val retval = generatedTruthValues.map(f => new java.lang.Integer(f))
      new java.util.ArrayList(retval.asJava)
    } else {
      null
    }
  }
  
  def generateControlVars(): java.util.List[Object] = {
    //this.numClustersCtrl = random.nextInt(MAX_CLUSTERS+1)
    this.initMethodCtrl = random.nextInt(MAX_INITMETHOD+1)
    this.maxItersCtrl = random.nextInt(MAX_MAXITERS+1)
    var retval = new java.util.ArrayList[Object]()
    retval.add(new java.lang.Integer(this.numClustersCtrl))
    retval.add(new java.lang.Integer(this.initMethodCtrl))
    retval.add(new java.lang.Integer(this.maxItersCtrl))
    retval
  }
  
  def setControlVars(controlValues: java.util.List[Object]) = {
     this.numClustersCtrl = controlValues.get(0).asInstanceOf[Integer].intValue()
     this.initMethodCtrl = controlValues.get(1).asInstanceOf[Integer].intValue()
     this.maxItersCtrl = controlValues.get(2).asInstanceOf[Integer].intValue()
  }
 
}