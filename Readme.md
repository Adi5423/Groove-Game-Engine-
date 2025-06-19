# ✨ Groove Game Engine

> **A next-gen modular C++ game engine**  
> Built with OpenGL, GLFW, ImGui, and CMake.  
> **Focus:** Realistic simulation, extensible core, and modern code.

---

<div align="center">
  <img src="resources/proof1.png" width="400" alt="Groove Engine Screenshot" />
  <br>
  <b>🚦 If you see a spinning 3D cube, you're ready to groove!</b>
</div>

---

## 🗂️ Project Structure

```text
Groove/
├─ engine/         # Core engine modules
│  ├─ Input/       # Input abstraction
│  ├─ Renderer/    # OpenGL, ImGui, shaders
│  ├─ Utils/       # Logger, helpers
│  └─ src/         # Engine, Window, Camera, TimeStep
├─ sandbox/        # Demo app (entry point)
├─ resources/      # Screenshots, shaders, textures
├─ out/            # CMake build output
├─ LICENSE.txt     # MIT License
├─ README.md       # This file
├─ Detailed_Guide.md # Deep-dive technical guide
└─ .gitignore
```

---

## 🚀 Features

| Subsystem         | Status | Highlights                                 |
|-------------------|:------:|--------------------------------------------|
| CMake Build       |   ✅   | Modular, multi-target                      |
| Windowing         |   ✅   | GLFW, VSync, resize                        |
| Input             |   ✅   | Keyboard, mouse, edge detection            |
| Logging           |   ✅   | Color console, file logs                   |
| Rendering         |   ✅   | OpenGL, VAO/VBO/IBO, shaders, 3D cube      |
| ImGui UI          |   ✅   | Overlay, debug panels                      |
| Delta Time        |   ✅   | TimeStep, smooth animation                 |
| Next Up           |   🔲   | ECS, events, scene, vehicles, roads        |

---

## 🛠️ Requirements

- **C++17** or newer
- **Visual Studio 2022** (Desktop C++)
- **CMake 3.21+**
- **vcpkg** (for dependencies)

```
vcpkg install glfw3 glad glm imgui[glfw-binding,opengl3-binding]
```

---

## ⚡ Quick Start

1. **Clone**
```
   git clone https://github.com/Adi5423/Groove-Game-Engine.git
   cd Groove-Game-Engine
```

2. **Configure (CMake)**
```
   cmake -S . -B out/build/windows-debug -G "Visual Studio 17 2022" -A x64 ^
     -DCMAKE_TOOLCHAIN_FILE="<VCPKG_PATH>/scripts/buildsystems/vcpkg.cmake"
```

3. **Build**
```
   cmake --build out/build/windows-debug --config Debug
```

4. **Run**
```
   ./out/build/windows-debug/sandbox/Sandbox.exe

```

---

## 🧩 Visual Studio Integration

- Open the root folder in Visual Studio.
- Edit and save any `CMakeLists.txt` to trigger CMake.
- Build with `Ctrl+Shift+B` or __Build > Rebuild All__.
- Run `Sandbox.exe` from the output directory.

---

## 🎮 Controls

- **W/A/S/D**: Move camera
- **Mouse**: Look around
- **ESC**: Toggle camera/cursor
- **Space/CTRL**: Move up/down

---

## 🖼️ Screenshots

| Output         | Preview                         |
|----------------|---------------------------------|
| proof1.png     | ![proof1](resources/proof1.png) |
| proof2.png  | ![proof2](resources/proof2.png) |

---

## 🗺️ Roadmap

- [x] Logging, Input, Window, Shaders, ImGui, 3D Cube
- [ ] ECS, Events, Scene, Vehicles, Roads

---

## 📜 License

MIT — see [`LICENSE.txt`](LICENSE.txt)

---

## 📬 Contact

- ✉️ [adii54ti23@gmail.com](mailto:adii54ti23@gmail.com)
- 💼 [LinkedIn](https://www.linkedin.com/in/aditya-tiwari-141731329/)
- 📸 [Instagram @adii5423_](https://www.instagram.com/adii5423_)

_Made with ❤️ by Adii_
