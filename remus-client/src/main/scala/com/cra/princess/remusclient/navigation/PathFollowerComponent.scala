package com.cra.princess.remusclient.navigation

import com.cra.princess.core.OptimizableComponent
import com.cra.princess.metron.remus.state.ObjectDetectionListener
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorVector

trait PathFollowerComponent extends OptimizableComponent[PathFollowerEnvironment, PathFollowerInput, KalmanFilterActuatorVector] with AbstractPathFollower with ObjectDetectionListener {

}
