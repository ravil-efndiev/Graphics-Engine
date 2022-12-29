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

    /*
     * Entry function that must be defined in any RVL Application
     * Mainly it should set rvl::CurrentApp to new instance of RvlApp inherited class 
     * (app you are currently using)
     * it can contain any functionallity but in any case it must initialize CurrentApp
    */
    extern void OnInit() RVL_ENTRY_FUNCTION;

    /*
     * Entry function that can be defined in RVL Application
     * To apply defenition in your app define RVL_END_IMPL macro before including header file
     * If RVL_END_IMPL is defined the function will be called when the program ends
    */
    extern void OnEnd() RVL_ENTRY_FUNCTION;
}

#endif
