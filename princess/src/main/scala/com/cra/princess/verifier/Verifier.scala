package com.cra.princess.verifier

import com.cra.princess.core.VerificationResult

abstract class Verifier {
  def verify(output: Any): VerificationResult
}
