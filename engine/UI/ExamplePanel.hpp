// ExamplePanel.hpp
#pragma once
#include "UIManager.hpp"

namespace Groove {
    class ExamplePanel : public UIPanel {
    public:
        ExamplePanel() : UIPanel("ExamplePanel") {}
        void OnImGuiRender() override;
    };
}
