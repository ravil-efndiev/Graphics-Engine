#pragma once

#include "Event.hpp"
#include <Core/Core.hpp>

namespace Rvl
{
    class MouseEvent : public Event
    {
    public:
        virtual EventType GetType() const override;
        EventCategory GetCategory() const override;

        keycode_t GetButton() const;

    protected:
        explicit MouseEvent(keycode_t button);

        keycode_t _button;
    };

    class MouseButtonPressEvent : public MouseEvent
    {
    public:
        MouseButtonPressEvent(keycode_t button);

        RVL_EVENT_TYPE_METHODS(MOUSE_BUTTON_PRESSED)

    };

    class MouseButtonReleaseEvent : public MouseEvent
    {
    public:
        MouseButtonReleaseEvent(keycode_t button);

        RVL_EVENT_TYPE_METHODS(MOUSE_BUTTON_RELEASED);
    };
}

