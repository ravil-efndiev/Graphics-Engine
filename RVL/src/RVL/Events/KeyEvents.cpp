#include "KeyEvents.hpp"

namespace rvl
{
    KeyEvent::KeyEvent(keycode_t keycode)
    {
        _keycode = keycode;
    }

    EventType KeyEvent::GetType() const
    {
        return EventType::UNDEFINED;
    }

    EventCategory KeyEvent::GetCategory() const
    {
        return EventCategory::KEY_EVENTS;
    }

    keycode_t KeyEvent::GetKeyCode() const
    {
        return _keycode;
    }
    
    
    KeyPressEvent::KeyPressEvent(keycode_t keycode) : KeyEvent(keycode)
    {
    }


    KeyReleaseEvent::KeyReleaseEvent(keycode_t keycode) : KeyEvent(keycode)
    {
    }

}
