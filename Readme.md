# 🎮 Groove Game Engine

A modular C++ game engine built from scratch using **OpenGL**, **GLFW**, and **CMake**. This is a personal project to understand and implement core game engine architecture — rendering, windowing, and sandbox testing — by building everything from the ground up.

---

## 🚧 Project Structure

```
Groove/
├── engine/           # Core engine code (Groove)
├── sandbox/          # Sandbox app that links to the engine
├── out/              # Build output folder
├── CMakeLists.txt    # Root build config
└── .gitignore
```

* `engine/`: Contains reusable engine modules.
* `sandbox/`: A minimal app for testing engine functionality.
* `out/build/windows-debug/sandbox/Sandbox.exe`: The final executable after building.

---

## ✅ Features So Far

* ✅ CMake-based modular engine structure
* ✅ Visual Studio 2022 support (multi-config builds)
* ✅ Linked via VCPKG with GLFW and GLAD
* ✅ Working OpenGL context
* ✅ Engine compiles and runs with output from sandbox

---

## 💻 Requirements

* **C++17 or higher**
* **Visual Studio 2022** with Desktop C++ workload
* **CMake 3.26+**
* **[VCPKG](https://github.com/microsoft/vcpkg)** for dependency management

> 🛠️ Packages used:
>
> ```
> vcpkg install glfw3 glad
> ```

Ensure `VCPKG_ROOT` is available, or pass the toolchain manually.

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

> Make sure to adjust the toolchain path above if needed.

### 🔹 3. Build the Project

```bash
cmake --build out/build/windows-debug --config Debug
```

---

## 🧪 Running the Engine

After a successful build, navigate to the sandbox output directory:

```bash
cd out/build/windows-debug/sandbox
Sandbox.exe
```

This will launch the test application using the engine.

---

## 📌 Notes

* Don't commit `.vs/`, `ipch/`, `*.exe`, or `*.VC.db` files — these are local-only.
* `.gitignore` has been configured to avoid these.
* The `engine` is still under early development and will evolve in modules (windowing, rendering, input, etc.)

---

## 🗓️ Roadmap

* [ ] Logging system
* [ ] ECS architecture
* [ ] Event system
* [ ] Shader & rendering abstraction
* [ ] Scene management
* [ ] UI & ImGui integration (future)

---

## 📜 License

This project is for educational and personal use. A formal open-source license may be added later.

---

Made with ❤️ by Adii
