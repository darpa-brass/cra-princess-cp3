package com.cra.princess.componentmodel.codeanalysis

import java.io._

import com.cra.princess.util.Recognizer
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

object ProgramTransformer{

  type MethodType = CtMethod[Int]
  type AssignmentType = CtAssignment[Any, Any]
  type VarAccess = CtVariableAccessImpl[Any]
  type LocalVar = CtLocalVariable[Any]
  type Constant = CtLiteralImpl[_]
  type Field = CtField[Any]
  val assignmentFilter = new TypeFilter[AssignmentType](classOf[AssignmentType])
  val constantFilter = new TypeFilter[Constant](classOf[Constant])
  val fieldFilter = new TypeFilter[CtField[Any]](classOf[CtField[Any]])
  val fieldWriteFilter = new TypeFilter[CtFieldWrite[Any]](classOf[CtFieldWrite[Any]])
  val ifFilter =  new TypeFilter[CtIf](classOf[CtIf])
  val localVarFilter = new TypeFilter[LocalVar](classOf[LocalVar])
  val loopFilter =  new TypeFilter[CtFor](classOf[CtLoop])
  val anyFilter = new TypeFilter[CtElement](classOf[CtElement])
  val classFilter = new TypeFilter[CtClass[Any]](classOf[CtClass[Any]])
  var constNum = 0

  def  main(args: Array[String]): Unit = {
//    val inputPath = "kalmanfilter/src/main/java/com/cra/princess/models/SingleFunctionKalmanFilter.java"//args(0)
    val inputPath = "pathplanner/src/main/java/com/cra/princess/pathplanner/SingleFunctionPathPlanner.java"
//    val outputPath = "SingleFunctionKalmanFilter.java"//args(1)
    val outputPath = "SingleFunctionPathPlanner.java"//args(1)
    transformClass(inputPath, outputPath)
  }

  def transformClass(inputPath: String, outputPath: String): Unit = {
    val launcher = new Launcher
    launcher.addInputResource(inputPath)
    launcher.getEnvironment.setAutoImports(true)
    launcher.getEnvironment.setNoClasspath(true)
    launcher.buildModel()
    val model: CtModel = launcher.getModel
    val cu: CompilationUnit = launcher.getFactory.CompilationUnit.create(model.getAllTypes.asScala.head.getPosition.getFile.getAbsolutePath)
    val methodFilter = new TypeFilter[MethodType](classOf[MethodType])
    val methodElements: Seq[MethodType] = model.getElements(methodFilter).asScala
    val mainClass = model.getElements(new TypeFilter[CtClass[Any]](classOf[CtClass[Any]])).asScala.toList.head
    val functionToTransform: MethodType = methodElements.filter(method => method.getModifiers.asScala.toList.exists(_.toString == "public")).head
    val fields: Seq[CtField[Any]] = model.getElements(fieldFilter).asScala.toList
    val fieldAssignments: Seq[CtFieldWrite[Any]] = model.getElements(fieldWriteFilter).asScala.toList

    val constantFieldAssignments: Seq[CtExpression[Any]] = model.getElements(assignmentFilter).asScala.map(a => a.getAssignment)
    transformMethod(functionToTransform, Set(), fields, fieldAssignments, constantFieldAssignments)
    
    val pw = new PrintWriter(new File(outputPath))
    pw.println(s"package ${mainClass.getPackage};\n")
    cu.getImports.asScala.toList.foreach(lib => pw.println(s"import $lib;"))
    pw.println()
    pw.println(model.getAllTypes.asScala.head)
    pw.close()
  }

  private def createFieldReference[T](varName: String, varType: CtTypeReference[T]) =  {
    val expression = new CtVariableReadImpl[T]
    val localVar = new CtLocalVariableReferenceImpl[T]
    localVar.setSimpleName(varName)
    expression.setVariable(localVar)
    expression
  }

  // TODO: figure out how to find literals (non-trivial) in set
  //     - features for literal? exclusion conditions?
  //     - NN to learn correct literals ?
  // replace every literal in set with a new formal argument
  def transformMethod(functionToTransform: MethodType, literals: Set[CtLiteral[Any]], fields: Seq[CtField[Any]],
                      fieldAssignments: Seq[CtFieldWrite[Any]], constExpressions: Seq[CtExpression[Any]]): Unit = {
    transformConstantAssignments(functionToTransform)
    transformLoopExpressions(functionToTransform)
    transformIfExpressions(functionToTransform)
    liftFieldsInMethod(functionToTransform, fields, fieldAssignments, constExpressions)
    functionToTransform.setSimpleName(s"autoTransformed${functionToTransform.getSimpleName}")
  }

  private def liftFieldsInMethod(func: MethodType, fields: Seq[CtField[Any]], fieldAssignments: Seq[CtFieldWrite[Any]],
                                 constExpressions: Seq[CtExpression[Any]]): Unit = {
    def insertStatementToMethod(method: MethodType, s: CtStatement): Unit = method.getBody.insertBegin(s)
    var index = 0
    val statements = fields.filter{f => fieldAssignments.count(_.getVariable.getSimpleName == f.getSimpleName) == 1}.map{ (f: CtField[Any]) =>
      val factory = f.getFactory
      val s = factory.createAssignment[Any, Any]()
      val assigned: CtExpression[Any] = createFieldReference[Any](s"this.${f.getSimpleName}", f.getType)
      val clone = constExpressions(index).asInstanceOf[CtExpressionImpl[Any]].clone()
      s.setAssigned(assigned)
      s.setAssignment(clone)
      s.getAssignment.getElements(constantFilter).asScala.foreach{ (c: Constant) =>
        val doubleType = factory.createTypeReference[Double]()
        c.replace(createExpression(s"ctrlVar$constNum", doubleType))
        addControlVariable(func, s.getAssignment, c.getType, s"ctrlVar$constNum")
        constNum += 1
      }
      index += 1
      s
    }
    statements.foreach(s => insertStatementToMethod(func, s))
  }

