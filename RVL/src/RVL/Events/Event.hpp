#ifndef RVL_EVENT_HPP
#define RVL_EVENT_HPP

#include <RVL/Rvlpch.hpp>

#define RVL_EVENT_TYPE_METHODS(type)  static EventType GetTypeStatic() { return EventType::type; } \
                                      EventType GetType() const override { return GetTypeStatic(); }

namespace rvl
{
    enum class EventType : short
    {
        UNDEFINED = -1,
        KEY_PRESSED, KEY_RELEASED,
        WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS,
        CURSOR_MOVED, 
        MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED,
    };

    enum class EventCategory : short
    {
        KEY_EVENTS,
        WINDOW_EVENTS,
        CURSOR_EVENTS,
        MOUSE_EVENTS
    };

    class Event
    {
    public:
        virtual EventCategory GetCategory() const = 0;

        virtual EventType GetType() const = 0;
    private:

    };
}

#endif
