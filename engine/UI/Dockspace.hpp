#pragma once
#include "UIManager.hpp" // instead of "UIPanel.hpp"

namespace Groove {
    class Dockspace : public UIPanel {
    public:
        Dockspace() : UIPanel("Dockspace") {}
        void OnImGuiRender() override;
    };
}
