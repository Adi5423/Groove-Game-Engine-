#pragma once

#include <string>
#include <functional>

// Forward declarations for all event types used in Window.cpp
namespace Groove {
    class KeyPressedEvent;
    class KeyReleasedEvent;
    class MouseButtonPressedEvent;
    class MouseButtonReleasedEvent;
    class MouseMovedEvent;
    class WindowResizeEvent;
    class WindowCloseEvent;
}

namespace Groove {

    // -------- Event Type Enum --------
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // -------- Event Category Bitmask --------
    enum EventCategory {
        None = 0,
        EventCategoryApplication   = 1 << 0,
        EventCategoryInput         = 1 << 1,
        EventCategoryKeyboard      = 1 << 2,
        EventCategoryMouse         = 1 << 3,
        EventCategoryMouseButton   = 1 << 4
    };

    // -------- Base Event Class --------
    class Event {
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & category;
        }

        bool Handled = false; // For dispatching control
    };

    // -------- Macros for Boilerplate --------
    // Macro to define static type and override virtual methods for event type
    #define EVENT_CLASS_TYPE(type) \
        static EventType GetStaticType() { return EventType::type; } \
        virtual EventType GetEventType() const override { return GetStaticType(); } \
        virtual const char* GetName() const override { return #type; }

    // Macro to define category flags for an event
    #define EVENT_CLASS_CATEGORY(categoryFlags) \
        virtual int GetCategoryFlags() const override { return categoryFlags; }

} // namespace Groove
