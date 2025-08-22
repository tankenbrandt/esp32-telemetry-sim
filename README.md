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
--> (LoRa wireless) -->
[ESP32 Receiver + LoRa] → [OLED Display]


## Fritzing Diagram & Key

- Top breadboard is transmitter, bottom is receiver
- Red wires for power, Black for ground
- Green and Blue wires for SCL and SDA (I2C communication)
- Orange for SPI LoRa communication

<img width="622" height="610" alt="Screenshot 2025-08-22 at 11 08 21 AM" src="https://github.com/user-attachments/assets/3423a948-cd58-4df8-b0cf-c4ad9769c45e" />


