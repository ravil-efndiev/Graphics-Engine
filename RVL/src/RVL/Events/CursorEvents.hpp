#ifndef RVL_CURSOREVENT_HPP
#define RVL_CURSOREVENT_HPP

#include "Event.hpp"
#include <Core/Core.hpp>

namespace rvl
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

#endif
