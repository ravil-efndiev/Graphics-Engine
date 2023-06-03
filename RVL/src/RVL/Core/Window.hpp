#ifndef RVL_WINDOW_HPP
#define RVL_WINDOW_HPP

#include "Events/Events.hpp"

struct GLFWwindow;

namespace Rvl
{
    class GLContext;

    class Window
    {
    public:
        Window(int width, int height, const std::string& name);
        ~Window();

        bool Closes() const;
        void SetClose(bool value);

        void SwapBuffers();
        void PollEvents();

        void SetEventsCallback(void (*eventCallback)(Event*));

        int GetWidth() const;
        int GetHeight() const;

        GLFWwindow* GetWindowPtr();

    private:
        struct EventCallbackStruct 
        {
            void (*EventCallback)(Event*);
        };

        EventCallbackStruct _eventCallback;

        int _width, _height;
        std::string _name;

        GLFWwindow* _window;

        Ptr<GLContext> _context;
        
        void InitGlfw();
        void CreateWindow();
        void SetCallbacks();

    };
}

#endif
