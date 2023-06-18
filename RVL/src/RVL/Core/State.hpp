#pragma once

#include <API/ECS/Scene.hpp>
#include <API/Objects/UserOrthographicCamera.hpp>
#include <Rvlpch.hpp>

namespace Rvl
{
    class PerspectiveCamera;
    class OrthographicCamera;
    class GLFrameBuffer;

    class State
    {
    friend class App;

    public:
        State();
        virtual ~State();

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Tick();

        void StartScene();
        void UpdateScene();

    protected:
        void AddFrameBuffer(const Ref<GLFrameBuffer>& fbo);

        Ref<UserCamera> _camera;
        Ref<GLFrameBuffer> _fbo;

        Scene _currentScene;

    private:
        void Begin(); // can be accessed by RvlApp parent but not RvlApp children
        void End();  // can be accessed by RvlApp parent but not RvlApp children

    };
}

