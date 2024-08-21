// Define pins for IN1 and IN2
#define IN1 2
#define IN2 3

void setup() {
  Serial.begin(115200);
  Serial.println("Started");
  // Set IN1 and IN2 as output pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  Serial.println("Running");
  // Move motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(2000);  // Run motor forward for 2 seconds

  // Stop the motor for a moment
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);  // Stop motor for 1 second

  // Move motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(2000);  // Run motor backward for 2 seconds

  // Stop the motor for a moment
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);  // Stop motor for 1 second
}
