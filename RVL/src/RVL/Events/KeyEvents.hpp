#ifndef RVL_KEYEVENTS_HPP
#define RVL_KEYEVENTS_HPP

#include "Event.hpp"
#include <Core/Platform.hpp>

namespace rvl
{
    class KeyEvent : public Event
    {
    public:
        virtual EventType GetType() const override;
        EventCategory GetCategory() const override;

        rvlKeycode_t GetKeyCode() const;

    protected:
        KeyEvent(rvlKeycode_t keycode);

        rvlKeycode_t _keycode;
    };


    class KeyPressEvent : public KeyEvent
    {
    public:
        KeyPressEvent(rvlKeycode_t keycode);

        RVL_EVENT_TYPE_METHODS(KEY_PRESSED)

    private:
    };

    class KeyReleaseEvent : public KeyEvent
    {
    public:
        KeyReleaseEvent(rvlKeycode_t keycode);

        RVL_EVENT_TYPE_METHODS(KEY_RELEASED)

    private:
    };
}

#endif
