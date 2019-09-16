package com.cra.princess

import java.io.{File, FileOutputStream, PrintWriter}

import scala.util.Random


object RLTestGame{
  def main(args: Array[String]): Unit = {
    val actorFile = "gameActor.h5"
    val criticFile = "gameCritic.h5"
//    val range = List(-25, 25)
    val destX = 25//choose(range)
    val destY = 25//choose(range)

    val testOpt: TestOptimizer = TestOptimizer(actorFile, criticFile, dimension = 2,
      initialState = Array(0,0,destX,destY), maxBufferSize = 1000)
    val maxIterations = 1000000
    for(i <- 0 until maxIterations) {
      var numMoves = 0
      println("initializing scenario.......")
      val pw = new PrintWriter(new FileOutputStream(new File("gameResults.csv"), true))
      var currentState = GameState((0,0), (destX, destY), (0,0))
      while (numMoves < 25 && currentState.currentLoc != currentState.dest) {
        val ctrls = testOpt.train(currentState, currentState)
        val move = Move(ctrls(0).round.toInt, ctrls(1).round.toInt)
//        val move = testOpt.selectMove(currentState)
        currentState = move(currentState)
        println(currentState)
        numMoves += 1
      }
      val (x1, y1) = currentState.currentLoc
      val (x2, y2) = currentState.dest
      pw.println(s"${Math.hypot(x1 - x2, y1 - y2)}, $numMoves")
      pw.close()
      testOpt.policy.setIterations(i)
      testOpt.saveParams(actorFile, criticFile)
    }
  }

  def choose[A](list: List[A]): A = choose2(list.iterator)
  def choose2[A](it: Iterator[A]): A =
    it.zip(Iterator.iterate(1)(_ + 1)).reduceLeft((row, col) =>
      if (Random.nextInt(col._2) == 0) col else row
    )._1
}

case class GameState(currentLoc: (Int, Int), dest: (Int, Int), prevLoc: (Int, Int))
case class Move(x: Int, y: Int) extends (GameState => GameState) {
  override def apply(v1: GameState): GameState = {
    val (prevX, prevY) = v1.currentLoc
    v1.copy(currentLoc = (prevX + x, prevY + y), prevLoc = v1.currentLoc)
  }
}