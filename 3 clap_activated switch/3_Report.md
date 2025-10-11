# Required Components

1. Arduino Uno
2. 1x Sound Sensor Module
3. 1x LED
4. 1x 220 Ohm Resistor (for the LED)
5. Jumper Wires
6. Breadboard (optional, but makes wiring cleaner)
  
# Arduino Uno Wiring Diagram
-----------------------------
LED/Resistor	→	Arduino Pin
LED Anode (Longer Leg)	→	Digital Pin 13
LED Cathode (Shorter Leg)	→	Resistor
Resistor (other end)	→	GND

# Arduino Code (Clap Switch)

This code uses a simple technique to track the sound events and ignore the "bouncing" or short noise spikes that happen after the main clap.