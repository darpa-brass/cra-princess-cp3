package com.cra.princess.componentmodel.codeanalysis

import java.io._

import com.cra.princess.util.Recognizer
import play.api.libs.json._
import spoon.Launcher
import spoon.reflect.CtModel
import spoon.reflect.code._
import spoon.reflect.cu.CompilationUnit
import spoon.reflect.declaration._
import spoon.reflect.factory.Factory
import spoon.reflect.reference.CtTypeReference
import spoon.reflect.visitor.filter.TypeFilter
import spoon.support.reflect.code._
import spoon.support.reflect.reference.CtLocalVariableReferenceImpl

import scala.collection.JavaConverters._
import scala.language.existentials


// TODO: Currently limited to static and public method
//     - convert private method to public?
// TODO: figure out how to find literals (non-trivial) in set
//     - features for literal? exclusion conditions?
//     - NN to learn correct literals ?
// replace every literal in set with a new formal argument
object ProgramTransformer{

  type MethodType = CtMethod[Any]
  type AssignmentType = CtAssignment[Any, Any]
  type VarAccess = CtVariableAccessImpl[Any]
  type LocalVar = CtLocalVariable[Any]
  type Constant = CtLiteralImpl[_]
  type Field = CtField[Any]
  type FieldWrite = CtFieldWrite[Any]
  type BooleanExp = CtBinaryOperator[java.lang.Boolean]
  val assignmentFilter = new TypeFilter[AssignmentType](classOf[AssignmentType])
  val constantFilter = new TypeFilter[Constant](classOf[Constant])
  val fieldFilter = new TypeFilter[CtField[Any]](classOf[CtField[Any]])
  val fieldWriteFilter = new TypeFilter[CtFieldWrite[Any]](classOf[CtFieldWrite[Any]])
  val ifFilter =  new TypeFilter[CtIf](classOf[CtIf])
  val localVarFilter = new TypeFilter[LocalVar](classOf[LocalVar])
  val loopFilter =  new TypeFilter[CtFor](classOf[CtLoop])
  val anyFilter = new TypeFilter[CtElement](classOf[CtElement])
  val classFilter = new TypeFilter[CtClass[Any]](classOf[CtClass[Any]])
  val methodFilter = new TypeFilter[MethodType](classOf[MethodType])

  private var constNum, loopNum, ifNum, varId = 0
  private var linesSearched = Set.empty[(String, Int)]

  def main(args: Array[String]): Unit = {
    constNum = 0
    loopNum = 0
    ifNum = 0
    varId = 0
    linesSearched = Set.empty[(String, Int)]
    
    val flag = args(0)
    if(flag == "-s") {
      val inputPath = args(1)
      val saveFile = args(2)
      saveTransformationCandidates(inputPath, saveFile)
    }
    else if(flag == "--t-s"){
      val inputPath = args(1)
      val outputPath = args(2)
      val saveFile = args(3)
      transformClass(inputPath, outputPath, Some(saveFile))
    }
    else if(flag == "-t"){
      val inputPath = args(1)
      val outputPath = args(2)
      transformClass(inputPath, outputPath, None)
    }
    else
      println("usage: \n" +
        "-s    [input java program] [path to candidates file]\n" +
        "-t    [input java program] [path to transformed program]\n" +
        "--t-s [input java program] [path to transformed program] [path to candidates file]\n")
  }

  def saveTransformationCandidates(inputPath: String, saveFile: String): Unit = {
    val (model, cu) = loadClassAST(inputPath)
    val (methods, fieldAssignments, lines) = loadTransformableStructures(model, cu)
    val transformCandidates = methods.indices.flatMap{ i =>
      val method = methods(i)
      val includedFields = if(i == 0) fieldAssignments else Seq()
      findPossibleTransformations(method, includedFields, lines)
    }
    val transformableVariables = transformCandidates.map{ case (c, expType, line, id, _) =>
      val parent = c.getParent
      Json.obj(
        "varName" -> s"var$id",
        "value" -> c.toString,
        "type" -> c.getType.toString,
        "parentCode" ->  parent.toString,
        "expressionType" -> expType,
        "line" -> line,
        "selected" -> false)
    }
    val data = Json.obj("transformableVariables" -> transformableVariables, "rawCode" -> lines)
    val pw = new PrintWriter(saveFile)
    pw.print(Json.prettyPrint(data))
    pw.close()
  }

