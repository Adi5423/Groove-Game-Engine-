// engine/src/Events/KeyEvent.hpp
#pragma once

#include "Event.hpp"

namespace Groove {

    // KeyPressedEvent
    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : m_KeyCode(keycode), m_RepeatCount(repeatCount) {
        }

        int GetKeyCode() const { return m_KeyCode; }
        int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override {
            return "KeyPressedEvent: " + std::to_string(m_KeyCode)
                + " (repeats: " + std::to_string(m_RepeatCount) + ")";
        }

        EVENT_CLASS_TYPE(KeyPressed)
            EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    private:
        int m_KeyCode, m_RepeatCount;
    };

    // KeyReleasedEvent
    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(int keycode)
            : m_KeyCode(keycode) {
        }

        int GetKeyCode() const { return m_KeyCode; }

        std::string ToString() const override {
            return "KeyReleasedEvent: " + std::to_string(m_KeyCode);
        }

        EVENT_CLASS_TYPE(KeyReleased)
            EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    private:
        int m_KeyCode;
    };

}
