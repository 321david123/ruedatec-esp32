# 🦽 RuedaTec ESP32 Bluetooth Control System

This repository contains the firmware for the **RuedaTec Smart Wheelchair**, developed to improve mobility and accessibility through low-cost, high-impact technology. It was showcased in **Invention Convention Americas 2023**, earning **2nd place internationally**.
After the beginning of 2024 we stopped the development, but we got another improved version locally literally in a computer in Mexico that I cant access right now, but this code was relatively updated.
The project consists of a Bluetooth-controlled electric wheelchair system, built using two ESP32 microcontrollers, and enhanced with AI-driven statistics for battery health and inclination monitoring.


## 📡 System Overview

The system is divided into two ESP32 boards:

### ✅ ESP32 #1 — **Controller Unit**
- Acts as the **remote control**.
- Sends commands via **Bluetooth** to the main wheelchair ESP32.
- Joystick behavior or mobile app input.
- Can optionally receive commands from a **custom Android app** over Bluetooth.

### ✅ ESP32 #2 — **Wheelchair Drive Unit**
- Receives commands from ESP32 #1 via Bluetooth.
- Controls the **main motors** and brakes,.
- Supports forward/reverse motion. Turning is in o.

This modular design improves flexibility: the chair can be controlled either by a physical controller (ESP32 #1) or directly from a smartphone.

---

## 🛠️ Hardware Used
- 2 × **ESP32 Dev Modules**
- 2 × **Motors** (with H-bridge motor drivers)
- 1/2 x Motor driver (L298N)
- 1/2 x H-bridge 
- Power supply for motors and ESP32s (it was a big battery)

---

## 🔗 Communication
- Bluetooth Classic via `BluetoothSerial` library.
- ESP32 #1 sends single-character commands to ESP32 #2 (e.g., `'F'` for forward, `'B'` for backward, `'0’–'9'` for speed levels).

---

## 📁 File Structure

| File                  | Description                          |
|-----------------------|--------------------------------------|
| `esp32_controller.ino`| Code for **ESP32 #1 (Controller Unit)** |
| `esp32_drive_unit.ino`| Code for **ESP32 #2 (Drive Unit)**     |

---

## 🧠 Command Reference

| Command | Description                    | Used By |
|---------|--------------------------------|---------|
| `F`     | Move forward                   | Both    |
| `B`     | Move backward                  | Both    |
| `L`     | Turn left                      | Drive Unit | / turning commands are being worked on since we don't have time anymore for it / computer in Mexico
| `R`     | Turn right                     | Drive Unit | / turning commands are being worked on since we don't have time anymore for it
| `S`     | Stop movement                  | Both    |
| `P`     | Pause / brake                  | Controller |
| `W/w`   | Enable/disable brake           | Controller |
| `X/x`   | Engage/disengage extra stop    | Controller |
| `0–9`   | Set speed (0 = stop, 9 = max)  | Both    |

---

## 💬 Tech Stack
- Language: **C++ (Arduino)**
- Frameworks: **Arduino Core for ESP32**
- Communication: **BluetoothSerial**
- AI Modules: **Battery trend prediction & inclination analysis (Hackathon version)**

---

## 📸 Mobile App Integration
A companion Android app allows users to control the wheelchair directly via Bluetooth. Control can switch seamlessly between the mobile app and physical controller.

---

## 🏆 Awards & Recognition

- 🥉 **Third Place – State Innovation Competition**, Guanajuato, Mexico 🇲🇽  
- 🏆 **Winner – Hackathon Challenge**, where we enhanced the system with **AI-powered statistics** to analyze:
  - Battery performance and degradation
  - Inclination data and safety alerts (power change)
- 🥈 **Second Place – Invention Convention Americas 2023**

---

## 🚀 Future Improvements
- Integration with GPS and obstacle detection.
- OTA firmware updates via Wi-Fi.
- Full mobile app release with customizable controls.

---

## 🌐 Live Project Website  
Visit: [ruedatec.com](https://ruedatec.com)

---
## 🤝 Contact

For inquiries, support, or collaboration:  
📧 **[soporte@ruedatec.com](mailto:soporte@ruedatec.com)**  