  def transformClass(inputPath: String, outputPath: String, candidateFile: Option[String]): Unit = {
    val selectedCandidates = candidateFile match {
      case Some(file) => Some(loadTransformationCandidates(file))
      case None => None
    }
    val (model, cu) = loadClassAST(inputPath)
    val (methods, fieldAssignments, lines) = loadTransformableStructures(model, cu)
    methods.indices.foreach{ i =>
      val m = methods(i)
      val includedFields = if(i == 0) fieldAssignments else Seq()
      val candidatesForMethod = findPossibleTransformations(m, includedFields, lines).filter{ x =>
        println(x._4, selectedCandidates)
        selectedCandidates.isEmpty || selectedCandidates.get.contains(s"var${x._4}")
      }
      transformMethod(m, Set(), includedFields, candidatesForMethod)
    }

    val pw = new PrintWriter(new File(outputPath))
    val mainClass = model.getElements(new TypeFilter[CtClass[Any]](classOf[CtClass[Any]])).asScala.toList.head
    pw.println(s"package ${mainClass.getPackage};\n")
    cu.getImports.asScala.toList.foreach(lib => pw.println(s"import $lib;"))
    pw.println()
    pw.println(model.getAllTypes.asScala.head)
    pw.close()
  }

  private def loadTransformationCandidates(saveFile: String): Seq[String] ={
    val source: String = io.Source.fromFile(saveFile).getLines.mkString
    val json = Json.parse(source).as[JsObject]
    val arr = json.value("transformableVariables").as[JsArray]
    arr.value.map{ x =>
      val obj = x.as[JsObject]
      (obj("varName").as[JsString].value, obj("selected").as[JsBoolean].value)
    }.filter(_._2).map(_._1)
  }

  private def loadClassAST(inputPath: String): (CtModel, CompilationUnit) = {
    val launcher = new Launcher
    launcher.addInputResource(inputPath)
    launcher.getEnvironment.setAutoImports(true)
    launcher.getEnvironment.setNoClasspath(true)
    launcher.buildModel()
    val model: CtModel = launcher.getModel
    val cu: CompilationUnit = launcher.getFactory.CompilationUnit
      .create(model.getAllTypes.asScala.head.getPosition.getFile.getAbsolutePath)
    (model, cu)
  }

  private def loadTransformableStructures(model: CtModel, cu: CompilationUnit):
  (Seq[MethodType], Seq[CtFieldWrite[Any]], List[String]) = {
    val methodElements: Seq[MethodType] = model.getElements(methodFilter).asScala
    val mainClass = model.getElements(new TypeFilter[CtClass[Any]](classOf[CtClass[Any]])).asScala.toList.head

    val methods: Seq[MethodType] = methodElements.filter { method =>
      val modifiers = method.getModifiers.asScala.toList.map(_.toString)
      val name = method.getSimpleName
      modifiers.contains("public") && // only transforming public methods
      !name.toLowerCase.contains("transformed") // only transforming methods not previously transformed
    }
    val fieldAssignments: Seq[CtFieldWrite[Any]] = model.getElements(fieldWriteFilter).asScala.toList
    val lines = List(s"package ${mainClass.getPackage};") ++ List("") ++
      cu.getImports.asScala.toList.map(lib => s"import $lib;") ++ List("") ++
      model.getAllTypes.asScala.head.toString.split("\n").toList
    (methods, fieldAssignments, lines)
  }

