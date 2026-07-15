# Roadmap

This roadmap outlines the planned evolution of the Modern C++ Inventory Manager. The project is being developed incrementally, with each milestone building upon the previous one to create a maintainable, enterprise-quality Windows desktop application.

---

# Current Status

🟢 **Active Development**

Current Milestone:

- ✅ Core Framework Foundation

See [PROJECT_STATUS.md](PROJECT_STATUS.md) for current progress.

---

# Milestone 1 – Core Framework Foundation

**Status:** ✅ Completed

## Goals

Build a clean, extensible application architecture.

### Completed

- [x] ApplicationContext (Composition Root)
- [x] Dependency Injection
- [x] Repository Layer
- [x] Service Layer
- [x] Central Logger
- [x] Log Categories
- [x] LogScope (RAII)
- [x] Modern C++ Resource Management

---

# Milestone 2 – Command Framework

**Status:** 🔄 Planned

## Goals

Introduce a reusable command system to support user actions and Undo/Redo functionality.

### Planned Features

- [ ] ICommand interface
- [ ] Command Manager
- [ ] Undo Manager
- [ ] Add Command
- [ ] Update Command
- [ ] Delete Command
- [ ] Undo
- [ ] Redo
- [ ] Command Logging

---

# Milestone 3 – Data Layer

**Status:** ⏳ Planned

## Goals

Implement persistent data storage.

### Planned Features

- [ ] SQLite integration
- [ ] Database abstraction
- [ ] Connection management
- [ ] Repository implementation
- [ ] Transactions

---

# Milestone 4 – Inventory Management

**Status:** ⏳ Planned

### Planned Features

- [ ] Product Management
- [ ] Category Management
- [ ] Supplier Management
- [ ] Inventory Tracking
- [ ] Stock Adjustment
- [ ] Search
- [ ] Filtering

---

# Milestone 5 – Sales Module

**Status:** ⏳ Planned

### Planned Features

- [ ] Sales Transactions
- [ ] Customer Management
- [ ] Order History
- [ ] Receipt Generation

---

# Milestone 6 – Reporting

**Status:** ⏳ Planned

### Planned Features

- [ ] Inventory Reports
- [ ] Sales Reports
- [ ] Low Stock Reports
- [ ] Export to CSV
- [ ] Export to Excel

---

# Milestone 7 – Application Polish

**Status:** ⏳ Planned

### Planned Features

- [ ] Settings
- [ ] Configuration Management
- [ ] Keyboard Shortcuts
- [ ] Theme Support
- [ ] Error Handling Improvements
- [ ] Performance Optimization

---

# Milestone 8 – Quality Assurance

**Status:** ⏳ Planned

### Planned Features

- [ ] Unit Tests
- [ ] Integration Tests
- [ ] Performance Testing
- [ ] Documentation Review
- [ ] Code Cleanup

---

# Version Goals

| Version | Goal |
|---------|------|
| v0.1 | Initial MFC Project |
| v0.2 | Logging Framework |
| v0.3 | Core Architecture |
| v0.4 | Dependency Injection |
| v0.5 | Command Framework |
| v0.6 | SQLite Integration |
| v0.7 | Inventory Management |
| v0.8 | Sales Module |
| v0.9 | Reporting |
| v1.0 | First Stable Portfolio Release |

---

# Long-Term Vision

The goal of this project is to demonstrate how a traditional MFC application can be modernized using contemporary C++ design principles and enterprise application architecture. By the first stable release, the project will showcase maintainable code, reusable components, modern design patterns, and production-quality engineering practices suitable for professional Windows desktop application development.

---

# Technical Mastery

The project is also used to practice and demonstrate the following topics:

- Modern C++ (C++17/20)
- MFC Framework
- Win32 Programming
- RAII
- Smart Pointers
- Dependency Injection
- Repository Pattern
- Service Layer
- Command Pattern
- Observer Pattern (if required)
- SQLite
- Unit Testing
- Clean Architecture
- SOLID Principles