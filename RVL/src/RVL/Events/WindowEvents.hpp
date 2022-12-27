#ifndef RVL_WINDOWEVENTS_HPP
#define RVL_WINDOWEVENTS_HPP

#include "Event.hpp"

namespace rvl
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height);

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        static EventType GetTypeStatic();

        EventCategory GetCategory() const override;
        EventType GetType() const override;

    private:
        uint32_t _width, _height;
    
    };
} 


#endif
