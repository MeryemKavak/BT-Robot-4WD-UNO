# BT-Robot-4WD-UNO
# 📡 4WD Bluetooth Controlled Robot

This repository contains the Arduino code for a mobile app-controlled Four-Wheel Drive (4WD) robot project.

## 🌟 Overview

The robot utilizes an **Arduino UNO** paired with an **L298N Motor Driver** and an **HC-05/HC-06 Bluetooth Module** to enable remote control via a smartphone application. The code manages the direction and PWM-based speed of all four motors.

## 🛠️ Hardware Requirements

* Arduino UNO (or compatible board)
* HC-05 or HC-06 Bluetooth Module
* L298N Motor Driver Module
* 4 x DC Motors and Chassis
* Power Supply (Battery)

## 📌 Pin Assignments

The pins defined in the code (for Arduino UNO) are as follows:

| Hardware Component | Arduino Pin | Description |
| :--- | :---: | :--- |
| **L298N** ENA | D9 | Left Motor Speed (PWM) |
| **L298N** ENB | D10 | Right Motor Speed (PWM) |
| **L298N** IN1, IN2 | D7, D6 | Left Motor Direction |
| **L298N** IN3, IN4 | D5, D4 | Right Motor Direction |
| **Bluetooth** RX | D11 | Arduino RX (SoftwareSerial) |
| **Bluetooth** TX | D12 | Arduino TX (SoftwareSerial) |

## ⚙️ Software & Configuration

* **Library:** Uses `SoftwareSerial.h` for reliable communication with the Bluetooth module.
* **Baud Rate:** Set to **9600** (`BLUETOOTH_BAUD`).
* **Default Speed:** Set to **255** (Max PWM value).

## 🕹️ Control Commands

The robot is controlled by sending single-character commands via Bluetooth.

| Command | Function | Speed Value Range (0-255) |
| :---: | :--- | :--- |
| `F` or `f` | **Forward** | Current Speed (`MOTOR_HIZI`) |
| `B` or `b` | **Backward** | Current Speed (`MOTOR_HIZI`) |
| `L` or `l` | **Left** (Pivot) | Current Speed (`MOTOR_HIZI`) |
| `R` or `r` | **Right** (Pivot) | Current Speed (`MOTOR_HIZI`) |
| `S` or `s` | **Stop** | 0 |
| `1` | **Speed 1** | 25 |
| `5` | **Speed 5** | 125 |
| `9` | **Speed 9** | 225 |
| *(Other digits 2, 3, 4, 6, 7, 8)* | **Incremental Speed** | *(Increments of 25)* |

***Note on Speed Command '10':*** *The Arduino code attempts to use '10' for max speed (255), but as the controller reads only a single character at a time, this command will not function correctly. Speed level 9 (`225`) is the highest working numerical speed setting.*

## ✨ Initial Test Sequence

The robot executes a short self-test sequence in the `setup()` function to confirm readiness: Forward -> Backward -> Forward -> Stop, with 500ms delay between movements.
