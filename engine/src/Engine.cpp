#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static GLFWwindow* window = nullptr;

void Engine::Init() {
    std::cout << "Initializing GLFW..." << std::endl;
    if (!glfwInit()) {
        std::cerr << "[Error] Failed to initialize GLFW!" << std::endl;
        return;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window = glfwCreateWindow(1280, 720, "Groove Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "[Error] Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "[Error] Failed to initialize GLAD!" << std::endl;
        return;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

void Engine::Run() {
    std::cout << "Entering main loop..." << std::endl;
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::Shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Shutdown complete." << std::endl;
}
