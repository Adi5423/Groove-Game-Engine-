# 🎮 Groove Game Engine

A modular C++ game engine built from scratch using **OpenGL**, **GLFW**, and **CMake**. This personal engine focuses on garage‑built realism—starting with roads and vehicles in future—while nailing core architecture: rendering, windowing, input, and utilities.

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
├── Readme.md         # High‑level overview & instructions
├── detailed_guide.md # In‑depth architecture & guide
└── .gitignore        # Ignored files (build, IDE caches, binaries)
```

---

## ✅ Features So Far

* **Modular CMake**: Engine & sandbox projects
* **VS2022** support (multi-config)
* **VCPKG** for GLFW, GLAD, GLM
* **Window**: GLFW wrapper with VSync
* **Input**: Keyboard & mouse abstraction
* **Logging**: Color‑coded console + file output
* **Rendering**: Shader class + test triangle via VAO/VBO

---

## 💻 Requirements

* **C++17** or higher
* **Visual Studio 2022** (Desktop C++ workload)
* **CMake 3.26+**
* **VCPKG** for dependencies

```bash
vcpkg install glfw3 glad glm
```

---

## 💠 Quick Start

1. **Clone** the repo:

   ```bash
   ```

git clone [https://github.com/Adi5423/Groove-Game-Engine.git](https://github.com/Adi5423/Groove-Game-Engine.git)
cd Groove-Game-Engine

````
2. **Configure**:
```bash
cmake -S . -B out/build/windows-debug -G "Visual Studio 17 2022" -A x64 \
-DCMAKE_TOOLCHAIN_FILE="D:/vcpkg/scripts/buildsystems/vcpkg.cmake"
````

3. **Build**:

   ```bash
   ```

cmake --build out/build/windows-debug --config Debug

````
4. **Run**:
```bash
cd out/build/windows-debug/sandbox
Sandbox.exe
````

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
* 🔲 Shader abstraction
* 🔲 Triangle rendering
* 🔲 ECS framework
* 🔲 Event dispatch system
* 🔲 Scene & entity management
* 🔲 UI/ImGui integration

---

## 📜 License

This project is licensed under the **MIT License**. See `LICENSE.txt`.

---

## 📌 Contact & Social

* **Email:** [adii54ti23@gmail.com](mailto:adii54ti23@gmail.com)
* **LinkedIn:** [Aditya Tiwari](https://www.linkedin.com/in/aditya-tiwari-141731329/)
* **Instagram:** [@adii5423\_](https://www.instagram.com/adii5423_)

Made with ❤️ by Adii
