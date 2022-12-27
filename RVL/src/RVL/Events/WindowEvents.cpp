#include "WindowEvents.hpp"

namespace rvl
{
    WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height)
    {
        _width = width;
        _height = height;
    }

    uint32_t WindowResizeEvent::GetWidth() const
    {
        return _width;
    }

    uint32_t WindowResizeEvent::GetHeight() const
    {
        return _height;
    }

    EventType WindowResizeEvent::GetTypeStatic()
    {
        return EventType::WINDOW_RESIZE;
    }

    EventType WindowResizeEvent::GetType() const
    {
        return GetTypeStatic();
    }

    EventCategory WindowResizeEvent::GetCategory() const
    {
        return EventCategory::WINDOW_EVENTS;
    }

}
