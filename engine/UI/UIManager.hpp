// UIManager.hpp
#pragma once
#include <vector>
#include <memory>

namespace Groove {

    class UIPanel {
    public:
        explicit UIPanel(const char* /*name*/ = "") {}
        virtual ~UIPanel() = default;
        virtual void OnImGuiRender() = 0;
    };

    class UIManager {
    public:
        void RegisterPanel(std::shared_ptr<UIPanel> panel);
        void RenderPanels();

    private:
        std::vector<std::shared_ptr<UIPanel>> m_Panels;
    };

}
