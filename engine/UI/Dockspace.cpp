#include "Dockspace.hpp"
#include <imgui.h>

namespace Groove {
    void Dockspace::OnImGuiRender() {
        ImGui::Begin("Main Dockspace");

        // Just a demo button for now
        if (ImGui::Button("Hello!")) {
            // Handle button press
        }

        ImGui::End();
    }
}
