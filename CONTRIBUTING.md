# Contributing

Thank you for your interest in contributing to the Modern C++ Inventory Manager.

Although this project is primarily maintained as a portfolio and learning project, contributions, suggestions, bug reports, and discussions are welcome.

---

# Development Goals

The project emphasizes:

- Modern C++ best practices
- Clean Architecture
- Maintainable code
- Enterprise software design
- Readability over cleverness
- Long-term maintainability

---

# Before Contributing

Please review the following documentation before making changes:

- README.md
- PROJECT_STATUS.md
- ROADMAP.md
- ARCHITECTURE.md
- docs/DESIGN_DECISIONS.md

Understanding the project's architecture and design philosophy will help ensure consistency.

---

# Development Workflow

1. Fork the repository.
2. Create a feature branch.
3. Implement your changes.
4. Update documentation if necessary.
5. Verify the project builds successfully.
6. Submit a Pull Request.

---

# Coding Guidelines

## Modern C++

The project follows Modern C++ principles.

Preferred practices include:

- RAII
- Smart pointers
- STL containers
- STL algorithms
- `constexpr` where appropriate
- `enum class`
- `std::optional`
- `std::string_view`
- Avoid raw ownership pointers whenever possible.

---

## Architecture

New code should respect the project's layered architecture.

```
Presentation

↓

Service Layer

↓

Repository Layer

↓

Database
```

Business logic should remain outside the UI layer.

---

## Logging

Significant operations should be logged using the centralized Logger service.

Avoid:

- `printf`
- `std::cout`
- `TRACE()` for application logging

Use the project's logging infrastructure instead.

---

## Documentation

When adding significant features, please update any affected documentation.

This typically includes:

- README.md
- PROJECT_STATUS.md
- ROADMAP.md
- CHANGELOG.md
- ARCHITECTURE.md
- docs/FEATURES.md
- docs/DESIGN_DECISIONS.md
- docs/ENGINEERING_JOURNAL.md

Documentation should evolve alongside the code.

---

# Pull Requests

A pull request should:

- Focus on a single feature or improvement.
- Follow the project's coding conventions.
- Include appropriate documentation updates.
- Build successfully without warnings or errors.

---

# Reporting Issues

When reporting an issue, please include:

- Description
- Steps to reproduce
- Expected behavior
- Actual behavior
- Environment information
- Screenshots (if applicable)

---

# Questions

Questions and suggestions are always welcome.

Thank you for helping improve the project.

---

# Engineering Philosophy

This project is intentionally developed with the mindset of a production-quality Windows desktop application.

Every architectural decision prioritizes:

- Maintainability
- Readability
- Extensibility
- Separation of Concerns
- Modern C++ best practices

The objective is not only to deliver functionality but also to demonstrate professional software engineering practices suitable for enterprise applications.