  /**
    * Searches a method for possible expressions to transform
    * @param func - input method
    * @param fieldAssignments - Assignment statements for fields in the containing class
    * @param lines - Seq of strings representing raw code for input method
    * @return Sequence of tuple containing
    *         - Constant value
    *         - String representing expression type
    *         - Line in raw code where expression appears
    *         - Id of variable (auto-increment)
    *         - Expression object
    */
  private def findPossibleTransformations(func: MethodType, fieldAssignments: Seq[CtFieldWrite[Any]],
                                          lines: List[String]): Seq[(CtExpression[_], String, Int, Int, CtElement)] = {
    val localVars: Seq[LocalVar] = func.getBody.getElements(localVarFilter).asScala
    val assignments: Seq[AssignmentType] = func.getBody.getElements(assignmentFilter).asScala.toList
    val ifStatements: Seq[CtIf] = func.getBody.getElements(ifFilter).asScala.toList
    val loops: Seq[CtExpression[java.lang.Boolean]] = func.getBody.getElements(loopFilter).asScala.map(_.getExpression).toList
    (localVars ++ assignments ++ ifStatements ++ loops ++ fieldAssignments)
      .filter(shouldTransform(_,assignments, fieldAssignments)).flatMap{ exp: CtElement =>
      val expType =
        if(Recognizer.recognize[LocalVar](exp)) "LocalVar"
        else if(Recognizer.recognize[AssignmentType](exp)) "Assignment"
        else if(Recognizer.recognize[CtIf](exp)) "IfConditional"
        else if(Recognizer.recognize[BooleanExp](exp)) "LoopConditional"
        else if(Recognizer.recognize[CtFieldWrite[Any]](exp)) {
          // constructor method is always 3 parent calls away from the field assignment within said constructor
          if(Recognizer.recognize[CtConstructor[Any]](exp.getParent.getParent.getParent)) "FieldConstructorInit"
          else "FieldWrite"
        }
        else throw new IllegalArgumentException(s"class type was ${exp.getClass}")

      val checkedExp =
        if(Recognizer.recognize[CtFieldWrite[Any]](exp)) exp.getParent
        else if(Recognizer.recognize[CtIf](exp)) exp.asInstanceOf[CtIf].getCondition
        else exp

      val filteredLines: Seq[Int] = lines
        .filter(s => s.trim.contains(checkedExp.toString.trim))
        .flatMap{ str => lines.indices.filter{i => lines(i) == str}}.distinct.map(_ + 1)
        .filter{ line =>
        !linesSearched.exists{ case (s, l) => s == checkedExp.toString.trim && line == l}
      }

      if(filteredLines.nonEmpty)
        linesSearched = linesSearched ++ Set((checkedExp.toString.trim, filteredLines.min))

      val line = if(filteredLines.nonEmpty) filteredLines.min else -1
      val constants: Seq[(CtExpression[_], String, Int, Int, CtElement)] =
        checkedExp.getElements(constantFilter).asScala.map { x =>
          val constant = (x, expType, line, varId, exp)
          varId += 1
          constant
        }

      val addedVariables = exp match {
        case value: CtBinaryOperator[_] =>
          val addVars = List((value.getRightHandOperand, expType, line, varId, exp))
          varId += 1
          addVars
        case _ => List()
      }
      constants ++ addedVariables
    }
  }

  def transformMethod(functionToTransform: MethodType,
                      literals: Set[CtLiteral[Any]], fieldAssignments: Seq[CtFieldWrite[Any]],
                      transformCandidates: Seq[(CtExpression[_], String, Int, Int, CtElement)]): Unit = {
    val (fwCandidates, otherCandidates) = transformCandidates.partition(tc => Recognizer.recognize[FieldWrite](tc._5))
    fieldAssignments.foreach(transformFieldAssignments(functionToTransform, _, fwCandidates))
    otherCandidates.foreach{ case (_, expType, _, _, exp) =>
      expType match {
        case  "LocalVar" =>
          val v = exp.asInstanceOf[LocalVar]
          transformConstant(functionToTransform, v.getAssignment, v)
        case "Assignment" =>
          val v = exp.asInstanceOf[AssignmentType]
          transformConstant(functionToTransform, v.getAssignment, v)
        case "IfConditional" =>
          val ifStatement = exp.asInstanceOf[CtIf]
          transformIfExpressions(functionToTransform, ifStatement, ifNum)
          ifNum += 1
        case "LoopConditional" =>
          val loopEnd = exp.asInstanceOf[CtBinaryOperator[_]]
          transformLoopExpressions(functionToTransform, loopEnd, loopNum)
          loopNum += 1
        case _ => throw new IllegalArgumentException(s"class type was ${exp.getClass}")
      }
    }
    functionToTransform.setSimpleName(s"autoTransformed${functionToTransform.getSimpleName}")
  }

