#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// --- Configuration ---

// **IMPORTANT**: Check your I2C address. Common addresses are 0x27 or 0x3F.
// You might need to run an I2C scanner sketch to confirm.
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// The duration for a C4 in CS:GO is 40 seconds (or 35 in CS 1.6/Source).
const int C4_DURATION = 40; 
const int BUZZER_PIN = 8; // Digital pin for the buzzer

// --- Time & State Variables ---

// Convert duration to milliseconds for the countdown
unsigned long totalTime_ms = (unsigned long)C4_DURATION * 1000;
unsigned long startTime_ms = 0;
int remainingTime_s = C4_DURATION;

// Ticking control variables
unsigned long lastTick_ms = 0;
unsigned long tickInterval_ms = 1000; // Default tick is every 1000ms (1 second)

// State flags
bool isArmed = true; 
bool detonated = false;

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Record the start time
  startTime_ms = millis();
  
  // Initial display
  lcd.setCursor(0, 0);
  lcd.print("C4 ARMED!");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (isArmed && !detonated) {
    
    // --- 1. Update Remaining Time ---
    
    unsigned long elapsedTime_ms = currentMillis - startTime_ms;
    
    // Remaining time in seconds
    remainingTime_s = C4_DURATION - (elapsedTime_ms / 1000);
    
    // --- 2. Ticking Logic ---
    
    // C4 ticking rate changes in CS:GO: 
    // >10s = 1s interval
    // 10s-5s = 0.5s interval
    // <5s = 0.3s interval
    
    if (remainingTime_s > 10) {
      tickInterval_ms = 1000;
    } else if (remainingTime_s > 5) {
      tickInterval_ms = 500;
    } else if (remainingTime_s > 0) {
      tickInterval_ms = 300;
    }

    if (currentMillis - lastTick_ms >= tickInterval_ms && remainingTime_s > 0) {
      lastTick_ms = currentMillis;
      
      // Make a short, low-frequency beep (the ticking sound)
      tone(BUZZER_PIN, 500, 50); // 500Hz for 50ms
    }

    // --- 3. Display Countdown ---
    
    // Check if a full second has passed to update the display
    if (currentMillis / 1000 != (currentMillis - 1000) / 1000) {
        
        // Ensure the display is cleared only in the countdown area
        lcd.setCursor(0, 1);
        lcd.print("                "); // Clear line 2

        // Calculate minutes and seconds for display
        int minutes = remainingTime_s / 60;
        int seconds = remainingTime_s % 60;
        
        // Print Time (MM:SS) roughly centered on Line 2
        lcd.setCursor(6, 1); 
        
        if (minutes < 10) lcd.print("0");
        lcd.print(minutes);
        lcd.print(":");
        if (seconds < 10) lcd.print("0");
        lcd.print(seconds);
    }
    
    // --- 4. Detonation Check ---
    
    if (remainingTime_s <= 0) {
      isArmed = false; // Stop the timer
      detonated = true; // Set the bomb state
      noTone(BUZZER_PIN); // Stop any remaining tick sound
    }
  }
  
  // --- 5. Detonation Action (BOOM) ---
  
  if (detonated) {
    // This runs only once after the countdown hits zero
    lcd.clear();
    
    // Print "BOOM!" on both lines for emphasis
    lcd.setCursor(5, 0); 
    lcd.print("*** BOOM! ***");
    lcd.setCursor(5, 1); 
    lcd.print("*** BOOM! ***");
    
    // Explosive Sound Effect (Simple siren-like sound)
    for (int i = 2000; i >= 100; i -= 10) {
      tone(BUZZER_PIN, i, 10);
      delay(1); 
    }
    noTone(BUZZER_PIN);

    detonated = false; // Prevent this block from running again
  }
}