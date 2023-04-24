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

    class RvlScene
    {
    friend class RvlApp;

    public:
        RvlScene();
        virtual ~RvlScene();

        virtual void Start();
        virtual void Update();
        virtual void Render();

    protected:
        typedef UserOrthographicCamera Camera;

        Ref<UserOrthographicCamera> _camera;

    private:
        void MakeScene(); // can be accessed by RvlApp parent but not RvlApp children
    };
}

#endif
