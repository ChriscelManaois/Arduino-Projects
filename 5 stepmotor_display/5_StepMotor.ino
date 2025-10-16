#include <Stepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // Include the LCD I2C Library

// --- Stepper Motor Setup (Remains the same) ---
const int stepsPerRevolution = 2048; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); // Pins 8, 10, 9, 11

// --- LCD Setup ---
// Set the LCD address (0x27 or 0x3F are most common) and the number of columns and rows
// You may need to change 0x27 to 0x3F if your screen doesn't work.
LiquidCrystal_I2C lcd(0x27, 16, 2); 


void setup() {
  // --- Motor Setup ---
  myStepper.setSpeed(10); 
  Serial.begin(9600);

  // --- LCD Initialization ---
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on the backlight (if applicable)
  
  // Initial message on LCD
  lcd.print("Stepper Project");
  lcd.setCursor(0, 1); // Move to the second row (row 1, since it starts at 0)
  lcd.print("Ready...");
  delay(2000);
  lcd.clear(); // Clear initial message
}

void loop() {
  // 1. Clockwise Movement
  lcd.clear();
  lcd.print("Direction: CW ->");
  lcd.setCursor(0, 1);
  lcd.print("Status: Moving");
  
  Serial.println("Moving Clockwise");
  myStepper.step(stepsPerRevolution); 
  
  // Display completion status
  lcd.setCursor(0, 1); // Go back to the second row
  lcd.print("Status: CW Done!");
  
  delay(1000); // Wait for a second

  // 2. Counter-Clockwise Movement
  lcd.clear();
  lcd.print("Direction: <- CCW");
  lcd.setCursor(0, 1);
  lcd.print("Status: Moving");
  
  Serial.println("Moving Counter-Clockwise");
  myStepper.step(-stepsPerRevolution); // Negative steps reverse direction
  
  // Display completion status
  lcd.setCursor(0, 1); // Go back to the second row
  lcd.print("Status: CCW Done!");

  delay(1000); // Wait for a second
}