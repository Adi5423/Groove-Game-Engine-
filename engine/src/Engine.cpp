#include "Engine.h"
#include "../Utils/Logger.h" // Add this line
#include "../Input/Input.h"  // Added for input system

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static GLFWwindow* window = nullptr;

void Engine::Init() {
    Groove::Logger::Init("Groove.log"); // Initialize logger with optional file output

    Groove::Logger::Info("Initializing GLFW...");
    if (!glfwInit()) {
        Groove::Logger::Error("Failed to initialize GLFW!");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "Groove Engine", nullptr, nullptr);
    if (!window) {
        Groove::Logger::Error("Failed to create GLFW window!");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Groove::Logger::Error("Failed to initialize GLAD!");
        return;
    }

    Groove::Input::Init(window); // Initialize input system

    Groove::Logger::Info(std::string("OpenGL Version: ") + (const char*)glGetString(GL_VERSION));
}

void Engine::Run() {
    Groove::Logger::Info("Entering main loop...");
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TEMP: Input test logging
        if (Groove::Input::IsKeyPressed(GLFW_KEY_W)) {
            Groove::Logger::Info("W key pressed");
        }

        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            Groove::Logger::Info("Left mouse button pressed");
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


void Engine::Shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
    Groove::Logger::Info("Shutdown complete.");
    Groove::Logger::Shutdown();
}
