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

    Groove::Transform cube1;
    Groove::Transform cube2;

    cube1.Position = glm::vec3(-1.5f, 0.0f, 0.0f); // Left
    cube1.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    cube2.Position = glm::vec3(1.5f, 0.0f, 0.0f); // Right
    cube2.Rotation = glm::vec3(0.0f, 45.0f, 0.0f); // Rotated 45° on Y

    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());

    // Always show the cursor
    glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    while (!glfwWindowShouldClose(glfwWin)) {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Only process camera movement/rotation if right mouse button is held
        bool rightMouseHeld = Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT);

        if (rightMouseHeld) {
            glm::vec3 direction{0.0f};
            if (Groove::Input::IsKeyPressed(GLFW_KEY_W)) direction.z += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_S)) direction.z -= 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_A)) direction.x -= 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_D)) direction.x += 1.0f;
            if (Groove::Input::IsKeyPressed(GLFW_KEY_Q)) direction.y += 1.0f; // Up
            if (Groove::Input::IsKeyPressed(GLFW_KEY_E)) direction.y -= 1.0f; // Down
            m_Camera->ProcessKeyboard(direction, deltaTime);

            double dx, dy;
            Groove::Input::GetMouseDelta(dx, dy);
            m_Camera->ProcessMouseMovement((float)dx, (float)dy);
        } else {
            // Optionally, reset mouse delta so camera doesn't jump when RMB is pressed again
            double dx, dy;
            Groove::Input::GetMouseDelta(dx, dy); // Consume delta
        }

        // 3) Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set a dark gray background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Animate both cubes (optional: rotate both)
        cube1.Rotation.y += deltaTime * 50.0f;
        cube2.Rotation.y -= deltaTime * 30.0f;

        Groove::Renderer::DrawCube(cube1, *m_Camera);
        Groove::Renderer::DrawCube(cube2, *m_Camera);

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
                << " | Camera Active: " << (rightMouseHeld ? "Yes" : "No");
            Groove::Logger::Info(oss.str());
            oss.str("");
            oss << "Cube1 Rotation Y: " << cube1.Rotation.y;
            Groove::Logger::Info(oss.str());
            oss.str("");
            oss << "Cube2 Rotation Y: " << cube2.Rotation.y;
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