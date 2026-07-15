# Modern C++ Inventory Manager

> A modern Windows desktop inventory management application built with MFC and Modern C++.

![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-blue)
![MFC](https://img.shields.io/badge/Framework-MFC-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

---

## Overview

Modern C++ Inventory Manager is a portfolio project designed to demonstrate enterprise-level Windows desktop application development using Microsoft Foundation Classes (MFC) and Modern C++.

Rather than focusing solely on implementing inventory features, the project emphasizes clean architecture, maintainability, extensibility, and modern software engineering practices. It serves as a practical example of how traditional MFC applications can be modernized using current C++ design principles.

---

## Goals

The project aims to demonstrate:

- Modern C++ (C++17/20)
- MFC application development
- Enterprise application architecture
- Separation of concerns
- Dependency Injection
- Repository Pattern
- Service Layer
- Command Pattern
- RAII
- Logging framework
- SQLite integration
- Unit testing

---

## Features

### Current

- Modern MFC application architecture
- Dependency Injection
- ApplicationContext (Composition Root)
- Centralized logging framework
- Log categories
- RAII-based LogScope
- Service layer
- Repository layer

### Planned

- SQLite database
- Product management
- Inventory management
- Customer management
- Sales module
- Reports
- Undo / Redo
- Search and filtering
- Configuration management

For the complete feature list, see [docs/FEATURES.md](docs/FEATURES.md).

---

## Architecture

The application follows a layered architecture.

```text
Presentation (MFC)

↓

Service Layer

↓

Repository Layer

↓

Database
```

For detailed information, see [ARCHITECTURE.md](ARCHITECTURE.md).

---

## Technologies

- C++20
- MFC
- Win32 API
- STL
- Smart Pointers
- RAII
- SQLite (planned)
- Visual Studio 2026

---

## Project Structure

```text
ModernCppInventoryManager/

src/
tests/
docs/

README.md
ARCHITECTURE.md
PROJECT_STATUS.md
ROADMAP.md
CHANGELOG.md
```

---

## Building the Project

### Requirements

- Windows 10 / 11
- Visual Studio 2026
- Desktop development with C++
- MFC libraries

### Build

1. Clone the repository.
2. Open the solution in Visual Studio.
3. Restore dependencies if prompted.
4. Build the solution.
5. Run the application.

---

## Roadmap

Current development priorities include:

- Command Pattern
- SQLite integration
- Product CRUD
- Inventory module
- Reporting
- Unit tests

See [ROADMAP.md](ROADMAP.md) for detailed plans.

---

## Documentation

- [Project Status](PROJECT_STATUS.md)
- [Architecture](ARCHITECTURE.md)
- [Roadmap](ROADMAP.md)
- [Changelog](CHANGELOG.md)
- [Features](docs/FEATURES.md)
- [Design Decisions](docs/DESIGN_DECISIONS.md)
- [Development Journal](docs/DEVELOPMENT_JOURNAL.md)

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.