# 🎮 Groove Game Engine

> **Next‑gen modular C++ engine** built with OpenGL, GLFW, and CMake.
> Focus: Realistic roads & vehicles (future), solid core systems today.

## 🚧 Implemented the 3D Cube Renderer and its shaders (rotating cube animation), working perfectly.

> **If you see a 3D red cube**, everything is working!
> Try left & right mouse buttons and the `W` key — inputs are tracked 🎮

---

## 📁 Project Structure

```text
Groove/
├── engine/           # Core modules
│   ├── Input/        # Keyboard & mouse handling
│   ├── Renderer/     # Shader, rendering, ImGui integration
│   ├── Utils/        # Logger & utility classes
│   └── src/          # Engine lifecycle, Window, TimeStep, Camera
├── sandbox/          # Demo application (Sandbox.exe)
├── out/              # CMake build output
├── resources/        # Screenshots, textures, shaders
│   ├── proof1.png    # Output screenshot 1
│   └── proof2.png    # Output screenshot 2
├── LICENSE.txt       # [MIT License](LICENSE.txt)
├── README.md         # Overview & quickstart
├── detailed_guide.md # In‑depth architecture & guide
└── .gitignore        # Excluded files
```

---

## ✅ Features

| Subsystem             | Status | Highlights                              |
| --------------------- | :----: | --------------------------------------- |
| **CMake Build**       |    ✅   | Modular engine & sandbox targets        |
| **Windowing**         |    ✅   | GLFW wrapper + VSync                    |
| **Input**             |    ✅   | Keyboard & mouse API                    |
| **Logging**           |    ✅   | Color‑coded console & file output       |
| **Rendering (2D/3D)** |    ✅   | Shader + rotating cube with VAO/VBO/IBO |
| **UI (ImGui)**        |    ✅   | ImGui overlay panels                    |
| **Delta Time**        |    ✅   | TimeStep frame‑time integration         |
| **Next…**             |   🔲   | ECS, events, scene system, vehicles     |

---

## 💻 Requirements

* **C++17** or higher
* **Visual Studio 2022** (Desktop C++ workload)
* **CMake 3.26+**
* **vcpkg** (GLFW, GLAD, GLM, ImGui)

```bash
# Core libraries
vcpkg install glfw3 glad glm imgui[glfw-binding,opengl3-binding]
```

Make sure `VCPKG_ROOT` is set or pass the toolchain file via `-DCMAKE_TOOLCHAIN_FILE`.

---

## 🚀 Quick Start

### 1. Clone

```bash
git clone https://github.com/Adi5423/Groove-Game-Engine.git
cd Groove-Game-Engine
```

### 2. Configure (CMake)

```bash
cmake -S . -B out/build/windows-debug -G "Visual Studio 17 2022" -A x64 \
  -DCMAKE_TOOLCHAIN_FILE="<VCPKG_PATH>/scripts/buildsystems/vcpkg.cmake"
```

### 3. Build

```bash
cmake --build out/build/windows-debug --config Debug
```

### 4. Run

```bash
./out/build/windows-debug/sandbox/Sandbox.exe
```

---

## 🧩 Visual Studio (Optional)

> If you have Visual Studio installed and VCPKG set up:

1. Open the root folder in VS (`Groove-Game-Engine/`).
2. Open any `CMakeLists.txt`, edit and undo (forces generation).
3. Wait for "CMake generation finished".
4. Press `Ctrl+Shift+B` or use **Build > Rebuild All**.
5. Run `Sandbox.exe` from:

```text
./out/build/windows-debug/sandbox/Sandbox.exe
```

If you run into any issues, feel free to [email](mailto:adii54ti23@gmail.com) or DM.

---

## 🎬 Runtime Flow

```text
Sandbox.exe
  ↳ Engine::Init()     // Logger, Window, GLAD, Input, Renderer, ImGui
  ↳ Engine::Run()      // Clear, input, delta-time, draw, UI, swap & poll
  ↳ Engine::Shutdown() // Cleanup subsystems
```

---

## 🖼️ Output Screenshots

| Proof        | Preview                         |
| ------------ | ------------------------------- |
| `proof1.png` | ![proof1](resources/proof1.png) |
| `proof2.png` | ![proof2](resources/proof2.png) |

---

## 🗓️ Roadmap

* [x] Logging
* [x] Input handling
* [x] Window abstraction
* [x] Shader & triangle rendering
* [x] ImGui integration
* [x] **3D Cube Renderer**
* [ ] ECS framework
* [ ] Event dispatch system
* [ ] Scene & entity management
* [ ] Vehicle simulation & roads

---

## 📌 Notes

* `.gitignore` excludes build dirs, IDE caches, and large files.
* Remove stray binaries with `git rm --cached <file>`.
* Architecture is modular: drop in new subsystems under `engine/`.

---

## 📜 License

Licensed under the **MIT License**. See [`LICENSE.txt`](LICENSE.txt).

---

## 📬 Contact

* ✉️  [adii54ti23@gmail.com](mailto:adii54ti23@gmail.com)
* 💼 [LinkedIn](https://www.linkedin.com/in/aditya-tiwari-141731329/)
* 📸 [Instagram @adii5423\_](https://www.instagram.com/adii5423_)

Made with ❤️ by Adii
