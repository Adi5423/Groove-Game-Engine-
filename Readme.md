﻿# 🎮 Groove Game Engine

> **Next‑gen modular C++ engine** built with OpenGL, GLFW, and CMake.  
> Focus: Realistic roads & vehicles (future), solid core systems today.

## 🚧 Implemented the 3D Cube Renderer and it's shaders (rotating cube animation) , working perfectly.
> **If u see a 3d cube in red color everything working perfectly 
> can also Check left , right mouse button and W key pressing , it tracks that. :) i added a lot.

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
      git clone https://github.com/Adi5423/Groove-Game-Engine.git 
      cd Groove-Game-Engine
   ```

2. **Configure**
   ```bash
      cmake -S . -B out/build/windows-debug -G "Visual Studio 17 2022" -A x64 \
      -DCMAKE_TOOLCHAIN_FILE="<VCPKG_PATH_Entered-While-Installation>/scripts/buildsystems/vcpkg.cmake"
   ````

3. **Build**

   ```bash
      cmake --build out/build/windows-debug --config Debug
   ```


4. **Run**
```bash
./out/build/windows-debug/sandbox/Sandbox.exe
````

---

## ✅ If u have Visual Studio Installed.

> Tip: If u have Visual Studio Installed follow this after installing VCPKG as mentioned above , just vcpkg installation then this approach , if having Visual Studio.

0. **Open the cloned folder in Visual Studio.**

   ```text
	first , just open any the CMakeLists.txt , remove any letter from file then save , then Undo(Ctrl+Z) then save again.
	This will generate the CMakeBuild Files , ready to Build and Test.
   ```

   ```text
	If u see CMake Generated Finished in Visual Studio , good to for Build.
	Press "Ctrl+Shift+B" or can do -> Press Build in topbar -> then press Rebuild or Build All.
	Following any of step will generate the build files to run the final Exe.

	If All Build Successfull , the exe will be in the lcoation - Groove-Game-Engine(root)\out\build\windows-debug\sandbox\Sandbox.exe

	Run the if encounter any error in anywhere , either mail or mess me personally with that. 

	Will update the Readme , with perfect build steps detaile soon.
   ```

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
