# Architecture

## Overview

The project follows a layered architecture that emphasizes separation of concerns, maintainability, and extensibility. It adopts several modern C++ design principles while remaining compatible with the Microsoft Foundation Classes (MFC) framework.

The primary goal is to minimize coupling between components and ensure each layer has a single responsibility.

---

# High-Level Architecture

```
+------------------------------------------------------+
|                  MFC Application                     |
|                  (CHelloMFCApp)                      |
+---------------------------+--------------------------+
                            |
                            v
+------------------------------------------------------+
|               ApplicationContext                     |
|              (Composition Root)                      |
+---------------------------+--------------------------+
                            |
       +--------------------+--------------------+
       |                    |                    |
       v                    v                    v
+--------------+    +----------------+    +----------------+
|    Logger    |    |   Repository   |    | ProductService |
+--------------+    +----------------+    +----------------+
                            |
                            v
                    +----------------+
                    |    Database    |
                    +----------------+
```

---

# Architectural Layers

## Presentation Layer

Responsible for user interaction through MFC windows, dialogs, controls, and commands.

Responsibilities:

- Display data
- Handle user input
- Delegate work to services
- Avoid business logic

---

## Service Layer

Contains the application's business logic.

Responsibilities:

- Coordinate operations
- Validate business rules
- Interact with repositories
- Log important operations

Example:

```
ProductService
    ↓
Repository
    ↓
Database
```

---

## Repository Layer

Provides a clean abstraction over data storage.

Responsibilities:

- CRUD operations
- Data retrieval
- Hide database implementation
- Simplify testing

---

## Database Layer

Responsible for persistent storage.

Future implementations may include:

- SQLite
- SQL Server

Changing the database should not affect higher layers.

---

# Core Components

## ApplicationContext

Acts as the application's Composition Root.

Responsibilities:

- Create shared services
- Manage object lifetime
- Provide dependency injection
- Eliminate unnecessary global objects

---

## Logger

Provides centralized logging throughout the application.

Features:

- File logging
- Log levels
- Categories
- Timestamp support
- Automatic formatting

---

## LogScope

Uses RAII to automatically log function entry and exit.

Benefits:

- No manual cleanup
- Exception-safe
- Easier debugging
- Consistent tracing

---

# Design Principles

The project follows these principles:

- Single Responsibility Principle (SRP)
- Dependency Inversion Principle (DIP)
- Separation of Concerns
- Composition over Inheritance
- RAII
- Modern C++ Resource Management

---

# Current Design Patterns

Implemented:

- Composition Root
- Dependency Injection
- Repository Pattern
- Service Layer
- RAII

Planned:

- Command Pattern
- Observer Pattern (if required)
- Factory Pattern (if required)

---

# Dependency Flow

```
UI

↓

Service

↓

Repository

↓

Database
```

Dependencies always point downward.

Lower layers never reference higher layers.

---

# Future Architecture

Planned additions include:

- SQLite integration
- Inventory module
- Customer management
- Sales module
- Reporting
- Configuration manager
- Undo/Redo framework
- Unit testing support

The architecture is intentionally designed so these modules can be added with minimal impact on existing code.