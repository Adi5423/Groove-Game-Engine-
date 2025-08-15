#pragma once
#include "UIPanel.hpp"

namespace Groove {
    class PrimaryWindow : public UIPanel {
    public:
        PrimaryWindow() : UIPanel("Primary Window") {}
        void OnImGuiRender() override;
    };
}
