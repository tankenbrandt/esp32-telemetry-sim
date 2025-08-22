# ESP32 Telemetry Simulation

This project is a **telemetry system** built with **ESP32 microcontrollers** and **LoRa transceivers**. It transmits real sensor data (temperature, pressure, humidity, acceleration, and gyroscope) from a transmitter to a receiver. The receiver displays live data on an OLED screen and can be expanded for logging or integration with other systems. The goal is to demonstrate a simple flight computer workflow using embedded hardware.

---

## Features
- **ESP32-based transmitter and receiver** setup  
- **LoRa wireless communication** between transmitter and receiver  
- **BME280** sensor for temperature, pressure, and humidity  
- **MPU6050** IMU for acceleration and gyroscope data  
- **OLED display** on the receiver for live data output  
- Code written fully in the **Arduino IDE** using C/C++  
- Modular design for expansion (logging, dashboards, additional sensors)  

---

## System Overview

[BME280 + MPU6050 Sensors] → [ESP32 Transmitter + LoRa]
↓ (LoRa wireless)
[ESP32 Receiver + LoRa] → [OLED Display]

## Repository Structure

esp32-telemetry-sim/
├── src/
│ ├── transmitter/
│ │ └── telemetry-transmitter.ino
│ └── receiver/
│ └── telemetry-receiver.ino
├── docs/
│ ├── diagram.png
│ ├── demo.gif
├── README.md
└── LICENSE

