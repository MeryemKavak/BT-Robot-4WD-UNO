# BT-Robot-4WD-UNO
# 📡 4WD Bluetooth Controlled Robot

[cite_start]This repository contains the Arduino code for a mobile app-controlled Four-Wheel Drive (4WD) robot project[cite: 1].

[cite_start]The project utilizes an **Arduino UNO** [cite: 1][cite_start], an **L298N Motor Driver** [cite: 1][cite_start], and an **HC-05/HC-06 Bluetooth Module** [cite: 1] to allow remote operation via a smartphone application.

## 🛠️ Hardware Requirements

* [cite_start]Arduino UNO (or compatible board) [cite: 1]
* [cite_start]HC-05 or HC-06 Bluetooth Module [cite: 1]
* [cite_start]L298N Motor Driver Module [cite: 1]
* [cite_start]4 x DC Motors and Chassis [cite: 1]
* Power Supply (Battery)

## 📌 Pin Assignments

The pins defined in the code (for Arduino UNO) are as follows:

| Hardware Component | Arduino Pin | Description |
| :--- | :---: | :--- |
| **L298N** ENA | D9 | [cite_start]Left Motor Speed (PWM) [cite: 1, 5] |
| **L298N** ENB | D10 | [cite_start]Right Motor Speed (PWM) [cite: 1, 5] |
| **L298N** IN1, IN2 | D7, D6 | [cite_start]Left Motor Direction [cite: 1] |
| **L298N** IN3, IN4 | D5, D4 | [cite_start]Right Motor Direction [cite: 1, 2] |
| **Bluetooth** RX | D11 | [cite_start]Arduino RX (SoftwareSerial) [cite: 2] |
| **Bluetooth** TX | D12 | [cite_start]Arduino TX (SoftwareSerial) [cite: 2] |

## ⚙️ Software & Configuration

[cite_start]The code uses the `SoftwareSerial.h` library for communication with the Bluetooth module[cite: 1, 4].

* [cite_start]**Default Motor Speed:** Set to 255 (Max) initially (`MOTOR_HIZI = 255`)[cite: 3].
* [cite_start]**Bluetooth Baud Rate:** Set to 9600 (`BLUETOOTH_BAUD`)[cite: 3].

## 🕹️ Control Commands

[cite_start]The robot is controlled by sending single-character commands via Bluetooth[cite: 9, 10]:

| Command | Function | Description |
| :---: | :--- | :--- |
| `F` or `f` | **Forward** | [cite_start]Moves the robot forward[cite: 11, 12]. |
| `B` or `b` | **Backward** | [cite_start]Moves the robot backward[cite: 13, 14]. |
| `L` or `l` | **Left** | [cite_start]Turns the robot left (sharp pivot)[cite: 14, 15]. |
| `R` or `r` | **Right** | [cite_start]Turns the robot right (sharp pivot)[cite: 15, 16]. |
| `S` or `s` | **Stop** | [cite_start]Stops all motor movement[cite: 16, 17]. |
| `1` - `9` | **Speed Level** | [cite_start]Adjusts the speed from 25 to 225[cite: 17, 18, 19]. |
| `10` | **Max Speed** | [cite_start]Sets the speed to 255 (Maximum)[cite: 19]. |

## ✨ Initial Test Sequence

[cite_start]Upon startup (`setup()`), the robot performs a short test sequence[cite: 8]:

1.  [cite_start]Move Forward for 500ms[cite: 8].
2.  [cite_start]Move Backward for 500ms[cite: 8].
3.  [cite_start]Move Forward for 500ms[cite: 8].
4.  [cite_start]Stop[cite: 8, 9].
