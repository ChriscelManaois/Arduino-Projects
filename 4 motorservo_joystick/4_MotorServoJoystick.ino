#include <Servo.h>

// 1. Define the pins used
const int servoPin = 9;  // The SG90 signal wire is connected to Digital Pin 9
const int joyPinX = A0;  // The Joystick VRx (X-axis) is connected to Analog Pin A0

// 2. Create a Servo object
Servo myservo;

void setup() {
  // Attach the servo object to the pin
  myservo.attach(servoPin);

  // Optional: Start serial communication to debug/see values
  Serial.begin(9600);
  Serial.println("Joystick to Servo Control Initialized.");
}

void loop() {
  // 3. Read the raw value from the joystick X-axis
  int joyVal = analogRead(joyPinX);

  // 4. Map the joystick range (0 to 1023) to the servo range (0 to 180 degrees)
  // The 'map' function automatically handles the scaling.
  int servoAngle = map(joyVal, 0, 1023, 0, 180);

  // 5. Command the servo to move to the calculated angle
  myservo.write(servoAngle);

  // 6. Pause briefly to allow the servo to move and prevent jitter
  delay(15);
}