# 👏 Clap Switch (Sound-Activated LED)

## Project Overview

This project implements a basic sound-activated switch using an Arduino and a sound sensor module. The circuit acts as a **toggle switch**: the first clap turns the LED **ON**, and the second clap turns the LED **OFF**. The code includes logic to filter out noise and ensure reliable switching.

***

## 📦 Materials Used (Required Components)

| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | 1 | Arduino Uno |
| **Sensor** | 1 | Sound Sensor Module |
| **Output** | 1 | LED (Light Emitting Diode) |
| **Resistor** | 1 | $220 \Omega$ Resistor (Current limiter for LED) |
| **Jumper Wires** | Many | For connections |
| **Breadboard** | 1 | For cleaner wiring (Optional) |

***

## 🔌 Wiring Connections

### 1. Sound Sensor Module

The sound sensor's digital output (D0) is used to detect when a sound threshold (clapping) is met.

| Sensor Pin | Connect to Arduino Uno Pin | Purpose |
| :--- | :--- | :--- |
| **VCC** | **5V** | Power |
| **GND** | **GND** | Ground |
| **D0** (Digital Out) | **Digital Pin 2** | Sound Detection Signal (Input) |

### 2. LED Output Circuit

The LED is connected to a digital pin to be controlled by the program.

| LED/Resistor | Connect to Arduino Uno Pin | Purpose |
| :--- | :--- | :--- |
| LED Anode (Longer Leg) | **Digital Pin 13** | LED Control Signal (Output) |
| LED Cathode (Shorter Leg) | $\mathbf{220 \Omega}$ Resistor | Current Limiting |
| Resistor (other end) | **GND** | Ground |

***

## 💻 Program Functionality: Clap Switch Logic

The Arduino code implements a **State Change Detection** logic to ensure a single clap registers as a single event, ignoring noise spikes.

### Key Logic:

1.  **Input Reading:** The code continuously reads the digital state of the Sound Sensor (Pin 2). When a loud sound (like a clap) is detected, the sensor's D0 pin briefly goes **LOW**.
2.  **Toggle Mechanism:**
    * The system maintains a boolean variable (`ledState`) to track the current state of the LED (ON or OFF).
    * When a valid clap is detected, the `ledState` is inverted (e.g., if it was `false`, it becomes `true`).
3.  **Noise Filtering (Debounce):**
    * A primary problem with switches/sensors is **"bouncing"** (multiple signals from one physical event). The code tracks the `lastClapTime`.
    * After a clap is registered, the code ignores all further sensor input for a short duration (e.g., 200ms or 500ms) defined by a `debounceDelay`. This ensures the LED is only toggled once per intentional clap, not by the residual noise.
4.  **Output Control:**
    * The `ledState` variable is used to directly control the LED on Pin 13, turning it **HIGH** (ON) or **LOW** (OFF).

### In essence:

* **Clap 1:** Sensor detects sound $\rightarrow$ Logic confirms it's a new clap $\rightarrow$ `ledState` is set to **ON**.
* **Clap 2:** Sensor detects sound $\rightarrow$ Logic confirms it's a new clap $\rightarrow$ `ledState` is set to **OFF**.