# 🚧 Features

Si le contenu d'une feature n'est pas clair, demander des explications avant d'enrichir le contenu de la feature avec les réponses obtenues.
Avant d'implémenter une feature, on commence toujours par la déplacer du backlog à "Current Feature".
Une fois terminée: 

 * elle est déplacée dans "Completed Features"
 * un commit est effectué

## 🟡 Current Feature

*(Aucune fonctionnalité en cours pour l'instant)*

---

## ⚪ Backlog

### F005 - Define core interfaces

**Description**
Create some interfaces for hardware abstraction. They will be used to implemente plugin code for R6502AP, SYS6522A, HCS10017.

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

### F002 - Add "Load INI" button

**Description**
Add a button in the main window to trigger configuration loading.

**Requirements**

* Button visible in UI
* Click event handled

**Validation**

* Build passes with `build.ps1`
* Click handler is connected and logs the button event

**Status**
COMPLETED

---

### F003 - Load and parse INI file

**Description**
Allow user to select and load a `.ini` file.

**Requirements**

* File dialog opens
* File is read successfully
* Basic parsing works

**Validation**

* Build passes with `build.ps1`
* File dialog opens on button click
* INI file is parsed correctly (sections and values)
* Configuration is logged in trace.log

**Status**
COMPLETED

---

### F004 - Log configuration content

**Description**
Show parsed INI content in the UI. Here's an example of ini file file:

```ini
[CPU]
R6502AP
[IO]
SYS6522A
[Memory]
HCS10017
```

**Requirements**

* Log CPU / MEMORY / IO values
* Basic UI feedback

**Validation**

* Build passes with `build.ps1`
* Configuration values displayed in read-only QTextEdit after loading INI
* CPU, Memory, IO values logged to trace.log and shown in UI
* Placeholder text shown before file is loaded

**Status**
COMPLETED

---

## 📌 Rules Reminder

* Only one feature in progress at a time
* A feature is complete only after user validation
* One feature = one commit
* Do not start next feature without validation
