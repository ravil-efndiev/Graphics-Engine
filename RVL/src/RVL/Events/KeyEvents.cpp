#include "KeyEvents.hpp"

namespace rvl
{
    KeyEvent::KeyEvent(rvlKeycode_t keycode)
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

    rvlKeycode_t KeyEvent::GetKeyCode() const
    {
        return _keycode;
    }
    
    
    KeyPressEvent::KeyPressEvent(rvlKeycode_t keycode) : KeyEvent(keycode)
    {
    }


    KeyReleaseEvent::KeyReleaseEvent(rvlKeycode_t keycode) : KeyEvent(keycode)
    {
    }

}
