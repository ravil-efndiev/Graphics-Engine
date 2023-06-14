#pragma once

#include "Event.hpp"
#include <Core/Core.hpp>

namespace Rvl
{
    class CursorPosEvent : public Event
    {
    public:
        CursorPosEvent(double x, double y);

        EventCategory GetCategory() const override;

        RVL_EVENT_TYPE_METHODS(CURSOR_MOVED)

        double GetX() const;
        double GetY() const;

    private:
        double _x, _y;
    };
}