  private def transformFieldAssignments(func: MethodType, f: CtFieldWrite[Any],
                                        fwCandidates: Seq[(CtExpression[_], String, Int, Int, CtElement)]): Unit = {
    val factory: Factory = f.getFactory
    val s: CtAssignment[Any, Any] = factory.createAssignment[Any, Any]()
    val assigned: CtExpression[Any] = createFieldReference[Any](s"this.${f.getVariable}", f.getType)
    val assignedExp = f.getParent.asInstanceOf[AssignmentType].getAssignment
    val clone = assignedExp.asInstanceOf[CtExpressionImpl[Any]].clone()
    s.setAssigned(assigned)
    s.setAssignment(clone)
    s.getAssignment.getElements(constantFilter).asScala
      .filter(c =>
        fwCandidates.exists{case (const,_,_,_,exp) =>
          c.equals(const) &&
            c.getParent().toString == const.getParent().toString &&
            exp.toString == s.getAssigned.toString
        }
      )
      .foreach { c: Constant =>
        val doubleType = factory.createTypeReference[Double]()
        c.replace(createExpression(s"ctrlVar$constNum", doubleType))
        addControlVariable(func, s.getAssignment, c.getType, s"ctrlVar$constNum")
        constNum += 1
      }
    func.getBody.insertBegin(s)
  }

  private def createFieldReference[T](varName: String, varType: CtTypeReference[T]): CtVariableReadImpl[T] =  {
    val expression = new CtVariableReadImpl[T]
    val localVar = new CtLocalVariableReferenceImpl[T]
    localVar.setSimpleName(varName)
    expression.setVariable(localVar)
    expression
  }

  private def transformConstant[T](func: MethodType, exp: CtExpression[T], v: CtTypedElement[T]): Unit = {
    val varType: CtTypeReference[T] = v.getType
    val constants = exp.getElements(constantFilter).asScala
    constants.foreach{ c =>
      if(c != null && varType != null) {
        val expression = createExpression(s"ctrlConst$constNum", varType)
        c.replace(expression)
        addControlVariable(func, exp, c.getType, s"ctrlConst$constNum")
        constNum += 1
      }
    }
  }

  private def transformIfExpressions(func: MethodType, statement: CtIf, index: Int): Unit = {
    val compareCondition = statement.getCondition.asInstanceOf[CtBinaryOperator[java.lang.Boolean]]
    if(compareCondition.getRightHandOperand.toString != "null") {
      val literal = compareCondition.getRightHandOperand.asInstanceOf[CtLiteral[_]]
      val add = new CtBinaryOperatorImpl[Double]
      add.setKind(BinaryOperatorKind.PLUS)
      add.setLeftHandOperand(literal)
      val varType: CtTypeReference[_] = compareCondition.getLeftHandOperand.getType
      val expression = createExpression(s"ctrlCmp$index", varType)
      add.setRightHandOperand(expression)
      compareCondition.setRightHandOperand(add)
      addControlVariable(func, statement, varType, s"ctrlCmp$index")
    }
  }

  private def transformLoopExpressions[T](func: MethodType, loopEnd: CtBinaryOperator[_], index: Int): Unit = {
    val rhs: CtExpression[_] = loopEnd.getRightHandOperand
    val add = new CtBinaryOperatorImpl[Double]
    add.setKind(BinaryOperatorKind.PLUS)
    add.setLeftHandOperand(rhs)
    val varType: CtTypeReference[_] = loopEnd.getLeftHandOperand.getType
    val expression =  createExpression(s"ctrlLoop$index", varType)
    add.setRightHandOperand(expression)
    loopEnd.setRightHandOperand(add)
    addControlVariable(func, loopEnd, varType, s"ctrlLoop$index")
  }

