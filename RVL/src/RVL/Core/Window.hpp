#ifndef RVL_WINDOW_HPP
#define RVL_WINDOW_HPP

#include "Events/Events.hpp"

struct GLFWwindow;

namespace rvl
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& name);
        ~Window();

        bool Closes();

        void Clear(GLclampf red = 0.f, GLclampf green = 0.f, GLclampf blue = 0.f, GLclampf alpha = 1.f);
        void SwapBuffers();
        void PollEvents();

        void SetEventsCallback(void (*eventCallback)(Event*));

    private:
        struct EventCallbackStruct 
        {
            void (*EventCallback)(Event*);
        };

        EventCallbackStruct _eventCallback;

        int _width, _height;
        std::string _name;

        GLFWwindow* _window;
        
        void InitGlfw();
        void CreateWindow();
        void SetCallbacks();

    };
}

#endif
