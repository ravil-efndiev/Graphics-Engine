#pragma once

#include <API/ECS/Scene.hpp>
#include <API/Objects/UserOrthographicCamera.hpp>
#include <Core/Core.hpp>

namespace Rvl
{
    class PerspectiveCamera;
    class OrthographicCamera;
    class GLFrameBuffer;

    enum RenderMode 
    {
        RenderMode_3D = BIT(0),
        RenderMode_2D = BIT(1),
        RenderMode_Any = BIT(0) | BIT(1)
    };

    class State
    {
    friend class App;

    public:
        State(RenderMode mode);
        virtual ~State();

        virtual void Start() {}
        virtual void Update() {}
        virtual void Tick() {}
        virtual void Render() {}
        virtual void PostRender() {}

        void StartScene();
        void UpdateScene();

    protected:
        Ref<UserCamera> _camera;
        Ref<GLFrameBuffer> _fbo;

        Scene _currentScene;

        void CreateFrameBuffer();
        void CreateFrameBuffer(const glm::vec2& size);

    private:
        RenderMode _mode;

        void Begin(); // can be accessed by RvlApp parent but not RvlApp children
        void End();  // can be accessed by RvlApp parent but not RvlApp children

    };
}

