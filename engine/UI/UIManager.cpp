#include "UIManager.hpp"
#include <imgui.h>

namespace Groove {

    void UIManager::RegisterPanel(std::shared_ptr<UIPanel> panel) {
        m_Panels.push_back(panel);
    }

    void UIManager::RenderPanels() {
        for (auto& panel : m_Panels)
            panel->OnImGuiRender();
    }

}
