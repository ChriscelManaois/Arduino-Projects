// --- LIBRARIES ---
#include <LiquidCrystal_I2C.h>

// --- LCD SETUP ---
// Common I2C Address is 0x27 or 0x3F. Check your module if 0x27 doesn't work.
// Ensure your wiring for SDA (A4) and SCL (A5) is correct.
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// --- PIN DEFINITIONS ---
// Car Traffic Light Pins
const int CAR_RED_PIN = 13;
const int CAR_YELLOW_PIN = 12;
const int CAR_GREEN_PIN = 11;

// Pedestrian Light Pins
const int PED_RED_PIN = 10;
const int PED_GREEN_PIN = 9;

// Button Pin (Connect one side to Pin 2, the other side to GND)
const int BUTTON_PIN = 2;

// --- MILLIS TIMING & STATE VARIABLES ---
unsigned long previousMillis = 0;   // Stores last time the state was updated
unsigned long requestTime = 0;      // Stores the millis() when the button was first pressed
int current_state = 0;              // 0: Car Green, 1: Car Yellow, 2: Car Red/Ped Walk
bool cross_requested = false;       // Flag to track if button was pressed

// --- TIMING CONSTANTS (in milliseconds) ---
// Adjust these values to change how long each light phase lasts.
const long GREEN_DURATION = 15000;  // Minimum Car Green duration (15 seconds)
const long YELLOW_DURATION = 2000;  // Car Yellow duration (2 seconds)
const long WALK_DURATION = 10000;   // Pedestrian Walk duration (10 seconds)
long phase_duration = GREEN_DURATION; // Duration for the current phase

// =======================================================
// HELPER FUNCTION for LCD
// =======================================================

void update_lcd_status(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0); // Start of the first line
  lcd.print(line1);
  lcd.setCursor(0, 1); // Start of the second line
  lcd.print(line2);
}

// =======================================================
// SETUP FUNCTION - Runs once when Arduino starts
// =======================================================

void setup() {
  // --- Initialize LCD ---
  lcd.init();
  lcd.backlight();
  
  // Set all LED pins as outputs
  pinMode(CAR_RED_PIN, OUTPUT);
  pinMode(CAR_YELLOW_PIN, OUTPUT);
  pinMode(CAR_GREEN_PIN, OUTPUT);
  pinMode(PED_RED_PIN, OUTPUT);
  pinMode(PED_GREEN_PIN, OUTPUT);

  // Set the button pin as an input with an internal PULLUP resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Set initial state
  digitalWrite(CAR_GREEN_PIN, HIGH);
  digitalWrite(PED_RED_PIN, HIGH);
  digitalWrite(CAR_RED_PIN, LOW);
  digitalWrite(CAR_YELLOW_PIN, LOW);
  digitalWrite(PED_GREEN_PIN, LOW);

  // Set initial timer state
  previousMillis = millis(); 
  
  // Update LCD with initial status
  update_lcd_status("Car: GO", "Press Button");
  
  Serial.begin(9600);
  Serial.println("System Initialized. Car Green.");
}

// =======================================================
// MAIN LOOP - Runs repeatedly
// =======================================================

void loop() {
  unsigned long currentMillis = millis();
  
  // 1. Check for button press
  if (digitalRead(BUTTON_PIN) == LOW && current_state == 0) {
    if (!cross_requested) {
      cross_requested = true;
      // Record the time the request was made
      requestTime = currentMillis; 
      update_lcd_status("Car: GO", "REQUESTED! Wait...");
      Serial.println("Pedestrian request recorded.");
    }
    // IMPORTANT: If a request is already made, subsequent presses are ignored 
    // until the cycle resets. This prevents the button from "nullifying" itself.
  }

  // 2. Check if the current phase time has elapsed OR if a transition condition is met
  if (currentMillis - previousMillis >= phase_duration) {
    previousMillis = currentMillis; // Reset timer for the next phase

    // --- STATE MACHINE ---
    switch (current_state) {
      case 0: // STATE 0: CAR GREEN
        // Transition only if:
        // 1. A request was made AND
        // 2. The minimum safe GREEN_DURATION has passed since the request time
        if (cross_requested && (currentMillis - requestTime >= GREEN_DURATION)) { 
          current_state = 1; // -> State 1 (CAR YELLOW)
          phase_duration = YELLOW_DURATION;
          
          // Set Pins & LCD for State 1
          digitalWrite(CAR_GREEN_PIN, LOW);
          digitalWrite(CAR_YELLOW_PIN, HIGH);
          update_lcd_status("Car: SLOW DOWN", "Ped: Wait");
          Serial.println("Phase: Car Yellow");
        } else {
          // If no transition, reset timer to continuously check the request/time condition
          previousMillis = currentMillis; 
        }
        break;

      case 1: // STATE 1: CAR YELLOW
        current_state = 2; // -> State 2 (CAR RED / PED WALK)
        phase_duration = WALK_DURATION;
        
        // Set Pins & LCD for State 2
        digitalWrite(CAR_YELLOW_PIN, LOW);
        digitalWrite(CAR_RED_PIN, HIGH);
        digitalWrite(PED_RED_PIN, LOW);
        digitalWrite(PED_GREEN_PIN, HIGH);
        update_lcd_status("Car: STOP", "Ped: WALK NOW!");
        Serial.println("Phase: Pedestrian Walk");
        break;

      case 2: // STATE 2: CAR RED / PED WALK
        current_state = 0; // -> State 0 (CAR GREEN - Reset)
        phase_duration = GREEN_DURATION;
        
        // Reset flags and timers for the next cycle
        cross_requested = false; 
        requestTime = 0; 
        
        // Set Pins & LCD for State 0
        digitalWrite(PED_GREEN_PIN, LOW);
        digitalWrite(PED_RED_PIN, HIGH);
        digitalWrite(CAR_RED_PIN, LOW);
        digitalWrite(CAR_GREEN_PIN, HIGH);
        update_lcd_status("Car: GO", "Press Button");
        Serial.println("Phase: Car Green (System Reset)");
        break;
    }
  }
}