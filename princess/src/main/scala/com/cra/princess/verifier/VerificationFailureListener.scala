package com.cra.princess.verifier

trait VerificationFailureListener {
  def verificationFailed(failure: VerificationFailure)
}
