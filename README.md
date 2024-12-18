# 🚀 R-Type

**Binary Names**: `r-type_server`, `r-type_client`  
**Language**: C++ 
**Build Tool**: CMake 

---

## 📚 Table of Contents
- [📖 Project Overview](#-project-overview)
- [✨ Key Features](#-key-features)
- [⚙️ Build and Run Instructions](#️-build-and-run-instructions)
- [📦 Dependencies](#-dependencies)
- [💻 Platform Support](#-platform-support)
- [📑 Documentation](#-documentation)
- [🤝 Contributing](#-contributing)
- [📝 License](#-license)
- [📞 Contacts](#-contacts)

---

## 📖 Project Overview

**Advanced R-Type** is a networked video game project inspired by the classic **R-Type**, reimagined as a multiplayer game where 1-4 players battle the evil Bydos together. This project involves creating:
- A **multithreaded server** that handles game logic and communication.
- A **graphical client** to display the game and handle player input.

The project emphasizes advanced software engineering practices, including modularity, cross-platform support, and efficient networking.

---

## ✨ Key Features

- 🎮 **Multiplayer Support**: Play with up to 4 players in a shared battle.
- 🛠️ **Custom Game Engine**: Designed with advanced architectural patterns like Entity-Component-System (ECS) and decoupled subsystems.
- 📡 **Binary Protocol**: High-performance UDP communication for in-game interactions.
- 🧩 **Extensible Gameplay**:
  - Modular design to support additional features and content.
  - Plugin-friendly for future enhancements.
- 🖥️ **Cross-Platform Compatibility**: Runs on both Windows and Linux.

---

## ⚙️ Build and Run Instructions

### 🛠️ Prerequisites
- **C++ Compiler**: GCC (Linux) or MSVC (Windows).
- **CMake**: Ensure version 3.16 or higher.
- Optional: Package manager (e.g., Conan, Vcpkg) for dependencies.

### 🔨 Build Instructions
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd Advanced-R-Type```

2.	Build the project using CMake:
    ```
    mkdir build && cd build
    cmake ..
    make```

### ▶️ Running the Game

- start the server:
    ```./r-type_server```
- Launch the client:
    ```./r-type_client```

### 📦 Dependencies

The project uses the following libraries:

- 🛠️ **Asio** or equivalent for networking (server).
- 🎨 **SFML** for rendering, input, and audio (client).
- ⚙️ Optional: **CMake FetchContent** or a package manager like **Conan** or **Vcpkg** to manage dependencies.

All third-party dependencies must be bundled with the project or fetched during the build process.

---

### 💻 Platform Support

- 🖥️ **Windows**: Compiled with MSVC.
- 🐧 **Linux**: Compiled with G++.
- 🌐 Cross-compilation supported with CMake.

---

### 📑 Documentation

For a complete reference, see [the documentation hosted online](https://epitech-f1becc07.mintlify.app/introduction).

---

### 🤝 Contributing

We welcome contributions! 🎉 To get started:

1. 🍴 Fork the repository.
2. 🌿 Create a feature branch.
3. 📨 Submit a pull request with a clear description of your changes.

#### Development Guidelines

- 📂 Use feature branches for development.
- 🖋️ Follow the provided coding conventions.
- ✅ Ensure all changes are documented and tested.

---

### 📝 License

This project is licensed under the **MIT License**. 📜 See the `LICENSE` file for more details.

---

### 📞 Contacts

For questions, suggestions, or feedback:

- 📧 **Team Contact**: [antoine.le@epitech.eu], [tristan.delahousse@epitech.eu], [isaac.gonzalez-bottini@epitech.eu], [nicolas.rodiet@epitech.eu], [theo.fisch-dewailly@epitech.eu]
