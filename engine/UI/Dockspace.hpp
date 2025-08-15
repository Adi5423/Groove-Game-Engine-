#pragma once
#include "UIPanel.hpp"
#include <memory>

namespace Groove {
    class DefaultWindow;
    class PrimaryWindow;

    class Dockspace : public UIPanel {
    public:
        Dockspace();
        void OnImGuiRender() override;

    private:
        std::shared_ptr<DefaultWindow> m_DefaultWindow;
        std::shared_ptr<PrimaryWindow> m_PrimaryWindow;
    };
}
