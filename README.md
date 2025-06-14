# UART Communication Game with Arduino

## 📖 Project Overview

This project demonstrates UART (Universal Asynchronous Receiver-Transmitter) communication between two Arduino boards. Developed as part of the Microprocessors and Microcontrollers course, it implements a simple interactive game where each Arduino controls a character displayed on an LCD screen. Players can move their characters and shoot bullets, with all interactions communicated via UART.

> **Note:** The current codebase is **incomplete** due to the nature of this project. Contributions and improvements are welcome.

---

## 🕹️ Game Explanation

The game involves two players, each controlling a character on their respective LCD screens. The core functionalities include:

- Displaying player positions on the LCD.
- Handling bullet shooting and erasure.
- Communicating moves and actions via UART between the two Arduino boards.

The game logic includes character display, bullet tracking, and synchronization between devices.

---

## 🔌 Schematic View

The following schematic illustrates the hardware setup required:

- **Two Arduino boards** connected via UART (TX/RX).
- **Two 4x4 Keypad** connected on each Arduino.
- **LCD module** (16x2) connected to each Arduino using standard 4-bit mode.
- **Two Push buttons** for player input (to starting game).
- **Resistors and wiring** for button debouncing and UART connections.


![Schematic Diagram](https://github.com/user-attachments/assets/e2087db9-2808-4f77-9b50-a85e8f539992)


---

## ⚠️ Project Status

- ✅ UART communication basic structure implemented.
- ✅ LCD display logic for players and bullets.
- ✅ Input handling via buttons not fully implemented.
- ❌ Bullet collision detection incomplete.
- ❌ Attack hit incomplete.
- ❌ Game win condition not yet added.

> This project is a **work in progress**. Check the [Issues](link-to-issues) for current development tasks.

---

## 📂 File Structure

- `ArduinoA.cpp` – Sender Microcontroller.
- `ArduinoB.cpp` – Principal Microcontroller.
- `README.md` – Project documentation.
- `schematics.pdf` – Contains all schematic diagrams in PDF format:
---
