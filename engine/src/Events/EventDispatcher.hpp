#pragma once

#include "Event.hpp"

namespace Groove {

    class EventDispatcher {
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {
        }

        // T must be a subclass of Event
        template<typename T, typename F>
        bool Dispatch(const F& func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

} // namespace Groove
