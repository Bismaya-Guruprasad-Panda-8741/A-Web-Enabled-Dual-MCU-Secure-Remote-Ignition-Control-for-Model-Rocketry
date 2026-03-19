# A-Web-Enabled-Dual-MCU-Secure-Remote-Ignition-Control-for-Model-Rocketry
🚀 Dual-MCU rocket launch control using ESP32 &amp; Arduino UNO. 📡 WiFi web dashboard for remote ignition. ⏱️ Precise countdown &amp; PWM fuse trigger. 🔒 Dual authentication &amp; real-time monitoring. ⚡ #ESP32 #Arduino #IoT #Rocketry #EmbeddedSystems #ModelRocketry #OpenSource #RemoteControl #PWM
...
...
...
...
# 🚀 Stellar Ignition System (SIS)

> **A Web-Enabled Dual-Microcontroller Architecture for Secure and Remote Ignition Control in Model Rocketry**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/)
[![Platform: Arduino UNO](https://img.shields.io/badge/Platform-Arduino%20UNO-teal.svg)](https://www.arduino.cc/)
[![Institution: DRIEMS University](https://img.shields.io/badge/Institution-DRIEMS%20University-red.svg)](https://driems.ac.in/)

---

## 📖 Overview

The **Stellar Ignition System (SIS)** is a dual-microcontroller rocket launch control solution designed to ensure **secure, precise, and efficient ignition** of model rockets and fireworks. It separates communication concerns from real-time control tasks across two dedicated microcontrollers — an **ESP32** and an **Arduino UNO** — to maximise reliability and safety.

| Controller | Role |
|---|---|
| **ESP32** | WiFi Access Point · Web Server · Launch Control API · Safety Logic |
| **Arduino UNO** | Countdown Timer · Buzzer Control · Fuse PWM Trigger |

The operator connects any phone, tablet, or laptop to the ESP32's WiFi access point and controls the entire launch from a browser — no additional apps required.

---

## ✨ Features

- **Web-based dashboard** — responsive, real-time launch control UI served directly from the ESP32
- **Dual-microcontroller safety** — communication and ignition run independently; network delays cannot affect the countdown
- **Dual authentication** — system must be explicitly armed before a launch command is accepted
- **Three-phase countdown** — Phase 1 (T-10→T-6), Phase 2 (T-5→T-1), Phase 3 (rapid pre-ignition beeps)
- **PWM fuse trigger** — 100 % duty-cycle 1 kHz PWM on Arduino pin 9 for reliable fuse ignition
- **Audible alerts** — buzzer tones escalate in frequency as countdown progresses
- **Real-time status polling** — dashboard updates every second (system state, uptime, launch count, connected clients)
- **Heartbeat LED** — ESP32 blinks every 500 ms to confirm the system is alive
- **WPA2-protected AP** — offline access point; no internet dependency during operation
- **INPUT_PULLUP trigger** — eliminates false triggers due to floating pins

---

## 🛒 Hardware Requirements

| Component | Quantity |
|---|---|
| ESP32 Development Board (WROOM-32 / DevKit) | 1 |
| Arduino UNO | 1 |
| Piezo Buzzer (5 V) | 1 |
| LED (green) — heartbeat | 1 |
| LED (red/green) — armed/disarmed status | 1 |
| 330 Ω resistors (for LEDs) | 2 |
| NPN BJT transistor (e.g., 2N2222 / BC547) + base resistor | 1 |
| Ignition fuse / e-match | 1 |
| Jumper wires, breadboard / PCB | — |
| 5 V USB power supplies | 2 |

---

## 🔌 Wiring / Pin Connections

### ESP32 Pin Map

| GPIO | Mode | Function |
|---|---|---|
| GPIO 4 | OUTPUT | Trigger pulse → Arduino pin 7 |
| GPIO 16 | OUTPUT | Heartbeat LED (blinks 2 Hz) |
| GPIO 17 | OUTPUT | System LED (HIGH = Armed) |

### Arduino UNO Pin Map

| Pin | Mode | Function |
|---|---|---|
| 7 | INPUT_PULLUP | Receives LOW trigger from ESP32 GPIO 4 |
| 9 | PWM OUTPUT | Ignition fuse via BJT driver circuit |
| 13 | OUTPUT | Buzzer — countdown tones & launch alarm |

### Connection Diagram (text)

```
ESP32 GPIO 4  ──────────────────────── Arduino Pin 7
ESP32 GND     ──────────────────────── Arduino GND
Arduino Pin 9 ── Base Resistor ── BJT Base
                                  BJT Collector ── Fuse ── +5V
                                  BJT Emitter  ── GND
Arduino Pin 13 ─────────────────────── Buzzer (+)
GND ────────────────────────────────── Buzzer (-)
```

> ⚠️ **Safety note:** Always use a transistor/MOSFET driver between the Arduino PWM pin and the ignition fuse. Never connect a fuse directly to a microcontroller GPIO.

---

## 💻 Software Dependencies

### ESP32 (Arduino IDE)

| Library | Install via |
|---|---|
| `WiFi.h` | Built-in (ESP32 board package) |
| `WebServer.h` | Built-in (ESP32 board package) |
| `ArduinoJson` v6 | Arduino Library Manager |
| `SPIFFS.h` | Built-in (ESP32 board package) |

**Board package URL** (add to Arduino IDE → Preferences → Additional Board Manager URLs):
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

### Arduino UNO

No external libraries required — uses built-in `tone()` and `analogWrite()`.

---

## 🚀 Setup & Installation

### 1. Clone the Repository

```bash
git clone https://github.com/<Bismaya-Guruprasad-Panda-8741>/stellar-ignition-system.git
cd stellar-ignition-system
```

### 2. Flash the ESP32

1. Open `esp32/esp32_launch_controller.ino` in Arduino IDE.
2. Select board: **ESP32 Dev Module**.
3. Install required libraries (see above).
4. Set Upload Speed to **115200**.
5. Click **Upload**.

### 3. Flash the Arduino UNO

1. Open `arduino/arduino_ignition_controller.ino` in Arduino IDE.
2. Select board: **Arduino UNO**.
3. Select the correct COM port.
4. Click **Upload**.

### 4. Power & Connect

1. Power both boards via USB (use separate supplies for the ignition circuit).
2. On your phone/laptop, connect to WiFi: **`Launch-Control-AP`** | Password: **`sis@2025`**
3. Open a browser and navigate to: **`http://192.168.4.1`**

---

## 🖥️ Using the Dashboard

| Action | Steps |
|---|---|
| **Arm** | Click **Arm System** → system LED turns ON |
| **Launch** | Click **⚠️ INITIATE LAUNCH SEQUENCE** → confirm dialog → Arduino begins countdown |
| **Disarm** | Click **Disarm System** → confirm dialog → launch button is disabled |
| **Monitor** | Status cards update every 1 second (uptime, clients, launches, last launch time) |
| **System Log** | Live log panel shows all operator actions and system events |

---

## 📡 API Reference

The ESP32 exposes a REST-like HTTP API over the local access point:

| Method | Endpoint | Description |
|---|---|---|
| `GET` | `/api/status` | Returns system JSON (armed, launching, uptime, clients, launch count) |
| `POST` | `/api/launch` | Triggers ignition sequence (requires system to be armed) |
| `POST` | `/api/arm` | Arms the launch system |
| `POST` | `/api/disarm` | Disarms the launch system |

**Example status response:**
```json
{
  "armed": true,
  "launching": false,
  "clients": 1,
  "totalLaunches": 2,
  "uptime": "00:12:34",
  "lastLaunch": "45s ago",
  "signalStrength": "Excellent"
}
```

---

## ⏱️ Launch Sequence Timeline

```
T-10  ──  Phase 1 start  (800 Hz beep, 1 s interval)
T-9
T-8
T-7
T-6
T-5  ──  Phase 2 start  (1200 Hz beep, 0.6 s interval)
T-4
T-3
T-2
T-1
T-0  ──  Phase 3: 5× rapid 1500 Hz beeps
         ↓
      🔥 IGNITION — 2000 Hz continuous tone + 100% PWM for 3 s
         ↓
      Fuse deactivated. System returns to standby.
```

---

## 🔒 Safety Architecture

| Layer | Mechanism |
|---|---|
| **Software** | Arm/Disarm state machine; confirmation dialogs; launch-in-progress guard |
| **Hardware** | INPUT_PULLUP prevents floating-pin false triggers; separate power domains |
| **Network** | WPA2-protected offline access point (no internet dependency) |
| **Timing** | Arduino operates autonomously after trigger; network issues cannot abort countdown |
| **PWM** | Fuse fires only after Launch Control API validation; fixed 3 s duration prevents overheating |

---

## 📊 System Statistics

| Metric | Value |
|---|---|
| Trigger success rate | 100 % |
| False trigger rate | ~0 % (INPUT_PULLUP) |
| Missed trigger rate | < 1 % |
| Status poll rate | 60 times/min |
| ESP32 GPIO utilisation | 10 % (3 of 30 pins) |
| Arduino GPIO utilisation | 21.4 % (3 of 14 pins) |
| Combined pin utilisation | 13.6 % |
| PWM frequency | 1 kHz |
| PWM duty cycle (ignition) | 100 % |
| Ignition pulse duration | 3 seconds |

---

## 🔭 Future Scope

- **Telemetry integration** — wind speed, temperature, altitude sensors
- **Multi-rocket coordination** — networked launch of multiple rockets simultaneously
- **Mesh networking** — extended range via ESP-NOW or LoRa
- **Machine learning anomaly detection** — preemptive abort on predicted system failure
- **GSM/LTE module** — operate beyond WiFi range
- **Mobile app** — dedicated Android/iOS launch controller

---

## 📁 Repository Structure

```
stellar-ignition-system/
│
├── esp32/
│   └── esp32_launch_controller.ino     # ESP32 firmware
│
├── arduino/
│   └── arduino_ignition_controller.ino # Arduino UNO firmware
│
├── docs/
│   └── images/                         # Schematics & screenshots
│
└── README.md
```

---

## 👨‍💻 Authors

| Name | Role |
|---|---|
| **Bismaya Guruprasad Panda** | Arduino Firmware & Hardware Integration |
| **Debasish Nayak** | System Design & ESP32 Firmware |

**Institution:** DRIEMS POLYTECHNIC  
**Submitted:** November 2025

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgements

- Espressif Systems for the ESP32 platform
- Arduino community for open-source tooling
- DRIEMS University for project support

---

> ⚠️ **Disclaimer:** This system is intended for educational and experimental use with model rockets and supervised pyrotechnic devices only. Always follow local laws and safety regulations regarding rocketry and pyrotechnics. The authors accept no liability for misuse.
