// engine/src/Engine.cpp

#include "Engine.h"
#include "Window.h"               // ← Use the new window class
#include "../Utils/Logger.h"
#include "../Input/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static Groove::Window* s_Window = nullptr;

void Engine::Init() {
    Groove::Logger::Init("Groove.log");

    s_Window = new Groove::Window(1280, 720, "Groove Engine");

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Groove::Logger::Error("Failed to initialize GLAD!");
        return;
    }

    Groove::Input::Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));

    Groove::Logger::Info(std::string("OpenGL Version: ") + (const char*)glGetString(GL_VERSION));
}

void Engine::Run() {
    Groove::Logger::Info("Entering main loop...");

    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());

    while (!glfwWindowShouldClose(glfwWin)) {
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TEMP: Input test logging
        if (Groove::Input::IsKeyPressed(GLFW_KEY_W)) {
            Groove::Logger::Info("W key pressed");
        }

        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            Groove::Logger::Info("Left mouse button pressed");
        }

        s_Window->OnUpdate(); // Handles buffer swap and polling
    }
}

void Engine::Shutdown() {
    delete s_Window;
    s_Window = nullptr;

    Groove::Logger::Info("Shutdown complete.");
    Groove::Logger::Shutdown();
}
