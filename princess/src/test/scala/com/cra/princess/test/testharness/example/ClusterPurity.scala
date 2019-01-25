package com.cra.princess.test.testharness.example

object ClusterPurity {
   def findMode(l: List[Int]) = {
    val groups = l.groupBy(s => s)
    val max = groups.maxBy(_._2.size)
    max._1
  }
  
  def metric(clusters: Map[Int, List[Int]], truth: List[Int]): Double = {
    val purity = clusters.map{c =>
      val members = c._2.map(truth(_))
      val mode = findMode(members)
      members.count(_ == mode)
    }
    purity.sum.toDouble/truth.size.toDouble
  }
}