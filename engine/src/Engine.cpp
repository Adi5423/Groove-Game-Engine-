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
#include "MousePicker.hpp"
#include "Intersection.hpp" // Added this to include RayIntersectsAABB
#include <cfloat> // For FLT_MAX

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h> // Ensure ImGui is included for ImGui::Begin/End/Text
#include <ImGuizmo.h> // ImGuizmo for 3D gizmos
#include <sstream>
#include <glm/gtc/type_ptr.hpp> // Include for glm::value_ptr
#include <glm/gtx/matrix_decompose.hpp> // For decomposing matrices
#include <vector> // Required for std::vector

static Groove::Window* s_Window = nullptr;
static Groove::ImGuiLayer* s_ImGuiLayer = nullptr;

// Updated: m_Camera as static at file-scope
static Groove::Camera* m_Camera = nullptr;

// Store transforms in a vector for picking (file-scope)
static std::vector<Groove::Transform> m_Transforms;

// Selection and gizmo state
static int s_SelectedIndex = -1; // -1 means no selection
static ImGuizmo::OPERATION s_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
static ImGuizmo::MODE s_CurrentGizmoMode = ImGuizmo::LOCAL;
static bool s_WasLeftClickPressed = false; // For click-once detection

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

    // Initialize transforms only once
    if (m_Transforms.empty()) {
        m_Transforms.push_back(Groove::Transform());
        m_Transforms.push_back(Groove::Transform());

        m_Transforms[0].Position = glm::vec3(-1.5f, 0.0f, 0.0f); // Left
        m_Transforms[0].Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

        m_Transforms[1].Position = glm::vec3(1.5f, 0.0f, 0.0f); // Right
        m_Transforms[1].Rotation = glm::vec3(0.0f, 45.0f, 0.0f);
    }

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
            if (Groove::Input::IsKeyPressed(GLFW_KEY_E)) direction.y += 1.0f; // Up
            if (Groove::Input::IsKeyPressed(GLFW_KEY_Q)) direction.y -= 1.0f; // Down
            m_Camera->ProcessKeyboard(direction, deltaTime);

            double dx, dy;
            Groove::Input::GetMouseDelta(dx, dy);
            m_Camera->ProcessMouseMovement((float)dx, (float)dy);
        } else {
            // Optionally, reset mouse delta so camera doesn't jump when RMB is pressed again
            double dx, dy;
            Groove::Input::GetMouseDelta(dx, dy); // Consume delta
            
            // Keyboard shortcuts for gizmo modes (only when not moving camera)
            if (Groove::Input::IsKeyPressed(GLFW_KEY_W) && s_SelectedIndex >= 0) {
                s_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
            }
            if (Groove::Input::IsKeyPressed(GLFW_KEY_E) && s_SelectedIndex >= 0) {
                s_CurrentGizmoOperation = ImGuizmo::ROTATE;
            }
            if (Groove::Input::IsKeyPressed(GLFW_KEY_R) && s_SelectedIndex >= 0) {
                s_CurrentGizmoOperation = ImGuizmo::SCALE;
            }
        }

        // Mouse picking logic - click once to select/deselect
        bool leftClickNow = Groove::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
        bool leftClickJustPressed = leftClickNow && !s_WasLeftClickPressed;
        s_WasLeftClickPressed = leftClickNow;

        // Only process selection if we just clicked AND gizmo is not being used
        if (leftClickJustPressed && !ImGuizmo::IsOver()) {
#if __cplusplus >= 201703L
            auto [origin, dir] = CastRayFromMouse(*m_Camera, *s_Window);
#else
            auto ray = CastRayFromMouse(*m_Camera, *s_Window);
            auto& origin = ray.first;
            auto& dir = ray.second;
#endif
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
                // Select the clicked object
                s_SelectedIndex = hitIndex;
                Groove::Logger::Info("Selected object #" + std::to_string(hitIndex));
            } else {
                // Clicked empty space - deselect
                if (s_SelectedIndex >= 0) {
                    Groove::Logger::Info("Deselected object");
                }
                s_SelectedIndex = -1;
            }
        }

        // 3) Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set a dark gray background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Only animate cubes that are NOT selected (so user can manipulate freely)
        for (int i = 0; i < (int)m_Transforms.size(); i++) {
            if (i != s_SelectedIndex) {
                // Original animation logic
                if (i == 0) m_Transforms[i].Rotation.y += deltaTime * 50.0f;
                else m_Transforms[i].Rotation.y -= deltaTime * 30.0f;
            }
        }

        Groove::Renderer::DrawCube(m_Transforms[0], *m_Camera);
        Groove::Renderer::DrawCube(m_Transforms[1], *m_Camera);

        s_ImGuiLayer->Begin();

        // Initialize ImGuizmo for this frame
        ImGuizmo::BeginFrame();
        ImGuizmo::SetOrthographic(false);
        
        // Set ImGuizmo to render on the background draw list (over the 3D scene)
        ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
        
        // Set the rect to cover the entire screen
        ImGuiIO& io = ImGui::GetIO();
        ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

        // Draw gizmo if an object is selected
        if (s_SelectedIndex >= 0 && s_SelectedIndex < (int)m_Transforms.size()) {
            glm::mat4 view = m_Camera->GetViewMatrix();
            glm::mat4 proj = m_Camera->GetProjectionMatrix();
            glm::mat4 model = m_Transforms[s_SelectedIndex].GetMatrix();

            // Draw and manipulate the gizmo
            ImGuizmo::Manipulate(
                glm::value_ptr(view),
                glm::value_ptr(proj),
                s_CurrentGizmoOperation,
                s_CurrentGizmoMode,
                glm::value_ptr(model)
            );

            // If gizmo was used, decompose the matrix back to position/rotation/scale
            if (ImGuizmo::IsUsing()) {
                glm::vec3 translation, rotation, scale;
                ImGuizmo::DecomposeMatrixToComponents(
                    glm::value_ptr(model),
                    glm::value_ptr(translation),
                    glm::value_ptr(rotation),
                    glm::value_ptr(scale)
                );
                m_Transforms[s_SelectedIndex].Position = translation;
                m_Transforms[s_SelectedIndex].Rotation = rotation;
                m_Transforms[s_SelectedIndex].Scale = scale;
            }
        }

        ImGui::Begin("Groove Engine");
        ImGui::Text("Hello from ImGui!");
        ImGui::Separator();
        ImGui::Text("Selection: %s", s_SelectedIndex >= 0 ? ("Object #" + std::to_string(s_SelectedIndex)).c_str() : "None");
        if (s_SelectedIndex >= 0) {
            ImGui::Text("Gizmo Mode: %s", 
                s_CurrentGizmoOperation == ImGuizmo::TRANSLATE ? "Translate (W)" :
                s_CurrentGizmoOperation == ImGuizmo::ROTATE ? "Rotate (E)" : "Scale (R)");
            ImGui::Text("Position: %.2f, %.2f, %.2f", 
                m_Transforms[s_SelectedIndex].Position.x,
                m_Transforms[s_SelectedIndex].Position.y,
                m_Transforms[s_SelectedIndex].Position.z);
            ImGui::Text("Rotation: %.2f, %.2f, %.2f", 
                m_Transforms[s_SelectedIndex].Rotation.x,
                m_Transforms[s_SelectedIndex].Rotation.y,
                m_Transforms[s_SelectedIndex].Rotation.z);
            ImGui::Text("Scale: %.2f, %.2f, %.2f", 
                m_Transforms[s_SelectedIndex].Scale.x,
                m_Transforms[s_SelectedIndex].Scale.y,
                m_Transforms[s_SelectedIndex].Scale.z);
        }
        ImGui::Separator();
        ImGui::Text("Controls:");
        ImGui::Text("  Left Click: Select/Deselect");
        ImGui::Text("  W/E/R: Translate/Rotate/Scale");
        ImGui::Text("  Right Click + Mouse: Camera");
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
            oss << "Cube1 Rotation Y: " << m_Transforms[0].Rotation.y;
            Groove::Logger::Info(oss.str());
            oss.str("");
            oss << "Cube2 Rotation Y: " << m_Transforms[1].Rotation.y;
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