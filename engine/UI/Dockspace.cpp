#include "Dockspace.hpp"
#include "DefaultWindow.hpp"
#include "PrimaryWindow.hpp"
#include <imgui.h>

namespace Groove {
    Dockspace::Dockspace()
        : UIPanel("Dockspace"),
        m_DefaultWindow(std::make_shared<DefaultWindow>()),
        m_PrimaryWindow(std::make_shared<PrimaryWindow>()) {
    }

    void Dockspace::OnImGuiRender() {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        ImGui::Begin("Dockspace Root", &dockspaceOpen, window_flags);

        if (opt_fullscreen) ImGui::PopStyleVar(2);

        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        // Render all sub-windows
        m_DefaultWindow->OnImGuiRender();
        m_PrimaryWindow->OnImGuiRender();

        ImGui::End();
    }
}
