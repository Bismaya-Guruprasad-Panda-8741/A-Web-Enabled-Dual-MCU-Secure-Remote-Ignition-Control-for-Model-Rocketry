// ============================================================
//   Stellar Ignition System — Arduino UNO Ignition Controller
//   Author  : Bismaya Guruprasad Panda | Debasish Nayak
//   Board   : Arduino UNO
//   Role    : Countdown Timer · Buzzer · Fuse PWM Trigger
// ============================================================

// ── Pin Definitions ──────────────────────────────────────────
const int buzzerPin  = 13;  // Piezo buzzer output
const int triggerPin = 7;   // Trigger input from ESP32 (INPUT_PULLUP, LOW = fire)
const int fusePin    = 9;   // PWM output to ignition fuse driver circuit

// ─────────────────────────────────────────────────────────────
void setup()
{
  Serial.begin(9600);

  pinMode(buzzerPin,  OUTPUT);
  pinMode(triggerPin, INPUT_PULLUP); // LOW pulse from ESP32 GPIO 4 starts sequence
  pinMode(fusePin,    OUTPUT);

  digitalWrite(fusePin, LOW); // Ensure fuse is off at power-up

  Serial.println("========================================");
  Serial.println("         LAUNCH COUNTDOWN SYSTEM       ");
  Serial.println("========================================");
  Serial.println();
  Serial.println("System Ready.");
  Serial.println("Waiting for launch signal on pin 7...");
  Serial.println("Fuse trigger on pin 9 - READY");
}

// ─────────────────────────────────────────────────────────────
void loop()
{
  if (digitalRead(triggerPin) == LOW)
  {
    Serial.println("Launch signal received!");
    delay(200); // Software debounce

    rocketCountdown();

    Serial.println("System on standby mode.");
    Serial.println("Waiting for next launch signal on pin 7...");
    Serial.println();
    delay(500);
  }
}

// ── Full Launch Sequence ─────────────────────────────────────
void rocketCountdown()
{
  Serial.println("INITIATING LAUNCH SEQUENCE...");
  Serial.println();
  delay(1000);

  // ── Phase 1: Slow countdown T-10 to T-6 ──────────────────
  Serial.println("=== PHASE 1: INITIAL COUNTDOWN ===");
  for (int i = 10; i >= 6; i--)
  {
    Serial.print("T-");
    Serial.println(i);
    tone(buzzerPin, 800, 500); // 800 Hz for 500 ms
    delay(1000);
  }
  Serial.println();

  // ── Phase 2: Accelerating countdown T-5 to T-1 ───────────
  Serial.println("=== PHASE 2: ACCELERATION PHASE ===");
  for (int i = 5; i >= 1; i--)
  {
    Serial.print("T-");
    Serial.println(i);
    tone(buzzerPin, 1200, 300); // 1200 Hz for 300 ms
    delay(600);
  }
  Serial.println();

  // ── Phase 3: Rapid pre-ignition beeps ────────────────────
  Serial.println("=== PHASE 3: FINAL SEQUENCE ===");
  for (int i = 0; i < 5; i++)
  {
    Serial.print("WARNING   ");
    tone(buzzerPin, 1500, 150);
    delay(200);
  }
  Serial.println();

  Serial.println("LAUNCH!");
  Serial.println("Deployment Successful!");

  // ── Ignition: full 100% PWM for 3 seconds ────────────────
  Serial.println("*** ACTIVATING FUSE TRIGGER ***");

  tone(buzzerPin, 2000);     // Continuous 2000 Hz alarm tone
  analogWrite(fusePin, 255); // 100% duty cycle → full current to fuse

  for (int i = 1; i <= 3; i++)
  {
    delay(1000);
    Serial.print("Launch +");
    Serial.print(i);
    Serial.println(" seconds - FUSE ACTIVE");
  }

  noTone(buzzerPin);         // Stop buzzer
  analogWrite(fusePin, 0);   // Cut power to fuse

  Serial.println("*** FUSE TRIGGER DEACTIVATED ***");
  Serial.println();
  Serial.println("=== LAUNCH SEQUENCE COMPLETED ===");
  Serial.println("System Status: Normal");
  Serial.println("Launch successful!");
  Serial.println("========================================");
  Serial.println();
}
