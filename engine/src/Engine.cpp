// engine/src/Engine.cpp

#include "Engine.h"
#include "Window.h"
#include "TimeStep.h"
#include "../Renderer/Renderer.h"
#include "../Utils/Logger.h"
#include "../Input/Input.h"
#include "../Renderer/ImGuiLayer.h"
#include "Camera.h"
#include "Transform.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h> // Ensure ImGui is included for ImGui::Begin/End/Text

static Groove::Window* s_Window = nullptr;
static Groove::ImGuiLayer* s_ImGuiLayer = nullptr; // Added ImGuiLayer pointer

Groove::Camera* m_Camera; // Declare m_Camera as a private member variable  

void Engine::Init() {
    Groove::Logger::Init("Groove.log");
    s_Window = new Groove::Window(1280, 720, "Groove Engine");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Groove::Logger::Error("Failed to initialize GLAD!");
        return;
    }
    Groove::Input::Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));
    Groove::Renderer::Init();

    // Aspect ratio = width/height
    m_Camera = new Groove::Camera(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

    s_ImGuiLayer = new Groove::ImGuiLayer();
    s_ImGuiLayer->Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));
}

void Engine::Run() {
    Groove::Logger::Info("Entering main loop...");

    float lastTime = (float)glfwGetTime();
    
    // Initialize a cube transform for demonstration purposes 
    Groove::Transform cubeTransform;

    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    while (!glfwWindowShouldClose(glfwWin)) {
        float currentTime = (float)glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;
        Groove::TimeStep ts(delta);

        Groove::Logger::Info("Delta: " + std::to_string(ts.GetMilliseconds()) + " ms");

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (Groove::Input::IsKeyPressed(GLFW_KEY_W))
            Groove::Logger::Info("W pressed");

        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) 
            Groove::Logger::Info("Left mouse button pressed");

        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) 
            Groove::Logger::Info("Right mouse button pressed");

        // Rotate the cube
        cubeTransform.Rotation.y += ts.GetSeconds() * 50.0f; // 50° per sec

        // Draw the cube
        Groove::Renderer::DrawCube(cubeTransform, *m_Camera);

        s_ImGuiLayer->Begin();

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
    delete m_Camera; // Clean up camera
    Groove::Logger::Info("Shutdown complete.");
    Groove::Logger::Shutdown();
}
