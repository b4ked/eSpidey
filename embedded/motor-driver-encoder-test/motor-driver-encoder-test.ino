// Define pins for IN1 and IN2
#define IN1 2
#define IN2 3

// Define encoder pins
#define ENCODER_A 12
#define ENCODER_B 1

// Variables to store the encoder count
volatile long encoderCount = 0;

void IRAM_ATTR handleEncoderA() {
  // Read the state of ENCODER_B to determine direction
  if (digitalRead(ENCODER_B) == LOW) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set encoder pins as inputs
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);

  // Attach interrupts to encoder pins
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), handleEncoderA, RISING);

  // Initial Serial feedback
  Serial.println("Starting motor movement sequence...");
}

void moveMotor(int direction, int ticks) {
  // Set motor direction
  if (direction == 1) {  // Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    Serial.println("Moving Forward");
  } else {  // Backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    Serial.println("Moving Backward");
  }

  // Reset encoder count
  long startCount = encoderCount;

  // Move motor until 1 tick is detected
  while (abs(encoderCount - startCount) < ticks) {
    // Print encoder count to Serial for debugging
    Serial.print("Encoder Count: ");
    Serial.println(encoderCount);
  }

  // Stop the motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("Motor Stopped");
  Serial.print("Final Encoder Count: ");
  Serial.println(encoderCount);
  //delay(100);  // Delay for 2 seconds
}

void loop() {

  Serial.println("One side");
  // Move motor forward 1 tick, 3 times
  for (int i = 0; i < 1; i++) {
    moveMotor(1, 2086);  // Move forward by 1 tick
  }

  delay(5000);

  Serial.println("Other side");
  // Move motor backward 1 tick, 3 times
  for (int i = 0; i < 1; i++) {
    moveMotor(-1, 2086);  // Move backward by 1 tick
  }

  delay(5000);
}
