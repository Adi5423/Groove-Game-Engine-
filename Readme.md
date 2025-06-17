﻿# 🎮 Groove Game Engine

> **Next‑gen modular C++ engine** built with OpenGL, GLFW, and CMake.  
> Focus: Realistic roads & vehicles (future), solid core systems today.
---

﻿
## 🚧 Project Structure

```text
Groove/
├── engine/           # Core modules
│   ├── Input/        # Keyboard & mouse handling
│   ├── Renderer/     # Shader & triangle rendering
│   ├── Utils/        # Logger & utilities
│   └── src/          # Engine lifecycle & window
├── sandbox/          # Demo app (Sandbox.exe)
├── out/              # Build artifacts
├── LICENSE.txt       # MIT License
├── README.md         # Overview & quickstart
├── detailed_guide.md # In‑depth architecture
└── .gitignore        # Excluded files
````

---

## ✅ Features

| Subsystem       | Status | Highlights                                  |
| --------------- | :----: | ------------------------------------------- |
| **CMake Build** |    ✅   | Modular engine & sandbox presets            |
| **Windowing**   |    ✅   | GLFW wrapper + VSync                        |
| **Input**       |    ✅   | Keyboard & mouse API                        |
| **Logging**     |    ✅   | Color‑coded console & file output           |
| **Rendering**   |    ✅   | Shader class + VAO/VBO triangle             |
| **UI (ImGui)**  |    ✅   | Overlaid ImGui panels                       |
| **Delta Time**  |    ✅   | Frame‑time (`TimeStep`) integration         |
| **Next…**       |   🔲   | ECS, event system, scene graph, vehicle sim |

---

## 💻 Requirements

* **C++17** or higher
* **Visual Studio 2022** (Desktop C++ workload)
* **CMake 3.26+**
* **vcpkg** (GLFW, GLAD, GLM, ImGui)

```bash
# core libs
vcpkg install glfw3 glad glm imgui[glfw-binding,opengl3-binding]
```

---

## 🚀 Quick Start

1. **Clone**

   ```bash
      git clone [https://github.com/Adi5423/Groove-Game-Engine.git](https://github.com/Adi5423/Groove-Game-Engine.git)
      cd Groove-Game-Engine
   ```

2. **Configure**
   ```bash
      cmake -S . -B out/build/windows-debug -G "Visual Studio 17 2022" -A x64 \
      -DCMAKE_TOOLCHAIN_FILE="<VCPKG_PATH>/scripts/buildsystems/vcpkg.cmake"
   ````

3. **Build**

   ```bash
      cmake --build out/build/windows-debug --config Debug
   ```


4. **Run**
```bash
./out/build/windows-debug/sandbox/Sandbox.exe
````

> Tip: Set `sandbox` as startup project in VS for one‑click debug.

---

## 🎬 Runtime Flow

```text
Sandbox.exe
  ↳ Engine::Init()
     • Logger + Window + GLAD + Input + Renderer + ImGui
  ↳ Engine::Run()
     • Clear screen
     • Process input + delta time
     • Draw triangle
     • ImGui frame
     • Swap buffers & poll events
  ↳ Engine::Shutdown()
     • Cleanup subsystems
```

---

## 🗓️ Roadmap

* [x] Logging
* [x] Input handling
* [x] Window abstraction
* [x] Shader & triangle rendering
* [x] ImGui integration
* [ ] ECS framework
* [ ] Event dispatch system
* [ ] Scene & entity management
* [ ] Vehicle simulation & roads

---

## 📌 Notes

* `.gitignore` excludes build dirs, IDE caches, large files.
* Use `git rm --cached <file>` to untrack stray binaries.
* Architecture is modular—drop in new subsystems under `engine/`.

---

## 📜 License

Licensed under the **MIT License**. See `LICENSE.txt`.

---

## 📬 Contact

* ✉️  [adii54ti23@gmail.com](mailto:adii54ti23@gmail.com)
* 💼 [LinkedIn](https://www.linkedin.com/in/aditya-tiwari-141731329/)
* 📸 [Instagram @adii5423\_](https://www.instagram.com/adii5423_)

Made with ❤️ by Adii
