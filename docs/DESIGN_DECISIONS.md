# Design Decisions

This document records the major architectural and implementation decisions made throughout the project. Each decision includes the rationale, considered alternatives, and expected impact on the application's maintainability, scalability, and code quality.

---

# Decision 001 - Use ApplicationContext as the Composition Root

**Status:** Accepted

## Context

The application requires several shared services, including logging, repositories, and business services. Directly creating these objects throughout the codebase would tightly couple components and make dependency management difficult.

## Decision

Introduce an `ApplicationContext` that owns and initializes shared application services. Components receive dependencies from the context rather than constructing them directly.

## Alternatives Considered

- Global singleton objects
- Static utility classes
- Manual object creation in individual views

## Rationale

Using a Composition Root centralizes object creation, improves maintainability, and simplifies future dependency injection.

## Consequences

### Positive

- Reduced coupling
- Centralized dependency management
- Easier testing
- Clear ownership of shared resources

### Negative

- Slight increase in initialization complexity

---

# Decision 002 - Adopt a Layered Architecture

**Status:** Accepted

## Context

Business logic, data access, and presentation responsibilities should remain independent.

## Decision

Separate the application into:

- Presentation Layer
- Service Layer
- Repository Layer
- Database Layer

## Rationale

Layering improves maintainability, readability, and future extensibility.

---

# Decision 003 - Introduce a Centralized Logging Framework

**Status:** Accepted

## Context

Using `TRACE()` or `std::cout` throughout the application does not scale well and provides inconsistent diagnostic information.

## Decision

Implement a centralized logging service with categories and log levels.

## Rationale

A unified logging system simplifies debugging and provides consistent diagnostics across the application.

---

# Decision 004 - Use RAII for Scope Logging

**Status:** Accepted

## Context

Manual ENTER and EXIT logging often leads to duplicated code and missed cleanup paths.

## Decision

Create `LogScope` to automatically log function entry and exit using RAII.

## Rationale

RAII guarantees cleanup regardless of how a scope exits, reducing boilerplate and improving reliability.

---

# Decision 005 - Use Repository Pattern

**Status:** Accepted

## Context

Business logic should not depend directly on database APIs.

## Decision

Introduce repositories responsible for data access.

## Rationale

Repositories isolate persistence concerns and make future database changes easier.

---

# Future Decisions

The following decisions will be documented as the project evolves:

- Command Pattern
- Undo / Redo Architecture
- SQLite Integration
- Configuration Management
- Exception Handling Strategy
- Threading Model
- Testing Strategy