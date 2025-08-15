// engine/src/Engine.cpp

#include "Engine.hpp"
#include "Window.hpp"
#include "TimeStep.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Utils/Logger.hpp"
#include "../Input/input.hpp"
#include "../Renderer/ImGuiLayer.hpp"
#include "../UI/UIManager.hpp"
#include "../UI/ExamplePanel.hpp"
#include "../UI/Dockspace.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "MousePicker.hpp"
#include "Intersection.hpp" // Added this to include RayIntersectsAABB
#include <cfloat> // For FLT_MAX
#include <ctime>
#include "Events/Event.hpp" // Add this include to ensure the definition of Groove::Event is available

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h> // Ensure ImGui is included for ImGui::Begin/End/Text
#include <sstream>
#include <glm/gtc/type_ptr.hpp> // Include for glm::value_ptr
#include <vector> // Required for std::vector

static Groove::Window* s_Window = nullptr;
static Groove::ImGuiLayer* s_ImGuiLayer = nullptr;
static Groove::UIManager* s_UIManager = nullptr;

// Updated: m_Camera as static at file-scope
static Groove::Camera* m_Camera = nullptr;

// Store transforms in a vector for picking (file-scope)
static std::vector<Groove::Transform> m_Transforms;

// File System
//namespace fs = Groove::Core;

// Helper function to convert glm::vec3 to string
static std::string Vec3ToString(const glm::vec3& vec) {
    std::ostringstream oss;
    oss << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return oss.str();
}

void Engine::Init() {
    Groove::Logger::Init("Groove.log");
    s_Window = new Groove::Window(1280, 720, "Groove Engine");

    // Event callback logging
    s_Window->SetEventCallback([](Groove::Event& e) {
        Groove::Logger::Info("Event: " + e.ToString());
        });

    // Init OpenGL loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Groove::Logger::Error("Failed to initialize GLAD!");
        return;
    }

    Groove::Input::Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));
    Groove::Renderer::Init();

    // Camera setup
    m_Camera = new Groove::Camera(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    m_Camera->SetPosition({ 0.0f, 0.0f, 3.0f });

    // ImGui setup (once)
    s_ImGuiLayer = new Groove::ImGuiLayer();
    s_ImGuiLayer->Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));

    // UIManager setup (once)
    s_UIManager = new Groove::UIManager();
    s_UIManager->RegisterPanel(std::make_shared<Groove::Dockspace>());
    s_UIManager->RegisterPanel(std::make_shared<Groove::ExamplePanel>());

    // Lock cursor initially
    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize cube transforms
    m_Transforms.resize(2);
    m_Transforms[0].Position = { -1.5f, 0.0f, 0.0f };
    m_Transforms[1].Position = { 1.5f, 0.0f, 0.0f };
    m_Transforms[1].Rotation = { 0.0f, 45.0f, 0.0f };
}

void Engine::Run() {
    Groove::Logger::Info("Entering main loop...");

    float lastTime = (float)glfwGetTime();
    float logTimer = lastTime;

    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    while (!glfwWindowShouldClose(glfwWin)) {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Camera controls
        bool rightMouseHeld = Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT);
        if (rightMouseHeld) {
            glm::vec3 dir{};
            if (Groove::Input::IsKeyPressed(GLFW_KEY_W)) dir.z += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_S)) dir.z -= 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_A)) dir.x -= 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_D)) dir.x += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_E)) dir.y += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_Q)) dir.y -= 1.0f;
            m_Camera->ProcessKeyboard(dir, deltaTime);

            double dx, dy;
            Groove::Input::GetMouseDelta(dx, dy);
            m_Camera->ProcessMouseMovement((float)dx, (float)dy);
        }
        else {
            double dx, dy;
            Groove::Input::GetMouseDelta(dx, dy); // consume delta
        }

        // Mouse picking (simplified)
#if __cplusplus >= 201703L
        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            auto [origin, dir] = CastRayFromMouse(*m_Camera, *s_Window);
            float closestT = FLT_MAX;
            int hitIndex = -1;

            for (int i = 0; i < (int)m_Transforms.size(); i++) {
                const auto& T = m_Transforms[i];
                glm::vec3 half = T.Scale * 0.5f;
                glm::vec3 min = T.Position - half;
                glm::vec3 max = T.Position + half;
                float t;
                if (Groove::RayIntersectsAABB(origin, dir, min, max, t) && t < closestT) {
                    closestT = t;
                    hitIndex = i;
                }
            }

            if (hitIndex >= 0) {
                Groove::Logger::Info("Clicked object #" + std::to_string(hitIndex));
            }
        }
#endif

        // Clear screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rotate cubes
        m_Transforms[0].Rotation.y += deltaTime * 50.0f;
        m_Transforms[1].Rotation.y -= deltaTime * 30.0f;

        // Render scene
        Groove::Renderer::DrawCube(m_Transforms[0], *m_Camera);
        Groove::Renderer::DrawCube(m_Transforms[1], *m_Camera);

        // ImGui
        s_ImGuiLayer->Begin();
        s_UIManager->RenderPanels();
        s_ImGuiLayer->End();

        // Logging every second
        if (currentTime - logTimer >= 1.0f) {
            logTimer = currentTime;
            glm::vec3 camPos(
                m_Camera->GetViewMatrix()[3].x,
                m_Camera->GetViewMatrix()[3].y,
                m_Camera->GetViewMatrix()[3].z
            );
            Groove::Logger::Info(
                "Camera Pos: " + Vec3ToString(camPos) +
                " | Yaw: " + std::to_string(m_Camera->GetYaw()) +
                " | Pitch: " + std::to_string(m_Camera->GetPitch()) +
                " | Camera Active: " + std::string(rightMouseHeld ? "Yes" : "No")
            );
            Groove::Logger::Info("Cube1 Rot Y: " + std::to_string(m_Transforms[0].Rotation.y));
            Groove::Logger::Info("Cube2 Rot Y: " + std::to_string(m_Transforms[1].Rotation.y));
        }

        // Swap buffers & poll events
        s_Window->OnUpdate();
    }
}

void Engine::Shutdown() {
    s_ImGuiLayer->Shutdown();
    delete s_ImGuiLayer;
    delete s_UIManager;
    delete m_Camera;
    Groove::Renderer::Shutdown();
    delete s_Window;
    Groove::Logger::Info("Shutdown complete.");
    Groove::Logger::Shutdown();
}
