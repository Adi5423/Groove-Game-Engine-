// UIManager.cpp
#include "UIManager.hpp"
#include <typeinfo>

namespace Groove {

    void UIManager::RegisterPanel(std::shared_ptr<UIPanel> panel) {
        if (panel) m_Panels.push_back(panel);
    }

    void UIManager::RenderPanels() {
        // Render Dockspace (if any) first, then the rest
        for (auto& p : m_Panels) {
            // heuristic: render the first one if it was registered first (Dockspace),
            // but to be safe we just render all in order
            p->OnImGuiRender();
        }
    }

}
