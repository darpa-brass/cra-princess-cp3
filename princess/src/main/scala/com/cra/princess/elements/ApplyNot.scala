package com.cra.princess.elements

import com.cra.figaro.language._

/**
  * Shortcut for negating a boolean element.
  * Facilitates clean printing/display of Figaro models which use a lot of these.
  */
class ApplyNot(elt:Element[Boolean], name:Name[Boolean], elementCollection:ElementCollection)
  extends Apply1[Boolean, Boolean](name, elt, (v:Boolean) => !v, elementCollection) {
  override def toString = "Not(" + elt  + ")"
}

object ApplyNot {
  def apply(e: Element[Boolean])(implicit name:Name[Boolean], elementCollection: ElementCollection) = e match {
    case c:Constant[Boolean] => Constant(!c.constant)
    case _ => new ApplyNot(e, name, elementCollection)
  }
}
