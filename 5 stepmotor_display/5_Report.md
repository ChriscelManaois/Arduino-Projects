# Arduino Stepper Motor with ULN2003 Driver and 16x2 I2C LCD

## ⚙️ Project Overview

This project demonstrates precise control over a **28BYJ-48 unipolar stepper motor** using an **Arduino Uno** and a **ULN2003 motor driver**. A **16x2 I2C LCD** is used to display the motor's current status and movement direction in real-time.

---

## 🔩 Materials Used

| Component | Quantity | Notes |
| :--- | :--- | :--- |
| **Arduino Uno** | 1 | Microcontroller |
| **28BYJ-48 Stepper Motor (5V)** | 1 | Geared unipolar motor |
| **ULN2003 Motor Driver Board** | 1 | Drives the motor coils |
| **16x2 LCD with I2C Backpack** | 1 | For serial output display |
| **External Power Supply (5V, 1A+)** | 1 | **Required** for motor power |
| **Jumper Wires** | ~10 | For connections |

---

## 🔌 Wiring and Connections

**⚠️ IMPORTANT:** The motor must be powered by a separate **5V supply** connected to the ULN2003 VCC, **NOT** the Arduino's 5V pin. A **Common Ground** must be established between the Arduino, ULN2003, LCD, and External Power Supply.

### 1. Motor to Driver (ULN2003)

| ULN2003 Driver Pin | Arduino Pin | Function |
| :--- | :--- | :--- |
| **IN1** | D8 | Coil Control Signal 1 |
| **IN2** | D9 | Coil Control Signal 2 |
| **IN3** | D10 | Coil Control Signal 3 |
| **IN4** | D11 | Coil Control Signal 4 |
| **Motor Port** | N/A | Stepper motor cable plugs directly in. |

### 2. I2C LCD to Arduino

| LCD I2C Pin | Arduino Pin (Uno) | Function |
| :--- | :--- | :--- |
| **SDA** | A4 | I2C Data Line |
| **SCL** | A5 | I2C Clock Line |
| **VCC** | 5V | LCD Power (Low Current) |
| **GND** | GND | Common Ground |

### 3. Power Connections

| Component | Connection | Notes |
| :--- | :--- | :--- |
| **ULN2003 VCC** | **+5V** from External Power Supply | Supplies current to the motor coils. |
| **Arduino GND** | **GND** from External Power Supply | Establishes Common Ground. |

---

## 💻 Program Description (Arduino Sketch)

The sketch uses the built-in **`Stepper.h`** library for motor control and the **`LiquidCrystal_I2C`** library for the display.

### Libraries Used
* **`Stepper.h`** (Standard Arduino Library)
* **`Wire.h`** (Standard Arduino Library, for I2C)
* **`LiquidCrystal_I2C.h`** (Must be installed via Library Manager)

### Key Program Functions

1.  **Initialization (`setup()`):**
    * The **LCD** is initialized and a brief "Ready" message is displayed.
    * The motor object (`myStepper`) is created with **2048 steps** per revolution (the effective steps for the geared 28BYJ-48).
    * The motor speed is set to **10 RPM** (`myStepper.setSpeed(10)`).
2.  **Loop Execution (`loop()`):**
    * **Clockwise Movement:** The motor moves one full revolution using `myStepper.step(stepsPerRevolution)`.
        * The **LCD** displays: `Direction: CW ->` and `Status: Moving`.
    * **Pause:** A 1000ms (`delay(1000)`) pause occurs.
    * **Counter-Clockwise Movement:** The motor reverses for one revolution using `myStepper.step(-stepsPerRevolution)`.
        * The **LCD** displays: `Direction: <- CCW` and `Status: Moving`.
    * **Pause:** A final 1000ms pause occurs before the cycle repeats.

The program effectively cycles the motor between one full rotation clockwise and one full rotation counter-clockwise, providing visual confirmation on the LCD at each stage.