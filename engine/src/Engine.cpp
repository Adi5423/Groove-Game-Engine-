// engine/src/Engine.cpp

#include "Engine.h"
#include "Window.h"
#include "TimeStep.h"
#include "../Renderer/Renderer.h"
#include "../Utils/Logger.h"
#include "../Input/Input.h"
#include "../Renderer/ImGuiLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h> // Ensure ImGui is included for ImGui::Begin/End/Text

static Groove::Window* s_Window = nullptr;
static Groove::ImGuiLayer* s_ImGuiLayer = nullptr; // Added ImGuiLayer pointer

void Engine::Init() {
    Groove::Logger::Init("Groove.log");
    s_Window = new Groove::Window(1280, 720, "Groove Engine");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Groove::Logger::Error("Failed to initialize GLAD!");
        return;
    }
    Groove::Input::Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));
    Groove::Renderer::Init();

    s_ImGuiLayer = new Groove::ImGuiLayer();
    s_ImGuiLayer->Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));
}

void Engine::Run() {
    Groove::Logger::Info("Entering main loop...");

    float lastTime = (float)glfwGetTime();

    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    while (!glfwWindowShouldClose(glfwWin)) {
        float currentTime = (float)glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;
        Groove::TimeStep ts(delta);

        Groove::Logger::Info("Delta: " + std::to_string(ts.GetMilliseconds()) + " ms");

        glClear(GL_COLOR_BUFFER_BIT);

        if (Groove::Input::IsKeyPressed(GLFW_KEY_W))
            Groove::Logger::Info("W pressed");

        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) 
            Groove::Logger::Info("Left mouse button pressed");

        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) 
            Groove::Logger::Info("Right mouse button pressed");

        s_ImGuiLayer->Begin();

        Groove::Renderer::DrawTriangle();

        ImGui::Begin("Groove Engine");
        ImGui::Text("Hello from ImGui!");
        ImGui::End();

        s_ImGuiLayer->End();

        s_Window->OnUpdate();
    }
}

void Engine::Shutdown() {
    s_ImGuiLayer->Shutdown();
    delete s_ImGuiLayer;
    Groove::Renderer::Shutdown();
    delete s_Window;
    Groove::Logger::Info("Shutdown complete.");
    Groove::Logger::Shutdown();
}
