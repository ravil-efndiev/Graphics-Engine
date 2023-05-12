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
        virtual void Tick();

        void SetClearColor(const glm::vec3& color);

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
    extern Ptr<RvlApp> OnInit() RVL_ENTRY_FUNCTION;

    /*
     * Entry function that can be defined in RVL Application
     * To apply defenition in your app define RVL_END_IMPL macro before including header file
     * If RVL_END_IMPL is defined the function will be called when the program ends
    */
    extern void OnEnd() RVL_ENTRY_FUNCTION;
}

#endif
