# 🧱 Architecture

## 🧭 Overview

The project is built around a **modular, plugin-based architecture** designed to emulate 8-bit systems.

The core application is responsible for:

* UI (Qt)
* Configuration loading
* Plugin discovery and validation
* Component orchestration

All hardware components (CPU, memory, IO, etc.) are implemented as **Qt plugins**.

---

## 🧩 High-Level Architecture

```
+----------------------+
|      Qt UI (Core)    |
+----------+-----------+
           |
           v
+----------------------+
| Configuration Loader |
|      (.ini file)     |
+----------+-----------+
           |
           v
+----------------------+
|   Plugin Manager     |
+----------+-----------+
           |
           v
+------------------------------+
| Hardware Components (Plugins)|
|------------------------------|
| CPU | Memory | IO | ...      |
+------------------------------+
           |
           v
+----------------------+
|   Core Interfaces    |
| (ICPU, IMemoryBus…)  |
+----------------------+
```

---

## 📦 Core Module (`/core`)

### Responsibilities

* Initialize Qt application and main window
* Load and parse `.ini` configuration files
* Discover and load Qt plugins
* Validate required hardware components
* Instantiate and connect components
* Provide shared abstractions (interfaces)

---

## 🔌 Plugin System (`/plugins`)

### Structure

Each hardware component is implemented as a Qt plugin.

Example:

```
/plugins
 ├── cpu/
 │    └── R6502AP/
 ├── memory/
 │    └── HCS10017/
 └── io/
      └── SYS6522A/
```

---

### Plugin Requirements

Each plugin must:

* Implement a well-defined interface (e.g., `ICPU`)
* Expose metadata (type, name, compatibility)
* Be loadable via Qt plugin system

---

### Plugin Types

* CPU
* Memory
* IO (e.g., VIA, PIA)
* (Future) Video, Sound, Storage

---

## ⚙️ Configuration System

### `.ini` File Role

Defines the hardware configuration of the emulated machine.

Example (Oric Atmos):

```
CPU=R6502AP
MEMORY=HCS10017
IO=SYS6522A
```

---

### Configuration Flow

1. User loads `.ini` file via UI
2. Core parses configuration
3. Required components are identified
4. Plugin Manager searches matching plugins
5. System validates all components are available
6. Emulation setup is initialized

---

## 🔗 Component Interaction

### Core Interfaces

The system relies on strict abstractions:

* `ICPU`
* `IMemoryBus`
* (future) `IIODevice`, `IVideo`, `IAudio`

---

### Example Interaction Flow

```
CPU <----> Memory Bus <----> Memory
  |
  +----> IO Devices
```

* CPU reads/writes through `IMemoryBus`
* Memory bus dispatches to:

  * RAM / ROM
  * IO-mapped devices

---

## 🧠 Execution Flow

1. Application starts
2. Qt UI is initialized
3. User loads configuration file
4. Plugins are discovered and loaded
5. Interfaces are validated
6. Components are instantiated
7. Components are connected together
8. Emulation loop starts (future step)

---

## 🧱 Abstraction Layer

### Goals

* Decouple core from hardware implementations
* Allow interchangeable components
* Ensure compatibility via contracts

---

### Example Interfaces

```cpp
class ICPU {
public:
    virtual void reset() = 0;
    virtual void step() = 0;
    virtual void connectMemory(IMemoryBus*) = 0;
};
```

---

## ⚠️ Constraints & Rules

* Core must never depend on concrete implementations
* All hardware must be provided via plugins
* Interfaces must remain stable
* Plugins must declare compatibility explicitly
* Configuration must be validated before execution

---

## 🔄 Extensibility

Adding a new component:

1. Implement interface (e.g., `ICPU`)
2. Package as Qt plugin
3. Place in `/plugins`
4. Reference in `.ini`

No core modification required.

---

## 🧪 Testing Strategy (Planned)

* Unit tests for interfaces
* Plugin validation tests
* Configuration validation tests
* Reference machine tests (e.g., Oric Atmos)

---

## 🔮 Future Improvements

* Emulation scheduler (cycle-accurate timing)
* Debugging tools (step, breakpoints)
* Visualization (memory, registers)
* Plugin dependency management
* Hot-reload of plugins (optional)

---

## 🧠 Notes for AI Assistants

* Do not bypass interfaces
* Always use abstractions (`ICPU`, `IMemoryBus`, etc.)
* Never hardcode a specific machine
* Prefer plugin-based implementations
* Validate all components before use
