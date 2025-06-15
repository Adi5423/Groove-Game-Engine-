# 🎮 Groove Game Engine

A modular C++ game engine built from scratch using **OpenGL**, **GLFW**, and **CMake**. This is a personal project to understand and implement core game engine architecture — rendering, windowing, and sandbox testing — by building everything from the ground up.

---

## 🚧 Project Structure

```
Groove/
├── engine/           # Core engine code (Groove)
│   ├── src/          # Engine main files (Engine.cpp, Window.cpp)
│   ├── Input/        # Input system module
│   └── Utils/        # Logger and utility code
├── sandbox/          # Sandbox app that links to the engine
├── out/              # Build output folder
├── CMakeLists.txt    # Root build config
└── .gitignore
```

* `engine/src`: Engine core (`Engine`, `Window`)
* `engine/Input`: Input module handling mouse/keyboard input
* `sandbox/`: A minimal app for testing engine functionality
* `out/build/windows-debug/sandbox/Sandbox.exe`: Final output after build

---

## ✅ Features So Far

* ✅ **Modular engine** architecture using CMake
* ✅ Visual Studio 2022 support (multi-config builds)
* ✅ **Modular CMake**: Engine & sandbox projects
* ✅ **VS2022** support (multi-config)
* ✅ **VCPKG** for GLFW, GLAD, GLM
* ✅ **Window**: GLFW wrapper with VSync
* ✅ **Input**: Keyboard & mouse abstraction
* ✅ **Logging**: Color‑coded console + file output
* ✅ **Rendering**: Shader class + test triangle via VAO/VBO

---

## 💻 Requirements

* **C++17 or higher**
* **Visual Studio 2022** with Desktop C++ workload
* **CMake 3.26+**
* **[VCPKG](https://github.com/microsoft/vcpkg)** for dependency management

> 🛠️ Packages used:
>
> ```
> vcpkg install glfw3 glad glm
> ```

Ensure `VCPKG_ROOT` is set, or pass the toolchain file manually.

---

## 💠 Build Instructions

### 🔹 1. Clone the Repo

```bash
git clone https://github.com/Adi5423/Groove-Game-Engine.git
cd Groove-Game-Engine
```

### 🔹 2. Configure with CMake (Debug)

```bash
cmake -S . -B out/build/windows-debug -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE="D:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

> Modify the VCPKG path above if needed.

### 🔹 3. Build the Project

```bash
cmake --build out/build/windows-debug --config Debug
```

---

## 🧪 Running the Engine

After a successful build:

```bash
cd out/build/windows-debug/sandbox
Sandbox.exe
```

This runs the sandbox app using the Groove engine.

---

## 🔄 How It Works

```
User runs → Sandbox.exe
         ↓
main.cpp calls Engine::Init()
         ↓
Logger starts → "Initializing GLFW..."
         ↓
GLFW initialized
         ↓
Window created + OpenGL context setup via GLAD
         ↓
Input system initialized (keyboard/mouse)
         ↓
Engine::Run() starts → clears screen, polls window events (game loop)
         ↓
Input test: W key or left mouse click logs to console
         ↓
User closes window
         ↓
Engine::Shutdown() → Logger shutdown → GLFW cleanup
```

---

## 🔁 Execution Flow

```
Sandbox.exe → Engine::Init() → Logger + Window + GLAD + Input + Renderer
             ↳ Engine::Run() → clear screen, input checks, draw triangle, swap buffers, poll events
             ↳ Engine::Shutdown() → cleanup subsystems
```


---

## 🗓️ Roadmap

## 🗓️ Roadmap

* ✅ Logging
* ✅ Input handling
* ✅ Window abstraction
* 🔲 Shader abstraction
* 🔲 Triangle rendering
* 🔲 ECS framework
* 🔲 Event dispatch system
* 🔲 Scene & entity management
* 🔲 UI/ImGui or QT integration

---

## 📌 Notes

* `.gitignore` avoids committing build, cache, or binary files.
* The engine is structured to evolve modularly: each system (logging, input, rendering, etc.) has its own source folder.
* Work is ongoing, with new systems being introduced incrementally.

---

## 📜 License

This project is licensed under the **MIT License**. See `LICENSE.txt`.

---

## 📌 Contact & Social

* **Email:** [adii54ti23@gmail.com](mailto:adii54ti23@gmail.com)
* **LinkedIn:** [Aditya Tiwari](https://www.linkedin.com/in/aditya-tiwari-141731329/)
* **Instagram:** [@adii5423\_](https://www.instagram.com/adii5423_)

Made with ❤️ by Adii