  private def createExpression[T](varName: String, varType: CtTypeReference[T]): CtExpression[T] = {
    val expression: CtVariableReadImpl[T] = new CtVariableReadImpl[T]
    val factory = varType.getFactory
    val localVar = factory.createLocalVariableReference[T]()
    localVar.setSimpleName(varName)
    expression.setVariable(localVar)
    if(!(varType.toString == "double") && varType.toString.nonEmpty)
      expression.addTypeCast(varType)
    expression
  }

  private def addControlVariable[T](func: MethodType, e: CtElement, varType: CtTypeReference[T], name: String): Unit ={
    val factory: Factory = e.getFactory
    val ctrlParam = factory.createParameter[T]()
    if(varType.getSimpleName == "double" || varType.getSimpleName == "String")
      ctrlParam.setSimpleName(s"${varType.getSimpleName.trim} $name")
    else
      ctrlParam.setSimpleName(s"double $name")
    func.addParameter(ctrlParam)
  }

  /**
    * Determines if a given expression is valid for transformation
    * @param statement - input expression
    * @param laterAssignments - book-keeps whether a variable definition was later assigned a different value
    * @param fieldAssignments - book-keeps all field assignments for the un-transformed input class
    * @return true if and only if expression is valid for transformation, otherwise false
    */
  private def shouldTransform(statement: CtElement, laterAssignments: Seq[AssignmentType] = Seq(),
                              fieldAssignments: Seq[CtFieldWrite[Any]] = Seq()): Boolean = {
    if (Recognizer.recognize[LocalVar](statement)) {
      val v = statement.asInstanceOf[LocalVar]
      val assign = v.getAssignment
      val varName = v.getSimpleName
      val usedAsIndex = laterAssignments.exists{ a =>
        val assignedStr = a.getAssigned.toString
        // avoids transforming array accessors in future usages
        assignedStr.contains(s"[$varName]")
      }
      // avoids transforming array accessors in original variable assignment
      if(assign == null || assign.toString.contains("[")) false
      else {
        val constants = assign.getElements(constantFilter).asScala.toList
        val parent = v.getParent
        // avoids transforming array accessors, and accessors within a loop
        !assign.getType.toString.contains("[]") && constants.nonEmpty &&
          !parent.isInstanceOf[CtFor] && !parent.isInstanceOf[CtWhile] && !usedAsIndex
      }
    }
    else if (Recognizer.recognize[AssignmentType](statement)) {
      val a = statement.asInstanceOf[AssignmentType]
      val assign = a.getAssignment
      val constants = assign.getElements(constantFilter).asScala.toList
      // avoids transforming array accessors
      !assign.toString.contains("[") && constants.nonEmpty
    }
    else if(Recognizer.recognize[CtIf](statement)){
      val conditional = statement.asInstanceOf[CtIf]
      conditional.getCondition match {
        case compareCondition: CtBinaryOperator[java.lang.Boolean] =>
          compareCondition.getRightHandOperand.isInstanceOf[CtLiteral[_]]
        case _ => false
      }
    }
    else if(Recognizer.recognize[CtFor](statement)) true
    else if(Recognizer.recognize[CtField[Any]](statement)) {
      val f = statement.asInstanceOf[CtField[Any]]
      val numAssigns = fieldAssignments.count(_.getVariable.getSimpleName == f.getSimpleName)
      numAssigns == 1 && fieldAssignments.exists(containedInConstructor)
    }
    else if(Recognizer.recognize[CtFieldWrite[Any]](statement)) true
    else if(Recognizer.recognize[CtBinaryOperator[java.lang.Boolean]](statement)) true
    else {
      throw new IllegalArgumentException(s"wanted LocalVar or AssignmentType but found: ${statement.getClass}")
    }
  }

  private def containedInConstructor(element: CtElement): Boolean = {
    val parents: Seq[CtElement] = getParentChain(element)
    parents.exists{ parent: CtElement =>
      Recognizer.recognize[CtConstructor[Any]](parent)
    }
  }

  private def getParentChain(element: CtElement): Seq[CtElement] = {
    var temp = element
    var parents: Seq[CtElement] = List(temp)
    while(temp.getParent != null){
      temp = temp.getParent
      parents = parents :+ temp
    }
    parents
  }
}