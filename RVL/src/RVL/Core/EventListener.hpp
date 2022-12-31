#ifndef RVL_EVENTLISTENER_HPP
#define RVL_EVENTLISTENER_HPP

#include "Events/Events.hpp"

#define MOUSE_BUTTONS_OFFSET 1024

namespace rvl
{
    class EventListener
    {
    public:
        static void Init();

        static void Listen(const Event *event);

        static bool GetKey(keycode_t keycode);
        static bool GetKeyWithFrame(keycode_t keycode);

        static void PollEvents();

    private:
        static std::array<bool, 1032> _keysPressed;
        static std::array<int, 1032> _changeFrames;

        static int _currentFrame;

        static void ListenWindowEvents(const Event *event);
        static void ListenKeyEvents(const Event *event);

    };
}


#endif
