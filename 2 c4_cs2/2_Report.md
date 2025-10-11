# Required Components

1. Arduino Uno
2. 16x2 LCD with I2C Adapter
3. Active or Passive Buzzer (A passive buzzer is recommended for cleaner sound control).
4. Jumper Wires
5. Breadboard (optional, but makes wiring cleaner)

# Arduino Uno Wiring Diagram

Component	Pin Label	Connect to Arduino Uno Pin
I2C LCD	    GND	        GND
I2C LCD	    VCC	        5V
I2C LCD	    SDA	        A4 (Analog 4)
I2C LCD	    SCL	        A5 (Analog 5)
Buzzer	    (Signal)	Digital Pin 8 (You can use any open digital pin)
Buzzer	    GND	GND

# Arduino Code with C4 Ticking & BOOM

This code uses the millis() function for non-blocking timing, which is the best practice for accurate countdowns and simultaneously controlling the buzzer's ticking.