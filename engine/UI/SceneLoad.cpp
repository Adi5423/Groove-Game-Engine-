#include "SceneLoad.hpp"
#include "../Renderer/Framebuffer.hpp"
#include "../Utils/Logger.hpp"
#include "../Input/Input.hpp"
#include "../src/Camera.hpp"
#include "../src/Transform.hpp"
#include "../Renderer/Renderer.hpp"   // For DrawCube / SetCameraPerspective
#include <imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cfloat>

namespace Groove {

    std::unique_ptr<Camera> SceneLoad::s_Camera;
    std::unique_ptr<Framebuffer> SceneLoad::s_Framebuffer;
    std::vector<Transform> SceneLoad::s_Transforms;
    int SceneLoad::s_ViewportWidth = 1280;
    int SceneLoad::s_ViewportHeight = 720;
    bool SceneLoad::s_ViewportFocused = false;
    bool SceneLoad::s_ViewportHovered = false;

    void SceneLoad::Init() {
        s_Camera = std::make_unique<Camera>(45.0f, (float)s_ViewportWidth / (float)s_ViewportHeight, 0.1f, 100.0f);
        s_Camera->SetPosition({ 0.0f, 0.0f, 3.0f });

        s_Transforms.resize(2);
        s_Transforms[0].Position = { -1.5f, 0.0f, 0.0f };
        s_Transforms[1].Position = { 1.5f, 0.0f, 0.0f };
        s_Transforms[1].Rotation = { 0.0f, 45.0f, 0.0f };

        s_Framebuffer = std::make_unique<Framebuffer>();
        if (!s_Framebuffer->Create(s_ViewportWidth, s_ViewportHeight)) {
            Logger::Error("SceneLoad: Failed to create framebuffer");
        }
        else {
            Logger::Info("SceneLoad initialized.");
        }
    }

    void SceneLoad::Shutdown() {
        s_Framebuffer.reset();
        s_Camera.reset();
        s_Transforms.clear();
    }

    void SceneLoad::Update(float dt) {
        // Camera controls only when viewport has focus and is hovered
        if (s_ViewportFocused && s_ViewportHovered && Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
            glm::vec3 dir{};
            if (Input::IsKeyPressed(GLFW_KEY_W)) dir.z += 1.0f;
            if (Input::IsKeyPressed(GLFW_KEY_S)) dir.z -= 1.0f;
            if (Input::IsKeyPressed(GLFW_KEY_A)) dir.x -= 1.0f;
            if (Input::IsKeyPressed(GLFW_KEY_D)) dir.x += 1.0f;
            if (Input::IsKeyPressed(GLFW_KEY_E)) dir.y += 1.0f;
            if (Input::IsKeyPressed(GLFW_KEY_Q)) dir.y -= 1.0f;
            s_Camera->ProcessKeyboard(dir, dt);

            double dx, dy;
            Input::GetMouseDelta(dx, dy);
            s_Camera->ProcessMouseMovement((float)dx, (float)dy);
        }

        // Animate transforms
        if (s_Transforms.size() >= 2) {
            s_Transforms[0].Rotation.y += dt * 50.0f;
            s_Transforms[1].Rotation.y -= dt * 30.0f;
        }
    }

    void SceneLoad::RenderSceneToFramebuffer() {
        if (!s_Framebuffer) return;

        s_Framebuffer->Bind();

        // Set viewport to texture size
        glViewport(0, 0, s_Framebuffer->GetWidth(), s_Framebuffer->GetHeight());
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ensure renderer uses camera projection (we pass camera into SetCameraPerspective which should call glUniformMatrix or similar)
        Renderer::SetCameraPerspective(*s_Camera, (float)s_Framebuffer->GetWidth() / (float)s_Framebuffer->GetHeight());

        // Draw scene objects using your existing Renderer
        if (s_Transforms.size() >= 2) {
            Renderer::DrawCube(s_Transforms[0], *s_Camera);
            Renderer::DrawCube(s_Transforms[1], *s_Camera);
        }

        // Unbind back to default framebuffer
        Framebuffer::Unbind();
    }

    void SceneLoad::OnImGuiRender() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("3D Scene", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        s_ViewportFocused = ImGui::IsWindowFocused();
        s_ViewportHovered = ImGui::IsWindowHovered();

        ImVec2 avail = ImGui::GetContentRegionAvail();
        int newW = (int)avail.x;
        int newH = (int)avail.y;

        if (newW <= 0) newW = 1;
        if (newH <= 0) newH = 1;

        if (!s_Framebuffer || newW != s_Framebuffer->GetWidth() || newH != s_Framebuffer->GetHeight()) {
            // Recreate / resize framebuffer and update camera aspect
            if (!s_Framebuffer) s_Framebuffer = std::make_unique<Framebuffer>();
            s_Framebuffer->Resize(newW, newH);
            s_Camera->SetAspectRatio((float)newW / (float)newH);
        }

        // Render scene into the framebuffer
        RenderSceneToFramebuffer();

        // Now draw the framebuffer texture to ImGui
        uint32_t texId = s_Framebuffer ? s_Framebuffer->GetColorTexture() : 0u;
        ImGui::Image((void*)(intptr_t)texId, avail, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();
    }

} // namespace Groove
