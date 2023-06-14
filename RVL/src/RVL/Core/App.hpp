#pragma once

#include <Rvlpch.hpp>
#include "Core.hpp"
#include "State.hpp"

namespace Rvl
{
    class Window;

    class App
    {
    public:
        App(int windowWidth, int windowHeight, const std::string& windowName);
        virtual ~App();

        status_t Run();

    protected:
        Ptr<State> _currentState;

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Tick();
        virtual void Render();

        void SetClearColor(const glm::vec3& color);
        void Close();

    private:
        Ptr<Window> _window;

        void CreateWindow(int windowWidth, int windowHeight, const std::string& windowName);
    };

    /*
     * Entry function that must be defined in any RVL Application
     * Mainly it should set rvl::CurrentApp to new instance of RvlApp inherited class 
     * (app you are currently using)
     * it can contain any functionallity but in any case it must initialize CurrentApp
    */
    extern Ptr<App> OnInit() RVL_ENTRY_FUNCTION;

    /*
     * Entry function that can be defined in RVL Application
     * To apply defenition in your app define RVL_END_IMPL macro before including header file
     * If RVL_END_IMPL is defined the function will be called when the program ends
    */
    extern void OnEnd() RVL_ENTRY_FUNCTION;
}

#define RVL_IMPL_INIT(AppType) Rvl::Ptr<Rvl::App> Rvl::OnInit() { return Rvl::NewPtr<AppType>(); }

