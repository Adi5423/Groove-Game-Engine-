#pragma once
#include <string>

namespace Groove {
    class UIPanel {
    public:
        UIPanel(const std::string& name) : m_Name(name) {}
        virtual ~UIPanel() = default;

        // Called every frame for rendering the panel's ImGui contents
        virtual void OnImGuiRender() = 0;

        // Getter for the panel name
        const std::string& GetName() const { return m_Name; }

    protected:
        std::string m_Name;
    };
}
