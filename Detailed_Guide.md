<p align="center">
  <img src="resources/proof1.png" alt="Groove Engine Cube" width="120"/>
</p>

<h1 align="center">📝 Detailed Guide: Groove Game Engine</h1>

---

## 📚 Table of Content
- [🏗️ Architecture Overview](#-architecture-overview)
- [🖥️ Engine Initialization & Main Loop](#-engine-initialization--main-loop)
- [🎮 Input & Camera System](#-input--camera-system)
- [🖌️ Rendering Pipeline](#-rendering-pipeline)
- [🧩 ImGui Integration](#-imgui-integration)
- [📝 Logging & Debugging](#-logging--debugging)
- [⚙️ Build System (CMake & vcpkg)](#-build-system-cmake--vcpkg)
- [🔍 Code Walkthrough & Core Mechanics](#-code-walkthrough--core-mechanics)
- [🔗 References & Further Reading](#-references--further-reading)

---

## 🏗️ Architecture Overview

- **Engine Core**: Orchestrates all subsystems (window, input, renderer, camera, ImGui, logger).
- **Window**: Abstracts GLFW window creation, VSync, and event polling.
- **Input**: Centralizes keyboard/mouse state, edge detection, and mouse deltas.
- **Renderer**: Handles OpenGL context, shaders, and all draw calls (3D cube, ImGui).
- **Camera**: Free-fly camera with position, yaw, pitch, and movement logic.
- **ImGui Layer**: Integrates ImGui for real-time UI and debugging.
- **Logger**: Thread-safe, color-coded logging to file and console.
- **Transform**: Simple struct for position, rotation, and scale.

---

## 🖥️ Engine Initialization & Main Loop

### Initialization (`Engine::Init`)
- Logger starts first to capture all events.
- Window is created (GLFW), OpenGL context is set up (GLAD).
- Input is initialized and hooked to the window.
- Renderer is set up, including OpenGL state and resources.
- Camera is created and positioned to view the scene.
- ImGui Layer is initialized after OpenGL context is ready.
- Cursor is locked for immersive camera control.

### Main Loop (`Engine::Run`)
- Delta time is calculated each frame for smooth movement and animation.
- Input is polled: keyboard for movement, mouse for camera look, ESC for toggling camera/cursor.
- Camera processes input only when active, updating position and orientation.
- Scene is rendered: screen is cleared, cube is rotated and drawn, ImGui overlays are rendered.
- Logging: Every second, camera and cube state are logged for debugging.
- Window swaps buffers and polls events.

### Shutdown (`Engine::Shutdown`)
- ImGui Layer is shut down and deleted.
- Renderer is cleaned up.
- Window and Camera are deleted.
- Logger writes final messages and closes.

---

## 🎮 Input & Camera System

- **Input**: Abstracted for easy extension; supports polling and edge detection.
- **Camera**: WASD/Space/CTRL for 3D navigation, mouse for look.
- **ESC**: Toggles between camera control (cursor locked) and UI mode (cursor visible).
- **Mouse Delta**: Used for smooth, frame-rate-independent camera rotation.

---

## 🖌️ Rendering Pipeline

- **Renderer**: Initialized after OpenGL context is ready.
- **DrawCube**: Uses current transform and camera view/projection.
- **ImGui**: Rendered after the 3D scene, allowing real-time UI and debug panels.
- **Transform**: Used for all scene objects (currently, the rotating cube).

---

## 🧩 ImGui Integration

- **ImGuiLayer**: Handles all ImGui setup, frame begin/end, and shutdown.
- **Panels**: Custom panels (e.g., "Groove Engine") for engine state, debug info, or tools.
- **Initialization**: Only after OpenGL context is valid.

---

## 📝 Logging & Debugging

- **Logger**: Always available, capturing info, warnings, and errors.
- **Color-coded**: Console output and file logging.
- **State Logging**: Camera position, cube rotation, and other key info logged every second.

---

## ⚙️ Build System (CMake & vcpkg)

- **CMake**: Modular, supports Ninja and Visual Studio generators.
- **vcpkg**: Manages all third-party dependencies (GLFW, GLAD, GLM, ImGui).
- **Minimum CMake**: 3.21 for modern features and compatibility.
- **Visual Studio**: Open the root folder, edit CMake, and build.

---

## 🔍 Code Walkthrough & Core Mechanics

### Engine Startup
- See [`engine/src/Engine.cpp`](engine/src/Engine.cpp) for the full lifecycle.
- `Engine::Init()` sets up all subsystems in order.
- `Engine::Run()` is the main loop, handling input, camera, rendering, ImGui, and logging.
- `Engine::Shutdown()` cleans up everything in reverse order.

### Input & Camera
- Input is polled every frame (`Groove::Input::IsKeyPressed`).
- Camera movement and rotation are handled in the main loop, only when camera is active.
- Mouse delta is used for smooth camera look (`Groove::Input::GetMouseDelta`).

### Rendering
- Renderer is initialized after OpenGL context is ready.
- `Groove::Renderer::DrawCube` draws a 3D cube using the current transform and camera.
- ImGui overlays are rendered after the 3D scene.

### ImGui
- ImGuiLayer wraps all ImGui setup, frame begin/end, and shutdown.
- Panels can be extended for real-time debug info.

### Logging
- Logger is initialized first and shut down last.
- Logs are written every second with camera and cube state.

---

## 🔗 References & Further Reading

- [GLFW Documentation](https://www.glfw.org/docs/latest/)
- [GLAD OpenGL Loader](https://glad.dav1d.de/)
- [ImGui](https://github.com/ocornut/imgui)
- [GLM Mathematics](https://github.com/g-truc/glm)
- [CMake Documentation](https://cmake.org/cmake/help/latest/)

---

> For further details, see the source code and comments in the `engine/` and `sandbox/` directories. This guide is meant to provide both a high-level overview and a deep technical reference for anyone wishing to understand or extend the Groove Game Engine.

_Made with ❤️ by Adii_