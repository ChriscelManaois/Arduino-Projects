// --- Pin Definitions ---
const int soundSensorPin = 2; // Digital pin connected to the sensor's D0 pin
const int ledPin = 13;        // Digital pin connected to the LED

// --- State Variables ---
int ledState = LOW;             // Current state of the LED (LOW = Off, HIGH = On)
int lastSoundState = HIGH;      // Stores the last state of the sound sensor output
unsigned long lastEventTime = 0;  // Stores the time of the last clap event
const unsigned long debounceDelay = 200; // Milliseconds to ignore sound after a clap

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  // Initialize the sensor pin as an input
  pinMode(soundSensorPin, INPUT);

  // Set the initial state of the LED
  digitalWrite(ledPin, ledState);

  Serial.begin(9600); // Start serial communication for debugging
  Serial.println("Clap Switch Ready!");
}

void loop() {
  // Read the current state of the sound sensor
  int currentSoundState = digitalRead(soundSensorPin);

  // Check for a *falling edge* transition (Sound detected)
  // The D0 pin often goes LOW when sound is detected.
  if (lastSoundState == HIGH && currentSoundState == LOW) {

    // Check if enough time has passed since the last event (Debouncing)
    if (millis() - lastEventTime > debounceDelay) {
      // A valid clap has been detected!

      // 1. Update the LED state (Toggle it)
      ledState = !ledState; // This flips LOW to HIGH, and HIGH to LOW

      // 2. Control the LED
      digitalWrite(ledPin, ledState);

      // 3. Record the time of the event
      lastEventTime = millis();

      // 4. Print confirmation to the Serial Monitor
      if (ledState == HIGH) {
        Serial.println("Clap detected! LED ON.");
      } else {
        Serial.println("Clap detected! LED OFF.");
      }
    }
  }

  // Save the current sensor state for the next loop iteration
  lastSoundState = currentSoundState;
}

// End of code