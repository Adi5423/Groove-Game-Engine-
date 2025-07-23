// engine/src/Events/ApplicationEvent.hpp
#pragma once

#include "Event.hpp"

namespace Groove {

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(int width, int height)
            : m_Width(width), m_Height(height) {
        }
        int GetWidth()  const { return m_Width; }
        int GetHeight() const { return m_Height; }

        std::string ToString() const override {
            return "WindowResizeEvent: "
                + std::to_string(m_Width) + "x"
                + std::to_string(m_Height);
        }

        EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        int m_Width, m_Height;
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;
        EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

}
