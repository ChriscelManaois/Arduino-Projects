# 🚦 Pedestrian-Activated Traffic Light System

## Project Overview

This project simulates a standard traffic light intersection with a pedestrian crossing request button. It uses an Arduino to manage the state transitions and an I2C LCD to display the current system status and phase timing. Crucially, the system employs **non-blocking code (`millis()`)** to ensure the button is always responsive, and the car light only changes **after** a minimum safe green time has passed following a request.

***

## 📦 Materials Used (Bill of Materials)

| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | 1 | Arduino Uno (or compatible) |
| **LEDs (Car Traffic)** | 3 | Red, Yellow, Green |
| **LEDs (Pedestrian)** | 2 | Red ("Don't Walk"), Green ("Walk") |
| **Resistors** | 5 | $\approx 220 \Omega$ (Current limiters for LEDs) |
| **Pushbutton** | 1 | Momentary switch (4-pin is common) |
| **LCD Display** | 1 | 16x2 LCD with **I2C Module** |
| **Breadboard** | 1 | For prototyping connections |
| **Jumper Wires** | Many | For connections |

***

## 🔌 Wiring Connections

### 1. Traffic Lights (LEDs)

Each LED Anode (long leg) connects to its respective Arduino Digital Pin, and the Cathode (short leg) connects to **GND** via a $\mathbf{220 \Omega}$ resistor.

| LED (Anode) | Arduino Pin |
| :--- | :--- |
| Car Red | **13** |
| Car Yellow | **12** |
| Car Green | **11** |
| Pedestrian Red | **10** |
| Pedestrian Green | **9** |

### 2. Pedestrian Button

The code uses the Arduino's internal **`INPUT_PULLUP`** resistor, simplifying the wiring to just two connections.

| Button Pin | Arduino Pin |
| :--- | :--- |
| One Side (e.g., Side A) | **2** (Input Pin) |
| Opposite Side (e.g., Side B) | **GND** (Ground) |

*(Note: If using a 4-pin button, ensure the connections are made across the non-connected pairs, typically diagonally or across the breadboard trench.)*

### 3. I2C LCD Display

The I2C module simplifies the connection to only four wires, using the dedicated hardware I2C pins on the Arduino Uno.

| LCD Pin | Arduino Pin |
| :--- | :--- |
| **GND** | **GND** |
| **VCC** | **5V** |
| **SDA** (Data) | **A4** (Analog Pin 4) |
| **SCL** (Clock) | **A5** (Analog Pin 5) |

***

## 💻 Program Functionality

The program operates as a **Finite State Machine (FSM)** managed by the non-blocking `millis()` function, ensuring responsiveness and accuracy.

### Key Logic:

1.  **Initial/Default State (Car Green, Ped Red):**
    * The car light remains **Green** indefinitely.
    * The system constantly checks the button state and the elapsed time.

2.  **Button Press (Request Phase):**
    * When the button is pressed (and the light is currently Green), the **`cross_requested`** flag is set to `true`, and the **`requestTime`** is recorded.
    * The light **does not** immediately change. The LCD updates to show a request has been received.

3.  **Minimum Green Time Enforcement:**
    * The system checks if the time elapsed since the request (`millis() - requestTime`) is greater than or equal to the defined **`GREEN_DURATION`** (e.g., 15 seconds).
    * If the time has **not** elapsed, the light remains Green, ignoring the request until the minimum safe time is guaranteed.

4.  **Traffic Light Cycle (Only on Request + Time Out):**
    * Once the minimum green time is satisfied, the system executes the non-blocking state transition:
        * **Car Green** $\rightarrow$ **Car Yellow** (for `YELLOW_DURATION`)
        * **Car Yellow** $\rightarrow$ **Car Red** (Ped Green/Walk begins for `WALK_DURATION`)
    * After the pedestrian walk time, the system resets to the default **Car Green** state, clearing the `cross_requested` flag and ready to accept a new button press.

### Code Highlights:

* **Non-Blocking:** No `delay()` functions are used in the main state machine, ensuring the button is responsive at all times.
* **State Management:** The `current_state` variable and `switch/case` structure govern the entire light sequence.
* **LCD Feedback:** The `update_lcd_status()` helper function provides real-time information on the light status for both cars and pedestrians.