#pragma once

#include "Events/Events.hpp"

#define MOUSE_BUTTONS_OFFSET 1024

namespace Rvl
{
    class EventListener
    {
    public:
        static void Init();

        static void Listen(const Event* event);

        static bool GetKey(keycode_t keycode);
        static bool GetKeyWithFrame(keycode_t keycode);

        static double GetCursorPosX();
        static double GetCursorPosY();

        static double GetCursorDeltaX();
        static double GetCursorDeltaY();

        static void PollEvents();

    private:
        static std::array<bool, 1032> _keysPressed;
        static std::array<int, 1032> _changeFrames;
        static double _cursorPosX, _cursorDeltaX;
        static double _cursorPosY, _cursorDeltaY;

        static bool _cursorStarted;
        static int _currentFrame;

        static std::unordered_map<keycode_t, keycode_t> _mouseButtons;

        static void ListenWindowEvents(const Event* event);
        static void ListenKeyEvents(const Event* event);
        static void ListenCursorEvents(const Event* event);
        static void ListenMouseEvents(const Event* event);

    };
}


