package com.cra.princess.training

import scala.collection.mutable.ArrayBuffer
import scala.reflect.ClassTag
import scala.util.Random

class ReplayBuffer[T](val maxSize: Int)(implicit t: ClassTag[T]){
  val random = new Random(12345)
  private val replayBuffer = ArrayBuffer.empty[T]

  def getMiniBatch(batchSize: Int = 64): Array[T] =
    if(batchSize == replayBuffer.length) replayBuffer.toArray
    else random.shuffle(replayBuffer.toList).take(batchSize).toArray

  def storeInstance(input: T): Unit = {
    if(replayBuffer.length >= maxSize)
      replayBuffer.remove(0)
    replayBuffer.append(input)
  }

  def length(): Int = replayBuffer.length
}
