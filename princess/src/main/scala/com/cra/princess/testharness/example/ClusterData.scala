package com.cra.princess.testharness.example

import weka.clusterers.SimpleKMeans
import weka.core.{Attribute, DenseInstance, Instances}

import scala.collection.JavaConverters._


class ClusterData(numClusters: Int, initMethod: Int, maxIters: Int) {
  def this(numClusters: java.lang.Integer, initMethod: java.lang.Integer, maxIters: java.lang.Integer) = {
    this(numClusters.toInt, initMethod.toInt, maxIters.toInt)
  }
    
  def createInstances(length: Int, dim: Int): Instances = {
    val attInfo = new java.util.ArrayList(List.tabulate(dim)(d => new Attribute(d.toString)).asJava)
    new Instances("data", attInfo, length)
  }
  
  def addInstance(data: Instances, datum: Array[Double], dim: Int) = {
    val inst = new DenseInstance(dim);
    for(i <- 0 until dim){
      inst.setValue(i, datum(i))
    }
    inst.setDataset(data)
    data.add(inst)
  }
  
  
  def cluster(data: java.util.ArrayList[Array[java.lang.Double]], dim: java.lang.Integer): java.util.List[java.lang.Integer] = {
    val sData = data.asScala.toList.map(_.map(_.toDouble))
    val a = cluster(sData, dim.toInt)
    a.map(i => i:java.lang.Integer).asJava
  }
  
  // Returns total squared error for clusters
  def cluster(data: List[Array[Double]], dim: Int): List[Int] = {
    val dataInstances = createInstances(data.length, dim)
    data.foreach(addInstance(dataInstances, _, dim))
    
    val kmeans = new SimpleKMeans()
    val options = Array(
      "-N", numClusters.toString,
      "-init", initMethod.toString,
      "-I", maxIters.toString,
      "-O"
    )
    kmeans.setOptions(options)
    kmeans.buildClusterer(dataInstances)
    List(kmeans.getAssignments():_*)
  }
  

}