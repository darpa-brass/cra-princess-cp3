package com.cra.princess.util

import scala.reflect.ClassTag

object Recognizer {

  def recognize[T](x: Any)(implicit tag: ClassTag[T]): Boolean = {
    x match {
      case _: T => true
      case _ => false
    }
  }

  def recognizeSeq[T](seq: Seq[Any])(implicit tag: ClassTag[T]): Boolean = {
    val results = seq.map(x => recognize[T](x))
    results.forall(b => b)
  }
}