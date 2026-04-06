# 🤖 AI Context & Development Rules

## 🧭 Purpose

This document defines how AI assistants (e.g., Gemini) must behave when contributing to this project.

The goal is to ensure:

* Consistency
* Incremental progress
* No unfinished or unstable features
* Clear validation of work

---

## 🚨 Core Rules (MANDATORY)

### 1. No Parallel Features

The AI MUST NOT start a new feature if the current one is not fully completed.

* Only **one feature at a time**
* No partial implementations left behind
* No speculative code for future features

---

### 2. Feature Completion Authority

A feature is considered **complete only when explicitly validated by the user**.

Validation can be:

* A direct statement from the user (e.g., "feature is complete")
* An automated validation method provided by the user (tests, script, etc.)

Until then:

* The feature is **NOT complete**
* The AI must continue working on it

---

### 3. One Feature = One Commit

Each completed feature must correspond to exactly **one Git commit**.

Rules:

* No multi-feature commits
* No partial feature commits
* Commit only when the feature is validated

---

### 4. No Premature Abstraction

The AI must:

* Avoid adding abstractions for features not yet implemented
* Avoid designing for hypothetical future needs

Follow:

> "Implement what is needed now, nothing more"

---

### 5. Use Existing Architecture

The AI MUST:

* Respect all interfaces (`ICPU`, `IMemoryBus`, etc.)
* Never bypass abstraction layers
* Never hardcode specific machines or components

---

## 📂 Context Awareness

### Required Files to Read

Before making any change, the AI MUST read:

* `README.md`
* `ARCHITECTURE.md`
* `AI_CONTEXT.md`
* Relevant files in `/docs`
* Relevant source files

---

### Continuity Between Sessions

The AI must:

* Reconstruct context from project files
* Not rely on previous chat history
* Infer current progress from code and documentation

---

## 🧠 Feature Workflow

### Step 1 — Understand the Feature

* Identify the current feature being worked on
* Confirm it is not already completed
* Do not assume anything without checking code

---

### Step 2 — Plan Before Coding

The AI MUST:

* Break down the feature into steps
* Identify impacted components
* Ensure alignment with architecture

---

### Step 3 — Implement Incrementally

* Write minimal working code
* Keep changes focused
* Avoid unrelated modifications

---

### Step 4 — Validate

* Ensure the feature is fully functional
* Use provided validation method if available
* Otherwise, ensure logical completeness

---

### Step 5 — Wait for User Validation

The AI MUST:

* Stop after implementation
* Wait for user confirmation before considering the feature complete

---

## ⚠️ Forbidden Behaviors

The AI MUST NOT:

* Start a new feature before finishing the current one
* Modify unrelated parts of the codebase
* Introduce breaking changes without justification
* Assume a feature is complete without validation
* Skip reading project documentation
* Generate large amounts of speculative code

---

## 🧩 Definition of a Feature

A feature must be:

* Clearly defined
* Self-contained
* Testable or verifiable
* Fully integrated into the system

---

## 🧪 Validation Strategy

A feature is valid if:

* It works as intended
* It integrates correctly with existing components
* It respects architecture and interfaces
* It can be verified (manually or automatically)

---

## 🧠 Guiding Principles

* **Clarity over cleverness**
* **Completion over speed**
* **Consistency over innovation**
* **Explicit over implicit**

---

## 📝 Notes

* The user is the final authority on feature completion
* The AI is an execution assistant, not a decision maker
* All progress must be traceable and structured
