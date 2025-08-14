#pragma once
#include "UIManager.hpp"

namespace Groove {

    class Dockspace : public UIPanel {
    public:
        void OnImGuiRender() override;
    };

} // namespace Groove
