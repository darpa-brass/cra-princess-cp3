package com.cra.princess.core

sealed abstract class AdaptationState
  case object ANALYSIS_STARTED extends AdaptationState
  case object INTENT_VIOLATION_DETECTED extends AdaptationState
  case object ADAPTATION_STARTED extends AdaptationState
  case object ADAPTATION_COMPLETE extends AdaptationState
  case object ANALYSIS_COMPLETE extends AdaptationState
