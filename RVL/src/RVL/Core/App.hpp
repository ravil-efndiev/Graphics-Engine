#pragma once

#include <Rvlpch.hpp>
#include "Core.hpp"
#include "State.hpp"
#include "Utils/Types.hpp"

namespace Rvl
{
    class Window;

    class App
    {
    public:
        template <class T, class... Args>
        static App* New(Args&& ...args)
        {
            RVL_ASSERT(!_instance, "instance of App already exists");

            _instance = NewPtr<T>(std::forward<Args>(args)...);
            RVL_ASSERT((Utils::InstanceOf<App>(_instance.get())), "specified type is not derieved from App");

            return _instance.get();
        }

        static App* Get() { return _instance.get(); }

    public:
        App(i32 windowWidth, i32 windowHeight, const std::string& windowName);
        virtual ~App();

        status Run();
        void ProcessEvent(Event* event);

        void SetCursorLocked(bool flag);
        RenderMode GetStateRenderMode() const;

        bool GetWindowClose() const;

    protected:
        Ptr<State> _currentState;

        virtual void Start();
        virtual void Update();
        virtual void Tick();
        virtual void Render();

        void SetClearColor(const glm::vec3& color);
        void Close();

    private:
        void CreateWindow(i32 windowWidth, i32 windowHeight, const std::string& windowName);
        
    private:
        Ptr<Window> _window;
        static Ptr<App> _instance;
    };

}
