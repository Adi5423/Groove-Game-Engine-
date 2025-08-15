#include "PrimaryWindow.hpp"
#include "SceneLoad.hpp"
#include <imgui.h>

namespace Groove {

    void PrimaryWindow::OnImGuiRender() {
        ImGui::Begin("Hierarchy");
        ImGui::Text("Entity 1");
        ImGui::Text("Entity 2");
        ImGui::End();

        SceneLoad::OnImGuiRender(); // 3D Scene dockable tab

        ImGui::Begin("Properties");
        ImGui::Text("Selected Object Properties...");
        ImGui::End();

        ImGui::Begin("Content Browser");
        ImGui::Text("Assets go here...");
        ImGui::End();
    }

}
