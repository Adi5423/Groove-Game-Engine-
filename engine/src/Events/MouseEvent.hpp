// engine/src/Events/MouseEvent.hpp
#pragma once

#include "Event.hpp"

namespace Groove {

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            return "MouseMovedEvent: (" + std::to_string(m_MouseX) + ", "
                + std::to_string(m_MouseY) + ")";
        }

        EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_MouseX, m_MouseY;
    };

    class MouseButtonPressedEvent : public Event {
    public:
        MouseButtonPressedEvent(int button) : m_Button(button) {}
        int GetButton() const { return m_Button; }

        std::string ToString() const override {
            return "MouseButtonPressedEvent: " + std::to_string(m_Button);
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
            EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

    private:
        int m_Button;
    };

    class MouseButtonReleasedEvent : public Event {
    public:
        MouseButtonReleasedEvent(int button) : m_Button(button) {}
        int GetButton() const { return m_Button; }

        std::string ToString() const override {
            return "MouseButtonReleasedEvent: " + std::to_string(m_Button);
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
            EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

    private:
        int m_Button;
    };

}
