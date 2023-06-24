#pragma once

#include <API/ECS/Scene.hpp>
#include <API/Objects/UserOrthographicCamera.hpp>
#include <Rvlpch.hpp>

namespace Rvl
{
    class PerspectiveCamera;
    class OrthographicCamera;
    class GLFrameBuffer;

    enum class RenderMode { Mode_3D, Mode_2D };

    class State
    {
    friend class App;

    public:
        State(RenderMode mode);
        virtual ~State();

        virtual void Start() {}
        virtual void Update() {}
        virtual void Render() {}
        virtual void Tick() {}

        void StartScene();
        void UpdateScene();

    protected:
        void AddFrameBuffer(const Ref<GLFrameBuffer>& fbo);

        Ref<UserCamera> _camera;
        Ref<GLFrameBuffer> _fbo;

        Scene _currentScene;

    private:
        RenderMode _mode;

        void Begin(); // can be accessed by RvlApp parent but not RvlApp children
        void End();  // can be accessed by RvlApp parent but not RvlApp children

    };
}

