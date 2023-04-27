#ifndef RVL_RVLAPP_HPP
#define RVL_RVLAPP_HPP

#include <Rvlpch.hpp>
#include "Core.hpp"
#include "RvlScene.hpp"

namespace rvl
{
    class Window;

    class RvlApp
    {
    public:
        RvlApp(int windowWidth, int windowHeight, const std::string& windowName);
        virtual ~RvlApp();

        status_t Run();

    protected:
        Ref<RvlScene> _currentScene;

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;

        void SetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

    private:
        Scope<Window> _window;

        std::array<GLclampf, 4> _clearColor;

        void CreateWindow(int windowWidth, int windowHeight, const std::string& windowName);

    };

    /*
     * Entry function that must be defined in any RVL Application
     * Mainly it should set rvl::CurrentApp to new instance of RvlApp inherited class 
     * (app you are currently using)
     * it can contain any functionallity but in any case it must initialize CurrentApp
    */
    extern Scope<RvlApp> OnInit() RVL_ENTRY_FUNCTION;

    /*
     * Entry function that can be defined in RVL Application
     * To apply defenition in your app define RVL_END_IMPL macro before including header file
     * If RVL_END_IMPL is defined the function will be called when the program ends
    */
    extern void OnEnd() RVL_ENTRY_FUNCTION;
}

#endif
