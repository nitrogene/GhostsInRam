# 🚧 Features

## 🟡 Current Feature

*(Aucune fonctionnalité en cours pour l’instant)*

---

## ⚪ Backlog

### F002 - Add "Load INI" button

**Description**
Add a button in the main window to trigger configuration loading.

**Requirements**

* Button visible in UI
* Click event handled

---

### F003 - Load and parse INI file

**Description**
Allow user to select and load a `.ini` file.

**Requirements**

* File dialog opens
* File is read successfully
* Basic parsing works

---

### F004 - Display configuration content

**Description**
Show parsed INI content in the UI.

**Requirements**

* Display CPU / MEMORY / IO values
* Basic UI feedback

---

### F005 - Define core interfaces

**Description**
Create base interfaces for hardware abstraction.

**Requirements**

* `ICPU`
* `IMemoryBus`
* Interfaces compile and are usable

---

### F006 - Create plugin base system

**Description**
Set up Qt plugin loading mechanism.

**Requirements**

* Plugin directory scanned
* Plugins detected by Qt

---

### F007 - Implement CPU plugin interface

**Description**
Define and enforce CPU plugin structure.

**Requirements**

* CPU plugin implements `ICPU`
* Core can identify CPU plugins

---

### F008 - Validate configuration against plugins

**Description**
Ensure required components exist as plugins.

**Requirements**

* Check CPU / MEMORY / IO availability
* Display error if missing

---

### F009 - Instantiate components

**Description**
Create instances of required components from plugins.

**Requirements**

* Components created dynamically
* Instances accessible from core

---

### F010 - Connect components (CPU ↔ Memory Bus)

**Description**
Wire components together via interfaces.

**Requirements**

* CPU connected to memory bus
* Communication possible

---

## 🟢 Completed Features

### F001 - Investigate why trace.log is not generated

**Description**
Currently when the application is executed, no trace.log is generated.

**Requirements**

* trace.log generated

**Validation**

* Running the application generate a trace.log

**Status**
COMPLETED

---

## 📌 Rules Reminder

* Only one feature in progress at a time
* A feature is complete only after user validation
* One feature = one commit
* Do not start next feature without validation
