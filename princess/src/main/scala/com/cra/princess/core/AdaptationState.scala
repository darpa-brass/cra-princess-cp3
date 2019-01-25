package com.cra.princess.core

sealed abstract class AdaptationState
  case object INTENT_VIOLATION_DETECTED extends AdaptationState
  case object ADAPTATION_STARTED extends AdaptationState
  case object ADAPTATION_COMPLETE extends AdaptationState

