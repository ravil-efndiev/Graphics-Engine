#pragma once

#include "Events/Events.hpp"

struct GLFWwindow;

namespace Rvl
{
    class GLContext;

    class Window
    {
    public:
        Window(i32 width, i32 height, const std::string& name);
        ~Window();

        bool Closes() const;
        void SetClose(bool value);

        void SwapBuffers();
        void PollEvents();

        void SetEventsCallback(void (*eventCallback)(Event*));

        GLFWwindow* GetWindowPtr();

        void SetCursorLocked(bool flag);

    private:
        struct EventCallbackStruct 
        {
            void (*EventCallback)(Event*);
        };

        EventCallbackStruct _eventCallback;

        std::string _name;
        GLFWwindow* _window;
        Ptr<GLContext> _context;

        void InitGlfw();
        void CreateWindow(i32 width, i32 height);
        void SetCallbacks();

    };
}

