#ifndef RVL_RVLAPP_HPP
#define RVL_RVLAPP_HPP

#include "Window.hpp"

namespace rvl
{
    class RvlApp
    {
    public:
        RvlApp(int windowWidth, int windowHeight, const std::string& windowName);
        virtual ~RvlApp();

        void Run();

    protected:
        virtual void Start() = 0;
        virtual void Update() = 0;

    private:
        Window* _window;

        void CreateWindow(int windowWidth, int windowHeight, const std::string& windowName);

    };

    extern RvlApp* CreateApp();
}

#endif
