package com.cra.princess.util

import java.io.{File, PrintWriter}

import com.ibm.wala.util.graph.NumberedGraph
import com.ibm.wala.util.intset.IntSetAction

import scala.collection.JavaConverters._
import scalax.collection.edge.LDiEdge

/**
  * Generates DOT files from a Wala graphs
  */
class GraphWriter {

  /** Performs a depth-first traversal of the graph starting at the root.
    * This has the advantage of ignoring ancestors of 'root', if present.*/
  private def performDfs[T](graph:NumberedGraph[T], root:T, nodeAction:T => Unit, edgeAction:(T, T) => Unit) = {
    // depth-first traversal of the graph
    val visited = scala.collection.mutable.Set[T]()
    val frontier = scala.collection.mutable.Stack[T](root)
    while(!frontier.isEmpty) {
      val next = frontier.pop()
      nodeAction(next)
      visited += next
      val successors = graph.getSuccNodes(next).asScala.toList

      successors.foreach(succ => {
        if (!visited.contains(succ) && !frontier.contains(succ)) {
          frontier.push(succ)
        }
        edgeAction(next, succ)
      })
    }
  }

  private val graphMLHeader = """<?xml version="1.0" encoding="UTF-8" standalone="no"?>
      |<graphml
      |xmlns="http://graphml.graphdrawing.org/xmlns"
      |xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      |xmlns:y="http://www.yworks.com/xml/graphml"
      |xmlns:yed="http://www.yworks.com/xml/yed/3"
      |xsi:schemaLocation="http://graphml.graphdrawing.org/xmlns http://www.yworks.com/xml/schema/graphml/1.1/ygraphml.xsd">
      |<key for="node" id="d1" yfiles.type="nodegraphics"/>
      |<key for="edge" id="d2" yfiles.type="edgegraphics"/>
      |<graph edgedefault="directed" id="G">""".stripMargin

  /** A specialization intended primarily for Figaro element graphs */
  def writeGraphML[T](graph:scalax.collection.Graph[LabeledElement, LDiEdge], fileName:String) = {
    // TODO better would be to use JAXB
    val writer = new PrintWriter(new File(fileName))
    try {
      writer.write(graphMLHeader)

      val nodeIds = graph.nodes.toOuter.zipWithIndex.toMap
      graph.nodes.toOuter.foreach(n => {
        writer.write("<node id=\"" + nodeIds(n) + "\">\n")
        writer.write("""<data key="d1"><y:ShapeNode>""" + "\n")
        writer.write("<y:NodeLabel><![CDATA[" + n.label + "]]></y:NodeLabel>\n")
        writer.write("""</y:ShapeNode></data>""" + "\n")
        writer.write("</node>")
      })

      graph.edges.toOuter.foreach(e => {
        writer.write("<edge source=\"" + nodeIds(e.nodeSeq(0)) + "\" target=\"" + nodeIds(e.nodeSeq(1)) + "\">\n")
        writer.write("""<data key="d2"><y:PolyLineEdge>""" + "\n")
        writer.write("<y:EdgeLabel modelName=\"centered\" modelPosition=\"center\" preferredPlacement=\"center\">" + e.label + "</y:EdgeLabel>\n")
        writer.write("""<y:Arrows source="none" target="standard"/>""")
        writer.write("</y:PolyLineEdge></data>\n")
        writer.write("</edge>\n")
      })

      writer.write(
        """</graph>
          |</graphml>
        """.stripMargin)
    } finally {
      writer.close
    }
  }

  def writeGraphML[T](graph:NumberedGraph[T], fileName:String, root:T, nameFun: T => String) = {
    // TODO better would be to use JAXB
    val writer = new PrintWriter(new File(fileName))
    try {
      writer.write(graphMLHeader)

      performDfs(graph, root, (node:T) => {
        val nodeNum = graph.getNumber(node)
        val label = nameFun(node)
        writer.write("<node id=\"" + nodeNum + "\">\n")
        writer.write("""<data key="d1"><y:ShapeNode>""" + "\n")
        writer.write("<y:NodeLabel><![CDATA[" + label + "]]></y:NodeLabel>\n")
        writer.write("""</y:ShapeNode></data>""" + "\n")
        writer.write("</node>")
      }, (from:T, to:T) => {
        val fromId = graph.getNumber(from)
        val toId = graph.getNumber(to)
        writer.write("<edge source=\"" + fromId + "\" target=\"" + toId + "\"/>")
      })

      writer.write(
        """</graph>
           |</graphml>
        """.stripMargin)
    } finally {
      writer.close
    }
  }

  /** Writes a graph to a comma-separated edge list file */
  def writeEdgeList[T](graph:NumberedGraph[T], fileName:String, root:T, nameFun: T => String) = {
    val writer = new PrintWriter(new File(fileName))
    try {
      writer.write("from,to\n")
      performDfs(graph, root, (node:T) => (), (from:T, to:T) => {
          val fromName = nameFun(from)
          val toName = nameFun(to)
          writer.write("\"" + fromName + "\",\"" + toName + "\"\n")
        })
    } finally {
      writer.close
    }
  }

  /** Writes a graph to a DOT file */
  def writeDot[T](graph:NumberedGraph[T], fileName:String, root:T, nameFun: T => String = null) = {
    val writer = new PrintWriter(new File(fileName))
    try {
      writer.write("digraph {\n")
      performDfs(graph, root, (node:T) => {
        val number = graph.getNumber(node)
        val label = nameFun(node)
        writer.write(number + " [label=\"" + label + "\"];\n")
      }, (from:T, to:T) => {
          val fromNumber = graph.getNumber(from)
          val toNumber = graph.getNumber(to)
          writer.write(fromNumber + " -> " + toNumber + ";\n")
        }
      )
      writer.write("}\n")
    } finally {
      writer.close
    }
  }
}
