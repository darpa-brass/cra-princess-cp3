package com.cra.princess.optimizer

trait Trainable[Input, Output]{
  def train(x: Input, y: Output): Array[Double]
}
