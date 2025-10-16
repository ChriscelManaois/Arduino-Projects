# Arduino Joystick to Servo Control

## ⚙️ Project Overview

This project reads the position of the **X-axis** on an analog joystick and uses that value to precisely control the angular position of a **micro servo motor (SG90)**. This allows for direct, analog control of the servo's movement from the joystick's physical displacement.

---

## 🔩 Materials Used

| Component | Quantity | Notes |
| :--- | :--- | :--- |
| **Arduino Uno** | 1 | Microcontroller |
| **SG90 Servo Motor** | 1 | Micro servo motor (Signal wire: Orange/Yellow) |
| **Analog Joystick Module** | 1 | Used for input control |
| **Jumper Wires** | ~5 | For connections |

---

## 🔌 Wiring and Connections

The circuit connects the servo and joystick to the Arduino's power, ground, and specific signal pins.

### 1. Servo Motor (SG90) Connections

| Servo Wire | Arduino Pin | Function |
| :--- | :--- | :--- |
| **Signal (Orange/Yellow)** | **Digital Pin 9** | PWM control signal for the servo |
| **VCC (Red)** | **5V** | Power supply for the servo |
| **GND (Brown/Black)** | **GND** | Ground |

### 2. Joystick Connections

| Joystick Pin | Arduino Pin | Function |
| :--- | :--- | :--- |
| **VRx (X-axis)** | **Analog Pin A0** | Reads the analog position of the X-axis |
| **VCC** | **5V** | Power supply for the joystick |
| **GND** | **GND** | Ground |

---

## 💻 Program Description (Arduino Sketch)

The sketch uses the built-in **`Servo.h`** library to interface with the motor.

### Libraries Used
* **`Servo.h`** (Standard Arduino Library)

### Key Program Functions

1.  **Initialization (`setup()`):**
    * A `Servo` object (`myservo`) is created and attached to **Digital Pin 9**.
    * Serial communication is started at 9600 baud for optional debugging.

2.  **Loop Execution (`loop()`):**
    * **Read Joystick:** The code reads the raw analog value from the joystick's X-axis via **Analog Pin A0**. This raw value ranges from **0 to 1023**.
    * **Mapping:** The core of the control is the `map()` function:
        * `int servoAngle = map(joyVal, 0, 1023, 0, 180);`
        * This scales the joystick's raw input range (`0` to `1023`) to the servo's standard angular range (`0` to `180` degrees).
    * **Servo Command:** The calculated angle is sent to the servo using `myservo.write(servoAngle)`, commanding it to move to the corresponding physical position.
    * **Stabilization:** A small `delay(15)` is included to give the servo time to move and prevent erratic jittering in the control loop.

The program's outcome is **proportional control** where pushing the joystick all the way one direction moves the servo to **0 degrees**, and pushing it the other way moves the servo to **180 degrees**.