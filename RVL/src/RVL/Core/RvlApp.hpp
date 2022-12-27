#ifndef RVL_RVLAPP_HPP
#define RVL_RVLAPP_HPP

#include <Rvlpch.hpp>
#include "Platform.hpp"

namespace rvl
{
    class Window;

    class RvlApp
    {
    public:
        RvlApp(int windowWidth, int windowHeight, const std::string& windowName);
        virtual ~RvlApp();

        rvlStatus_t Run();

    protected:
        virtual void Start() = 0;
        virtual void Update() = 0;

    private:
        Window* _window;

        void CreateWindow(int windowWidth, int windowHeight, const std::string& windowName);

    };

    static RvlApp* CurrentApp;

    extern void OnInit() RVL_ENTRY_FUNCTION;
}

#endif
