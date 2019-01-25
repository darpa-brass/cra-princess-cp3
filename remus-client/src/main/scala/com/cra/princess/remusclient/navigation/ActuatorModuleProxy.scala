package com.cra.princess.remusclient.navigation

import com.cra.princess.metron.remus.command.RemusVehicleCommand
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorVector

class ActuatorModuleProxy {
  
  def generateRemusCommand(actuatorValues: KalmanFilterActuatorVector, depth: Double): RemusVehicleCommand = {
    val rpm = actuatorValues.getEntry(0)
    val ratio = actuatorValues.getEntry(1)
    val slip = actuatorValues.getEntry(3)
    
    val speed = (rpm / ratio) * (1 - (slip / 100)) / 60.0
    
    val heading = actuatorValues.getEntry(4)
    
    new RemusVehicleCommand(heading, depth, speed)
  }

  def generateRemusStopCommand: RemusVehicleCommand = new RemusVehicleCommand(0.0, 0.0, 0.0)

}