  private def transformIfExpressions(func: MethodType): Unit = {
    val ifStatements: Seq[CtIf] = func.getBody.getElements(ifFilter).asScala.toList
    var ctrlCmpNum = 0
    ifStatements.foreach{ statement =>
      statement.getCondition match {
        case compareCondition: CtBinaryOperator[java.lang.Boolean] =>
          compareCondition.getRightHandOperand match {
            case literal : CtLiteral[_] =>
              val add = new CtBinaryOperatorImpl[Double]
              add.setKind(BinaryOperatorKind.PLUS)
              add.setLeftHandOperand(literal)
              val varType: CtTypeReference[_] = compareCondition.getLeftHandOperand.getType
              val expression =  createExpression(s"ctrlCmp$ctrlCmpNum", varType)
              add.setRightHandOperand(expression)
              compareCondition.setRightHandOperand(add)
              addControlVariable(func, statement, varType, s"ctrlCmp$ctrlCmpNum")
              ctrlCmpNum +=1
            case _ =>
          }
        case _ =>
      }
    }
  }

  private def transformLoopExpressions[T](func: MethodType): Unit ={
    val loops: Seq[CtFor] = func.getBody.getElements(loopFilter).asScala.toList
    loops.indices.foreach{ i =>
      val loop: CtFor = loops(i)
      val loopEnd = loop.getExpression.asInstanceOf[CtBinaryOperator[_]]
      val rhs: CtExpression[_] = loopEnd.getRightHandOperand
      val add = new CtBinaryOperatorImpl[T]
      add.setKind(BinaryOperatorKind.PLUS)
      add.setLeftHandOperand(rhs)
      val varType: CtTypeReference[_] = loopEnd.getLeftHandOperand.getType
      val expression =  createExpression(s"ctrlLoop$i", varType)
      add.setRightHandOperand(expression)
      loopEnd.setRightHandOperand(add)
      addControlVariable(func, loopEnd, varType, s"ctrlLoop$i")
      loop
    }
  }

  private def transformConstantAssignments(func: MethodType): Unit = {
    val localVars = func.getBody.getElements(localVarFilter).asScala // local variable definitions
    val assignments = func.getBody.getElements(assignmentFilter).asScala.toList // assignment to variables
    localVars.filter(shouldTransform(_, assignments)).foreach{ (v: LocalVar) =>
      val assign = v.getAssignment
      transformConstant(func, assign, v)
    }
    assignments.filter(shouldTransform(_)).foreach{ (a: AssignmentType) =>
      val assign = a.getAssignment
      transformConstant(func, assign, a)
    }
  }

  private def transformConstant[T](func: MethodType, exp: CtExpression[T], v: CtTypedElement[T]): Unit ={
    val varType: CtTypeReference[T] = v.getType
    val constants = exp.getElements(constantFilter).asScala
    constants.foreach{ c =>
      val expression = createExpression(s"ctrlConst$constNum", varType)
      c.replace(expression)
    }
    addControlVariable(func, exp, varType, s"ctrlConst$constNum")
    constNum+=1
  }

  private def shouldTransform(statement: CtStatement, laterAssignments: Seq[AssignmentType] = Seq()): Boolean = {
    if (Recognizer.recognize[LocalVar](statement)) {
      val v = statement.asInstanceOf[LocalVar]
      val assign = v.getAssignment
      val varName = v.getSimpleName
      val isIndexVariable = laterAssignments.exists{ a =>
        val assignedStr = a.getAssigned.toString
        assignedStr.contains(s"[$varName]")
      }
      if(assign == null) false
      else {
        val constants = assign.getElements(constantFilter).asScala
        val parent = v.getParent
        !assign.getType.toString.contains("[]") && constants.nonEmpty &&
          !parent.isInstanceOf[CtFor] && !parent.isInstanceOf[CtWhile] && !isIndexVariable
      }
    }
    else if (Recognizer.recognize(statement, scala.reflect.runtime.universe.typeOf[AssignmentType])) {
      val a = statement.asInstanceOf[AssignmentType]
      val assign = a.getAssignment
      val constants = assign.getElements(constantFilter).asScala.toList
      !assign.toString.contains("[") && constants.nonEmpty
    }
    else {
      throw new IllegalArgumentException(s"wanted LocalVar or AssignmentType but found: ${statement.getLabel}")
    }
  }

  private def createExpression[T](varName: String, varType: CtTypeReference[T]): CtExpression[T] =  {
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
    if(varType.getSimpleName == "double"){
      val t = e.getReferencedTypes.asScala.head.asInstanceOf[CtTypeReference[T]]
      t.setSimpleName(varType.getSimpleName)
      ctrlParam.setType(t)
      ctrlParam.setSimpleName(name)
    }
    else
      ctrlParam.setSimpleName(s"double $name")
    func.addParameter(ctrlParam)
  }
}