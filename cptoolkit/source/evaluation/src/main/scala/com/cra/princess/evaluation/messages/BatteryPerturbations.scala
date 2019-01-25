package com.cra.princess.evaluation.messages

case class BatteryPerturbations(BatteryPerturbations: List[BPEntry]) extends ToJson
object BatteryPerturbations extends FromJson[BatteryPerturbations]

case class BPEntry(TimeIntoScenario: Int, PowerReduction: Int) extends ToJson
object BPEntry extends FromJson[BPEntry]
