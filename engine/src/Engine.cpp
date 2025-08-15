// engine/src/Engine.cpp
#include "Engine.hpp"
#include "Window.hpp"
#include "TimeStep.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Utils/Logger.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/ImGuiLayer.hpp"
#include "../UI/UIManager.hpp"
#include "../UI/ExamplePanel.hpp"
#include "../UI/Dockspace.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "MousePicker.hpp"
#include "Intersection.hpp"
#include <cfloat>
#include <ctime>
#include "Events/Event.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

static Groove::Window* s_Window = nullptr;
static Groove::ImGuiLayer* s_ImGuiLayer = nullptr;
static Groove::UIManager* s_UIManager = nullptr;
static Groove::Camera* m_Camera = nullptr;
static std::vector<Groove::Transform> m_Transforms;

static std::string Vec3ToString(const glm::vec3& v) {
    std::ostringstream oss; oss << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return oss.str();
}

void Engine::Init() {
    Groove::Logger::Init("Groove.log");
    s_Window = new Groove::Window(1280, 720, "Groove Engine");

    s_Window->SetEventCallback([](Groove::Event& e) {
        Groove::Logger::Info("Event: " + e.ToString());
        });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Groove::Logger::Error("Failed to initialize GLAD!");
        return;
    }

    Groove::Input::Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));
    Groove::Renderer::Init();

    // Camera
    m_Camera = new Groove::Camera(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    m_Camera->SetPosition({ 0.0f, 0.0f, 3.0f });

    // ImGui once
    s_ImGuiLayer = new Groove::ImGuiLayer();
    s_ImGuiLayer->Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));

    // UIManager once — register Dockspace FIRST (real instance, not null)
    s_UIManager = new Groove::UIManager();
    s_UIManager->RegisterPanel(std::make_shared<Groove::Dockspace>());
    s_UIManager->RegisterPanel(std::make_shared<Groove::ExamplePanel>());

    // Initial cursor mode
    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Scene
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
        float now = (float)glfwGetTime();
        float dt = now - lastTime;
        lastTime = now;

        // Camera controls (RMB)
        bool rmb = Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT);
        if (rmb) {
            glm::vec3 dir{};
            if (Groove::Input::IsKeyPressed(GLFW_KEY_W)) dir.z += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_S)) dir.z -= 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_A)) dir.x -= 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_D)) dir.x += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_E)) dir.y += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_Q)) dir.y -= 1.0f;
            m_Camera->ProcessKeyboard(dir, dt);

            double dx, dy;
            Groove::Input::GetMouseDelta(dx, dy);
            m_Camera->ProcessMouseMovement((float)dx, (float)dy);
        }
        else {
            double dx, dy; Groove::Input::GetMouseDelta(dx, dy); // consume
        }

#if __cplusplus >= 201703L
        if (Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            auto [origin, dir] = CastRayFromMouse(*m_Camera, *s_Window);
            float closestT = FLT_MAX; int hit = -1;
            for (int i = 0; i < (int)m_Transforms.size(); ++i) {
                const auto& T = m_Transforms[i];
                glm::vec3 half = T.Scale * 0.5f;
                glm::vec3 mn = T.Position - half, mx = T.Position + half;
                float t;
                if (Groove::RayIntersectsAABB(origin, dir, mn, mx, t) && t < closestT) { closestT = t; hit = i; }
            }
            if (hit >= 0) Groove::Logger::Info("Clicked object #" + std::to_string(hit));
        }
#endif

        // Keep GL viewport + camera aspect in sync with framebuffer
        int fbw = 0, fbh = 0;
        glfwGetFramebufferSize(glfwWin, &fbw, &fbh);
        if (fbw > 0 && fbh > 0) {
            glViewport(0, 0, fbw, fbh);
            Groove::Renderer::SetCameraPerspective(*m_Camera, (float)fbw / (float)fbh);
        }

        // 1) Clear & render scene (shows through dockspace central area)
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Transforms[0].Rotation.y += dt * 50.0f;
        m_Transforms[1].Rotation.y -= dt * 30.0f;

        Groove::Renderer::DrawCube(m_Transforms[0], *m_Camera);
        Groove::Renderer::DrawCube(m_Transforms[1], *m_Camera);

        // 2) ImGui pass
        s_ImGuiLayer->Begin();
        s_UIManager->RenderPanels();     // Dockspace first (UIManager ensures order)
        s_ImGuiLayer->End();

        // Periodic logs
        if (now - logTimer >= 1.0f) {
            logTimer = now;
            glm::vec3 camPos(
                m_Camera->GetViewMatrix()[3].x,
                m_Camera->GetViewMatrix()[3].y,
                m_Camera->GetViewMatrix()[3].z
            );
            Groove::Logger::Info(
                "Camera Pos: " + Vec3ToString(camPos) +
                " | Yaw: " + std::to_string(m_Camera->GetYaw()) +
                " | Pitch: " + std::to_string(m_Camera->GetPitch()) +
                " | Camera Active: " + std::string(rmb ? "Yes" : "No")
            );
        }

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
