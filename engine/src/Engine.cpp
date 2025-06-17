// engine/src/Engine.cpp

#include "Engine.h"
#include "Window.h"               // ← Use the new window class
#include "TimeStep.h"  		// Added include for TimeStep
#include "../Renderer/Renderer.h"    // Added include for Renderer
#include "../Utils/Logger.h"
#include "../Input/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static Groove::Window* s_Window = nullptr;

void Engine::Init() {
    Groove::Logger::Init("Groove.log");
    s_Window = new Groove::Window(1280, 720, "Groove Engine");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Groove::Logger::Error("Failed to initialize GLAD!");
        return;
    }
    Groove::Input::Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));
    Groove::Renderer::Init();
}

void Engine::Run() {
    Groove::Logger::Info("Entering main loop...");

    // initialize lastTime once
    float lastTime = (float)glfwGetTime();

    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    while (!glfwWindowShouldClose(glfwWin)) {
        // compute delta
        float currentTime = (float)glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;
        Groove::TimeStep ts(delta);
        // optional: log every frame or every N frames
         Groove::Logger::Info("Delta: " + std::to_string(ts.GetMilliseconds()) + " ms");

        glClear(GL_COLOR_BUFFER_BIT);

        // your input tests, drawing, etc.
        if (Groove::Input::IsKeyPressed(GLFW_KEY_W))
            Groove::Logger::Info("W pressed");

        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) 
            Groove::Logger::Info("Left mouse button pressed");

        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) 
                Groove::Logger::Info("Right mouse button pressed");

        Groove::Renderer::DrawTriangle();

        s_Window->OnUpdate();
    }
}

void Engine::Shutdown() {
    Groove::Renderer::Shutdown();
    delete s_Window;
    Groove::Logger::Info("Shutdown complete.");
    Groove::Logger::Shutdown();
}
