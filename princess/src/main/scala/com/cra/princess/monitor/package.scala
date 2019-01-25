package com.cra.princess

import com.cra.princess.core.{IntentResult, VerificationResult}

package object monitor {
  type IntentResultListener = IntentResult => Unit
  type VerificationResultListener = VerificationResult => Unit
}
