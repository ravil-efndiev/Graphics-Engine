#include "CursorEvents.hpp"

namespace Rvl
{
    CursorPosEvent::CursorPosEvent(double x, double y)
    {
        _x = x;
        _y = y;
    }

    EventCategory CursorPosEvent::GetCategory() const
    {
        return EventCategory::CURSOR_EVENTS;
    }

    double CursorPosEvent::GetX() const
    {
        return _x;
    }

    double CursorPosEvent::GetY() const
    {
        return _y;
    }
}
