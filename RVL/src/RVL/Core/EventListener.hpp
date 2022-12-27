#ifndef RVL_EVENTLISTENER_HPP
#define RVL_EVENTLISTENER_HPP

#include "Events/Events.hpp"

namespace rvl
{
    
    class EventListener
    {
    public:
        static void Init();

        static void Listen(const Event *event);

        static bool GetKey(rvlKeycode_t keycode);
        
    private:
        static std::array<bool, 1032> _keysPressed;
        static std::array<int, 1032> _changeFrames;

        static void ListenWindowEvents(const Event *event);
        static void ListenKeyEvents(const Event *event);

    };

}


#endif
