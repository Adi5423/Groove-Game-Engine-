#pragma once
#include "UIPanel.hpp"

namespace Groove {
    class DefaultWindow : public UIPanel {
    public:
        DefaultWindow() : UIPanel("Default Window") {}
        void OnImGuiRender() override;
    };
}
