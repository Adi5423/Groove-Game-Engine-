#include "DefaultWindow.hpp"
#include <imgui.h>

namespace Groove {
    void DefaultWindow::OnImGuiRender() {
        ImGui::Begin("Default Window", nullptr, ImGuiWindowFlags_MenuBar);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Scene")) {}
                if (ImGui::MenuItem("Open Scene...")) {}
                if (ImGui::MenuItem("Save Scene")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Settings")) {
                ImGui::MenuItem("Preferences");
                ImGui::EndMenu();
            }
        }

        ImGui::EndMenuBar();
        ImGui::Text("This is the permanent menu bar window.");
        ImGui::End();
    }
}
