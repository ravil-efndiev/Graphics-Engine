#include "MouseEvents.hpp"

namespace rvl
{
    EventType MouseEvent::GetType() const
    {
    }
    
    EventCategory MouseEvent::GetCategory() const
    {
        return EventCategory::MOUSE_EVENTS;
    }
    
    keycode_t MouseEvent::GetButton() const
    {
        return _button;
    }
    
    MouseEvent::MouseEvent(keycode_t button)
    {
        _button = button;
    }
    
    MouseButtonPressEvent::MouseButtonPressEvent(keycode_t button) : MouseEvent(button) {}
    
    MouseButtonReleaseEvent::MouseButtonReleaseEvent(keycode_t button) : MouseEvent(button) {}
}
