# 🎮 Groove Game Engine

A modular C++ game engine built from scratch using **OpenGL**, **GLFW**, and **CMake**. This personal engine focuses on garage -built realism—starting with roads and vehicles in future—while nailing core architecture: rendering, windowing, input, and utilities.

---

## 🚧 Project Structure

```
Groove/
├── engine/           # Core engine modules (Input, Renderer, Utils, core)
│   ├── Input/        # Keyboard & mouse handling
│   ├── Renderer/     # Shader & graphics rendering
│   ├── Utils/        # Logger, helpers
│   └── src/          # Engine lifecycle & window abstraction
├── sandbox/          # Sample app linking Engine (Sandbox.exe)
├── out/              # CMake build output
├── LICENSE.txt       # MIT License
├── Readme.md         # High -level overview & instructions
├── detailed_guide.md # In -depth architecture & guide
└── .gitignore        # Ignored files (build, IDE caches, binaries)
```

## ✅ Features So Far

* ✅ **Modular engine** architecture using CMake
* ✅ Visual Studio 2022 support (multi-config builds)
* ✅ **Modular CMake**: Engine & sandbox projects
* ✅ **VS2022** support (multi-config)
* ✅ **VCPKG** for GLFW, GLAD, GLM
* ✅ **Window**: GLFW wrapper with VSync
* ✅ **Input**: Keyboard & mouse abstraction
* ✅ **Logging**: Color -coded console + file output
* ✅ **Rendering**: Shader class + test triangle via VAO/VBO

---

## 💻 Requirements

* **C++17 or higher**
* **Visual Studio 2022** with Desktop C++ workload
* **CMake 3.26+**
* **[VCPKG](https://github.com/microsoft/vcpkg)** for dependency management

> 🛠️ Packages used:
>
> ```bash
> vcpkg install glfw3 glad glm
> ```
>
> Make sure `VCPKG_ROOT` is set, or pass the toolchain file manually.

---

## 🔠 Build Instructions

### 🔹 1. Clone the Repo

```bash
git clone https://github.com/Adi5423/Groove-Game-Engine.git
cd Groove-Game-Engine
```

### 🔹 2. Configure with CMake

> Replace `<VCPKG_PATH>` with your actual vcpkg path. If `VCPKG_ROOT` is globally set, this isn't needed.

```bash
cmake -S . -B out/build/windows-debug -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE="<VCPKG_PATH>/scripts/buildsystems/vcpkg.cmake"
```

Example:

```bash
-DCMAKE_TOOLCHAIN_FILE="D:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

### 🔹 3. Build the Project

```bash
cmake --build out/build/windows-debug --config Debug
```

This builds both `engine` and `sandbox` targets.

---

## 🧪 Running the Engine

After a successful build, run the sandbox app:

```bash
./out/build/windows-debug/sandbox/Sandbox.exe
```

Or from PowerShell:

```powershell
Start-Process .\out\build\windows-debug\sandbox\Sandbox.exe
```

You can also run via Visual Studio by setting `sandbox` as the startup project.

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

* ✅ Logging
* ✅ Input handling
* ✅ Window abstraction
* ✅ Shader abstraction
* ✅ Triangle rendering
* ☑️ ECS framework
* ☑️ Event dispatch system
* ☑️ Scene & entity management
* ☑️ UI/ImGui or QT integration

---

## 📌 Notes

* `.gitignore` avoids committing build, cache, and binary files.
* If `.vs/`, `*.exe`, `*.VC.db`, or build folders show up in GitHub commits—remove them using:

  ```bash
  git rm --cached filename
  ```
* The engine evolves modularly: each system (logging, input, rendering) lives in its own folder.
* New subsystems are added incrementally.

---

## 📜 License

This project is licensed under the **MIT License**. See `LICENSE.txt`.

---

## 📌 Contact & Social

* **Email:** [adii54ti23@gmail.com](mailto:adii54ti23@gmail.com)
* **LinkedIn:** [Aditya Tiwari](https://www.linkedin.com/in/aditya-tiwari-141731329/)
* **Instagram:** [@adii5423\_](https://www.instagram.com/adii5423_)

Made with ❤️ by Adii
