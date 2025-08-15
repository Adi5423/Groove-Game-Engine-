// ExamplePanel.cpp
#include "ExamplePanel.hpp"
#include <imgui.h>

namespace Groove {
    void ExamplePanel::OnImGuiRender() {
        ImGui::Begin("Groove Engine");
        ImGui::Text("Hello from Example Panel!");
        ImGui::End();
    }
}
