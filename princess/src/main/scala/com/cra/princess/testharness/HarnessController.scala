package com.cra.princess.testharness

import com.cra.princess.testharness.example.TestDataGenerator
import com.cra.princess.testharness.example.ClusterPurity
import com.cra.princess.testharness.example.ClusterData
import com.cra.princess.testharness.example.ClusterModel
import com.cra.figaro.algorithm.sampling.Importance
import com.cra.figaro.algorithm.sampling.MetropolisHastings
import com.cra.figaro.algorithm.sampling.ProposalScheme

object HarnessController {

  val numClustersSupport = (2, 10)
  val initMethodSupport = (0, 1)
  val maxItersSupport = (20, 25)

  def main(args: Array[String]): Unit = {

    /*
     * Generate random data
     * We might want an interface/api for this
     * This is basically just generating a whole bunch of  data by randomly selecting parameters to the data generation class
     */
    val allData = for { _ <- 0 until 20 } yield {
      val range = scala.util.Random.nextInt(50) + 50
      val scale = scala.util.Random.nextDouble
      val numClusters = scala.util.Random.nextInt(10) + 10
      val dim = scala.util.Random.nextInt(20) + 20
      val numData = 1000

      val generator = new TestDataGenerator(range, scale)
      val (data, truth) = generator.generate(numClusters, dim, numData, true)
      // Each piece of data is a set of points to cluster, the truth for those points, and the dimension of the data
      (data, truth, dim)
    }

    /*
     * Generate values of the control variables, and the metrics associated with those values
     * For this, randomly select a value of the control variables, and run all the data through
     * the clustering class, and capture the metrics
     * At the end, we should have a bunch of (control, metrics) tuples
     */
    val controlAndMetrics = (for { _ <- 0 to 20 } yield {
      // Randomly generate some control variable values
      val numClusters = scala.util.Random.nextInt(numClustersSupport._2 - numClustersSupport._1) + numClustersSupport._1
      val initMethod = scala.util.Random.nextInt(initMethodSupport._2 - initMethodSupport._1) + initMethodSupport._1
      val maxIters = scala.util.Random.nextInt(maxItersSupport._2 - maxItersSupport._1) + maxItersSupport._1
      val results = allData.map { d =>

        val start = System.currentTimeMillis()
        val clusterer = new ClusterData(numClusters, 0, Int.MaxValue)
        val assigns = (clusterer.cluster(d._1, d._3)).zipWithIndex
        val clusters = assigns.groupBy(f => f._1).mapValues(f => f.unzip._2)

        val purity = ClusterPurity.metric(clusters, d._2)
        val time = (System.currentTimeMillis() - start).toDouble/1000.0
        (purity, time)
      }
      (numClusters, initMethod, maxIters) -> results.toList
    }).toMap
    
    /*
     * Build the learning model. 
     */
    val model = new ClusterModel(numClustersSupport, initMethodSupport, maxItersSupport)
    val (universe, mapping) = model.makeLearningModel(controlAndMetrics)
    
    /*
     * Run a learning algorithm on the model. In this case, we will run Bayesian learning so we'll just 
     * run a sampling algorithm and pass that algorithm to the cluster model. 
     */
    val is = Importance(10000, (mapping.values.unzip._1 ++ mapping.values.unzip._2).toSeq:_*)(universe)
    //val is = MetropolisHastings(100000, ProposalScheme.default, (mapping.values.unzip._1 ++ mapping.values.unzip._2).toSeq:_*)(universe)
    is.start
    
    /*
     * Produce a new model that represents the learned model from the data
     */
    val newModel = model.makePosteriorModel(is)
    
    val purity = newModel.getElementByReference[Double]("purity")
    val runtime = newModel.getElementByReference[Double]("runtime")

    println(purity)
    println(runtime)
    
  }

}