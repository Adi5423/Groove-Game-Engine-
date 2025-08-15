#include "SceneLoad.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Renderer/Framebuffer.hpp"
#include "../Utils/Logger.hpp"
#include "../Input/Input.hpp"
#include "../src/Window.hpp"
#include "../src/TimeStep.hpp"
#include "../src/Transform.hpp"
#include "../src/Camera.hpp"
#include "../src/MousePicker.hpp"
#include "../src/Intersection.hpp"

#include <imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cfloat>

namespace Groove {

    std::unique_ptr<Camera> SceneLoad::s_Camera;
    std::vector<Transform> SceneLoad::s_Transforms;
    uint32_t SceneLoad::s_Framebuffer = 0;
    int SceneLoad::s_ViewportWidth = 1280;
    int SceneLoad::s_ViewportHeight = 720;
    bool SceneLoad::s_ViewportFocused = false;
    bool SceneLoad::s_ViewportHovered = false;

    void SceneLoad::Init() {
        s_Camera = std::make_unique<Camera>(45.0f, (float)s_ViewportWidth / s_ViewportHeight, 0.1f, 100.0f);
        s_Camera->SetPosition({ 0.0f, 0.0f, 3.0f });

        s_Transforms.resize(2);
        s_Transforms[0].Position = { -1.5f, 0.0f, 0.0f };
        s_Transforms[1].Position = { 1.5f, 0.0f, 0.0f };
        s_Transforms[1].Rotation = { 0.0f, 45.0f, 0.0f };

        s_Framebuffer = Framebuffer::Create(s_ViewportWidth, s_ViewportHeight);

        Logger::Info("SceneLoad initialized.");
    }

    void SceneLoad::Shutdown() {
        if (s_Framebuffer)
            glDeleteFramebuffers(1, &s_Framebuffer);
        s_Camera.reset();
        s_Transforms.clear();
    }

    void SceneLoad::ResizeFramebuffer(int width, int height) {
        if (width > 0 && height > 0 &&
            (width != s_ViewportWidth || height != s_ViewportHeight)) {
            s_ViewportWidth = width;
            s_ViewportHeight = height;
            Framebuffer::Resize(s_Framebuffer, width, height);
            s_Camera->SetAspectRatio((float)width / height);
        }
    }

    void SceneLoad::Update(float dt) {
        // Camera controls
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

        // Animate scene objects
        s_Transforms[0].Rotation.y += dt * 50.0f;
        s_Transforms[1].Rotation.y -= dt * 30.0f;
    }

    void SceneLoad::RenderScene() {
        Framebuffer::Bind(s_Framebuffer);
        glViewport(0, 0, s_ViewportWidth, s_ViewportHeight);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Renderer::SetCameraPerspective(*s_Camera, (float)s_ViewportWidth / s_ViewportHeight);
        Renderer::DrawCube(s_Transforms[0], *s_Camera);
        Renderer::DrawCube(s_Transforms[1], *s_Camera);

        Framebuffer::Unbind();
    }

    void SceneLoad::OnImGuiRender() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("3D Scene", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        s_ViewportFocused = ImGui::IsWindowFocused();
        s_ViewportHovered = ImGui::IsWindowHovered();

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        ResizeFramebuffer((int)viewportPanelSize.x, (int)viewportPanelSize.y);

        RenderScene();

        uint32_t textureID = Framebuffer::GetColorAttachment(s_Framebuffer);
        ImGui::Image((void*)(intptr_t)textureID, viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();
    }

} // namespace Groove
