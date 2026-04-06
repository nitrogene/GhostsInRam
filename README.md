# Project Name (TBD)

## 🧭 Overview

This project is a **modular 8-bit computer development and emulation framework** built with Qt6 and C++.

Its goal is to allow developers to define and emulate vintage 8-bit systems (such as the Oric Atmos) using a **plugin-based architecture**, where each hardware component (CPU, memory, IO, etc.) is implemented as a Qt plugin.

---

## 🎯 Objectives

* Provide a flexible framework to describe 8-bit machines via configuration files
* Enable dynamic loading of hardware components through plugins
* Offer a Qt-based UI for interaction and configuration
* Encourage clean abstractions for hardware emulation (CPU, memory bus, peripherals)

---

## 🧱 Architecture Summary

* Core application initializes a Qt UI
* User loads a `.ini` configuration file
* The configuration defines the target machine (e.g., Oric Atmos)
* Required hardware components are resolved via Qt plugins
* Core interfaces ensure compatibility between components

---

## ⚙️ Technologies

* **Language:** C++
* **Framework:** Qt6
* **Build system:** CMake
* **Toolchain setup:** PowerShell (`build.ps1`)

---

## 🚀 Getting Started

### 1. Setup toolchain

Run the provided script from the root directory:

```powershell
./build.ps1
```

To add additional Qt modules, modify this script accordingly.

---

### 2. Project structure setup

Ensure the following files exist at the root:

* `CMakeLists.txt`
* `main.cpp`

---

### 3. Build the project

(Details to be completed depending on your CMake configuration)

---

## 📁 Project Structure

```
/project
│
├── build.ps1              # Toolchain setup script
├── CMakeLists.txt         # Build configuration
├── main.cpp               # Application entry point
│
├── core/                  # Core application logic
│   ├── UI (Qt window)
│   ├── Plugin loader
│   └── Hardware abstractions
│
├── plugins/               # Hardware component plugins
│   ├── cpu/
│   ├── memory/
│   ├── io/
│   └── ...
```

---

## 🧩 Core Concepts

### Configuration-driven emulation

The emulator is configured via `.ini` files.

Example (Oric Atmos):

```
CPU=R6502AP
MEMORY=HCS10017
IO=SYS6522A
```

---

### Plugin-based hardware

Each hardware component must be implemented as a Qt plugin.

The core application:

* Loads required plugins dynamically
* Verifies that all required components are available
* Connects components through defined interfaces

---

### Hardware Abstractions

The core defines interfaces such as:

* `ICPU`
* `IMemoryBus`
* (others to be defined)

These ensure consistency and interoperability between plugins.

---

## 🧠 Design Principles

* Strict separation between core and hardware implementation
* Plugin-driven extensibility
* Configuration over hardcoding
* Emphasis on clean, testable abstractions

---

## ⚠️ Constraints

* All hardware components must be provided via plugins
* The core must validate required components before execution
* Interfaces must remain stable to avoid plugin breakage

---

## 🔮 Roadmap (TODO)

* Define full interface set (CPU, memory, IO, etc.)
* Implement plugin loading system
* Add Oric Atmos reference configuration
* Improve build & run workflow
* Add debugging tools for emulation

---

## 🤝 Contributing

(To be defined)
