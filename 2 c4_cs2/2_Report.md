# 💣 C4 Countdown Timer Simulation

## Project Overview

This project simulates a cinematic C4 explosive countdown timer using an Arduino Uno and a buzzer for sound effects. It utilizes the **`millis()`** function for non-blocking timing, which ensures the ticking sound is consistent and the LCD update is smooth, making the system highly responsive.

***

## 📦 Materials Used (Required Components)

| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | 1 | Arduino Uno |
| **LCD Display** | 1 | 16x2 LCD with I2C Adapter (For displaying the countdown) |
| **Buzzer** | 1 | Active or Passive Buzzer (Passive recommended for cleaner tones) |
| **Jumper Wires** | Many | For connections |
| **Breadboard** | 1 | For cleaner wiring (Optional) |

***

## 🔌 Wiring Connections

This setup uses the I2C interface for the LCD, significantly reducing the number of required pins.

| Component | Pin Label | Connect to Arduino Uno Pin | Purpose |
| :--- | :--- | :--- | :--- |
| I2C LCD | **GND** | **GND** | Ground |
| I2C LCD | **VCC** | **5V** | Power |
| I2C LCD | **SDA** | **A4** (Analog 4) | I2C Data Line |
| I2C LCD | **SCL** | **A5** (Analog 5) | I2C Clock Line |
| Buzzer | **(Signal)** | **Digital Pin 8** | Tone/Signal Output (Requires a PWM pin for passive buzzer control) |
| Buzzer | **GND** | **GND** | Ground |

***

## 💻 Program Functionality: C4 Ticking & BOOM

The program executes a multi-stage countdown sequence, controlled entirely by non-blocking timers.

### Key Features:

1.  **Non-Blocking Timing (`millis()`):**
    * The code is structured as a State Machine using `millis()` for all timing events. This ensures that the buzzer's ticking does not pause the core countdown logic, and the countdown value is accurate.
    * The main countdown updates once every second (1000 ms).

2.  **C4 Ticking Sound:**
    * A dedicated non-blocking timer controls the buzzer.
    * The buzzer is triggered to produce a brief **"TICK"** sound (using `tone()` and `noTone()`) precisely every 1000 milliseconds to simulate the C4 sound effect.

3.  **LCD Display:**
    * The 16x2 LCD displays the countdown value clearly on one line (e.g., "TIME LEFT: 00:09").
    * A custom message (e.g., "DETONATING IN T-5...") may be displayed on the second line or during the final critical phase.

4.  **Detonation Phase:**
    * When the countdown reaches zero, the system transitions into a final "Detonation" state.
    * The LCD displays a final message (e.g., "B O O M ! ! !").
    * The buzzer is activated with a sustained or complex tone sequence to simulate the "BOOM" sound, concluding the simulation.