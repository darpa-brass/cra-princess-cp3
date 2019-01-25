package com.cra.princess.util

import com.cra.figaro.language.Element
import com.cra.princess.elements.ApplyNot

import scalax.collection.Graph
import scalax.collection.GraphEdge._
import scalax.collection.GraphPredef._
import scalax.collection.edge.LDiEdge

case class LabeledElement(element:Element[Any], label:String)

/**
  * Constructs a graph of Figaro elements.
  * Will not work for all elements.
  */
object FigaroElementGraphBuilder {

  def apply(elt:Element[Any]):scalax.collection.mutable.Graph[LabeledElement, LDiEdge] = {

    val graph = scalax.collection.mutable.Graph[LabeledElement, LDiEdge]()

    def buildNode(elt:Element[_]):LabeledElement= {
      val (repr, args) = elt match {
        case a: com.cra.figaro.language.Atomic[_] => (elt.toString, Map.empty[String, Element[Any]])
        case a: com.cra.figaro.library.compound.If[_] =>
          ("If", Map("condition" -> a.parent, "then" -> a.thn, "else" -> a.els))
        case a: ApplyNot =>
          ("Not", Map("" -> a.arg1))
        case a: com.cra.figaro.language.Apply1[_, _] =>
          ("Apply1(" + a.fn + ")", Map("arg1" -> a.arg1))
        case a: com.cra.figaro.language.Apply2[_, _, _] =>
          ("Apply2(" + a.fn + ")", Map("arg1" -> a.arg1, "arg2" -> a.arg2))
        case a: com.cra.figaro.language.Apply3[_, _, _, _] =>
          ("Apply3(" + a.fn + ")", Map("arg1" -> a.arg1, "arg2" -> a.arg2, "arg3" -> a.arg3))
        case a: com.cra.figaro.language.Apply4[_, _, _, _, _] =>
          ("Apply4(" + a.fn + ")", Map("arg1" -> a.arg1, "arg2" -> a.arg2, "arg3" -> a.arg3, "arg4" -> a.arg4))
        case _ => (elt.toString, elt.args.zipWithIndex.map(ei => ("arg" + (ei._2 + 1), ei._1.asInstanceOf[Element[Any]])).toMap)
      }

      val labeledArgs = args.transform((k, v) => {
        buildNode(v.asInstanceOf[Element[Any]])
      })
      val labeledElt = LabeledElement(elt.asInstanceOf[Element[Any]], repr)
      val newEdges = args.keys.map(a => LDiEdge(labeledArgs(a), labeledElt)(a))
      graph ++= newEdges
      labeledElt
    }

    buildNode(elt)
    graph
  }
}
