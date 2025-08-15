// UIManager.hpp
#pragma once
#include <vector>
#include <memory>
#include "UIPanel.hpp"

namespace Groove {

    class UIManager {
    public:
        void RegisterPanel(std::shared_ptr<UIPanel> panel);
        void RenderPanels();

    private:
        std::vector<std::shared_ptr<UIPanel>> m_Panels;
    };

}
