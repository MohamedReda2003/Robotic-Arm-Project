# 🦾 Robotic Arm — Pick & Place Controller

> A PS3-controller-driven robotic arm built on the ESP32, capable of smooth pick-and-place operations using multiple servo motors managed through the PCA9685 PWM driver.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Circuit Overview](#circuit-overview)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

This project implements a fully functional **pick-and-place robotic arm** controlled wirelessly via a **PS3 DualShock controller**. The ESP32 microcontroller serves as the brain of the system, communicating with the controller over Bluetooth and translating joystick/button inputs into precise servo movements coordinated through a **PCA9685 16-channel PWM driver**.

The repository contains 4 development iterations of the same core system, each representing a refined and improved version of the codebase.

---

## ✨ Features

- 🎮 **Wireless PS3 Controller Support** — Full Bluetooth integration using the ESP32's built-in BT stack
- 🤖 **Multi-Servo Coordination** — Controls multiple servo motors simultaneously via the PCA9685 driver
- 📦 **Pick & Place Operations** — Precise arm movements for gripping, lifting, moving, and releasing objects
- 🔄 **Iterative Development** — 4 progressive code versions showcasing improvements over time
- ⚡ **Battery-Powered** — Fully portable and untethered from a fixed power source

---

## 🛠️ Hardware Requirements

| Component | Description |
|---|---|
| **ESP32** | Main microcontroller (with built-in Wi-Fi & Bluetooth) |
| **PS3 DualShock Controller** | Wireless input device connected via Bluetooth |
| **PCA9685** | 16-channel 12-bit PWM/Servo driver (I2C) |
| **Servo Motors** | Multiple servos for arm joints and gripper |
| **Battery Pack** | Power supply for servos and ESP32 |
| **Wires & Chassis** | Jumper wires, breadboard, and the physical arm frame |

---

## 📁 Project Structure

```
Robotic-Arm-Project/
│
├── robotic_arm/           # Version 1 — Initial implementation
│   └── robotic_arm.ino
│
├── robotic_arm_2/         # Version 2 — First update & improvements
│   └── robotic_arm_2.ino
│
├── robotic_arm_3/         # Version 3 — Further refinements
│   └── robotic_arm_3.ino
│
├── robotic_arm_4/         # Version 4 — Latest stable version
│   └── robotic_arm_4.ino
│
└── README.md
```

> 💡 **Tip:** It is recommended to use **`robotic_arm_4`** as it contains the most up-to-date and stable code.

---

## 🚀 Getting Started

### Prerequisites

Before uploading the code, make sure you have the following installed:

- [Arduino IDE](https://www.arduino.cc/en/software) (v2.x recommended)
- **ESP32 Board Package** — Add this URL in Arduino IDE > Preferences > Additional Board Manager URLs:
  ```
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  ```
- Required Libraries (install via Arduino Library Manager):
  - `PS3Controller` — for PS3 Bluetooth communication
  - `Adafruit PWM Servo Driver` — for PCA9685
  - `Wire` — for I2C communication (built-in)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/MohamedReda2003/Robotic-Arm-Project.git
   cd Robotic-Arm-Project
   ```

2. **Open the latest version** in Arduino IDE
   ```
   robotic_arm_4/robotic_arm_4.ino
   ```

3. **Select your board** — Go to `Tools > Board > ESP32 Arduino > ESP32 Dev Module`

4. **Connect your ESP32** via USB and select the correct COM port under `Tools > Port`

5. **Upload the sketch** by clicking the ➡️ Upload button

---

## 🎮 Usage

1. Power on the robotic arm (connect the battery pack)
2. The ESP32 will start advertising Bluetooth — **pair your PS3 controller** by pressing the PS button
3. Once connected, use the joysticks and buttons to control the arm:

| Input | Action |
|---|---|
| Left Joystick (Y-axis) | Base rotation |
| Right Joystick (Y-axis) | Shoulder joint |
| Right Joystick (X-axis) | Elbow joint |
| L2 / R2 Triggers | Wrist movement |
| Cross (✕) / Circle (○) | Open / Close gripper |

> ⚠️ Make sure servo power and ESP32 power are properly separated to avoid brownouts.

---

## 🔌 Circuit Overview

```
PS3 Controller  ──[Bluetooth]──►  ESP32
                                    │
                               I2C (SDA/SCL)
                                    │
                                 PCA9685
                                 /  |  \
                           Servo1 Servo2 Servo3 ...
                                    │
                              Battery Pack
```

- **PCA9685 SDA** → ESP32 GPIO 21
- **PCA9685 SCL** → ESP32 GPIO 22
- **PCA9685 VCC** → 3.3V
- **Servo Power (V+)** → External Battery (5–6V recommended)
- **Common GND** → All components share ground

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome!

1. Fork the repository
2. Create your feature branch: `git checkout -b feature/my-improvement`
3. Commit your changes: `git commit -m "Add my improvement"`
4. Push to the branch: `git push origin feature/my-improvement`
5. Open a Pull Request

---


<div align="center">

Made with ❤️ by [Mohamed Reda](https://github.com/MohamedReda2003)

</div>
