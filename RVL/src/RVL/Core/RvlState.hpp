#ifndef RVL_RVLSCENE_HPP
#define RVL_RVLSCENE_HPP

#include <API/Objects/Rectangle.hpp>
#include <API/Objects/Sprite.hpp>
#include <API/Objects/UserOrthographicCamera.hpp>
#include <Rvlpch.hpp>

namespace rvl
{
    class PerspectiveCamera;
    class OrthographicCamera;
    class GLFrameBuffer;

    typedef UserOrthographicCamera Camera;

    class RvlState
    {
    friend class RvlApp;

    public:
        RvlState();
        virtual ~RvlState();

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Tick();

    protected:
        void AddFrameBuffer(const Ref<GLFrameBuffer>& fbo);

        Ref<UserOrthographicCamera> _camera;
        Ref<GLFrameBuffer> _fbo;

    private:
        void Begin(); // can be accessed by RvlApp parent but not RvlApp children
        void End();  // can be accessed by RvlApp parent but not RvlApp children

    };
}

#endif
