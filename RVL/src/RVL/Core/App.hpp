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
        App(int windowWidth, int windowHeight, const std::string& windowName);
        virtual ~App();

        status_t Run();
        void ProcessEvent(Event* event);

        void SetCursorLocked(bool flag);
        RenderMode GetStateRenderMode() const;

        template <class T, class... Args>
        static Ref<App> New(Args&& ...args)
        {
            RVL_ASSERT((_instance == nullptr), "instance of App already exists");

            auto instance = NewRef<T>(args...);
            RVL_ASSERT((Utils::InstanceOf<App>(instance)), "specified type is not derieved from App");

            _instance = instance;
            return _instance;
        }

        static Ref<App> GetInstance() { return _instance; }

    protected:
        Ptr<State> _currentState;

        virtual void Start();
        virtual void Update();
        virtual void Tick();
        virtual void Render();

        void SetClearColor(const glm::vec3& color);
        void Close();

    private:
        Ptr<Window> _window;

        void CreateWindow(int windowWidth, int windowHeight, const std::string& windowName);

        static Ref<App> _instance;
    };

}
