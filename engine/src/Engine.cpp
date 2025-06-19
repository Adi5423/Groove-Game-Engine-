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
#include <sstream>
#include <glm/gtc/type_ptr.hpp> // Include for glm::value_ptr

static Groove::Window* s_Window = nullptr;
static Groove::ImGuiLayer* s_ImGuiLayer = nullptr;

// Updated: m_Camera as static at file-scope
static Groove::Camera* m_Camera = nullptr;

// Helper function to convert glm::vec3 to string
static std::string Vec3ToString(const glm::vec3& vec) {
    std::ostringstream oss;
    oss << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return oss.str();
}

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
    m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f)); // Move camera back so it can see the cube

    s_ImGuiLayer = new Groove::ImGuiLayer();
    s_ImGuiLayer->Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));

    // Lock the cursor to the window
    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Engine::Run() {
    Groove::Logger::Info("Entering main loop...");

    float lastTime = (float)glfwGetTime();
    float logTimer = lastTime;
    bool cameraActive = true; // Track camera movement/rotation state

    Groove::Transform cubeTransform;

    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    while (!glfwWindowShouldClose(glfwWin)) {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Toggle camera control and cursor on ESC key press (edge detection)
        static bool escWasPressed = false;
        bool escPressed = Groove::Input::IsKeyPressed(GLFW_KEY_ESCAPE);
        if (escPressed && !escWasPressed) {
            cameraActive = !cameraActive;
            if (cameraActive) {
                glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            } else {
                glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
        escWasPressed = escPressed;

        // Only process camera movement/rotation if cameraActive
        if (cameraActive) {
            glm::vec3 direction{0.0f};
            if (Groove::Input::IsKeyPressed(GLFW_KEY_W)) direction.z += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_S)) direction.z -= 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_A)) direction.x -= 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_D)) direction.x += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_SPACE)) direction.y += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) direction.y -= 1.0f;
            m_Camera->ProcessKeyboard(direction, deltaTime);

            double dx, dy;
            Groove::Input::GetMouseDelta(dx, dy);
            m_Camera->ProcessMouseMovement((float)dx, (float)dy);
        }

        // 3) Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set a dark gray background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeTransform.Rotation.y += deltaTime * 50.0f; // 50° per sec

        Groove::Renderer::DrawCube(cubeTransform, *m_Camera);

        s_ImGuiLayer->Begin();

        ImGui::Begin("Groove Engine");
        ImGui::Text("Hello from ImGui!");
        ImGui::End();

        s_ImGuiLayer->End();

        // Improved logging: log camera and cube info every second
        if (currentTime - logTimer >= 1.0f) {
            logTimer = currentTime;
            std::ostringstream oss;
            glm::vec3 cameraPosition(
                m_Camera->GetViewMatrix()[3].x,
                m_Camera->GetViewMatrix()[3].y,
                m_Camera->GetViewMatrix()[3].z
            );
            oss << "Camera Position: " << Vec3ToString(cameraPosition)
                << " | Yaw: " << m_Camera->GetYaw()
                << " | Pitch: " << m_Camera->GetPitch()
                << " | Camera Active: " << (cameraActive ? "Yes" : "No");
            Groove::Logger::Info(oss.str());
            oss.str("");
            oss << "Cube Rotation Y: " << cubeTransform.Rotation.y;
            Groove::Logger::Info(oss.str());
        }

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