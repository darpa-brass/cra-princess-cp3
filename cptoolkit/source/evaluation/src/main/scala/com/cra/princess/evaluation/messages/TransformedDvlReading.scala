package com.cra.princess.evaluation.messages

case class TransformedDvlReading(timestamp: Long,
                                 depth: Double,
                                 pitch: Double, roll: Double, heading: Double,
                                 vE: Double, vN: Double, vU: Double,
                                 vEConf: Double, vNConf: Double, vUConf: Double,
                                 vEStdDev: Double, vNStdDev: Double, vUStdDev: Double,
                                 surge: Double, sway: Double, heave: Double,
                                 surgeConf: Double, swayConf: Double, heaveConf: Double,
                                 surgeStdDev: Double, swayStdDev: Double, heaveStdDev: Double) extends ToJson

object TransformedDvlReading extends FromJson[TransformedDvlReading]