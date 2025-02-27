#pragma once

#include "Event.hpp"
#include <Core/Core.hpp>

namespace Rvl
{
    class KeyEvent : public Event
    {
    public:
        virtual EventType GetType() const override;
        EventCategory GetCategory() const override;

        keycode_t GetKeyCode() const;

    protected:
        explicit KeyEvent(keycode_t keycode);

        keycode_t _keycode;
    };


    class KeyPressEvent : public KeyEvent
    {
    public:
        KeyPressEvent(keycode_t keycode);

        RVL_EVENT_TYPE_METHODS(KEY_PRESSED)
    };

    class KeyReleaseEvent : public KeyEvent
    {
    public:
        KeyReleaseEvent(keycode_t keycode);

        RVL_EVENT_TYPE_METHODS(KEY_RELEASED)
    };
}

