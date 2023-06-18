#pragma once
#include <Rendering/Renderer/Camera.hpp>
#include <Core/Core.hpp>

namespace Rvl
{
    class UserOrthographicCamera;
    class UserPerspectiveCamera;

    class UserCamera
    {
    public:
        static Ref<UserOrthographicCamera> ToOrtho(const Ref<UserCamera>& cam);
        static Ref<UserPerspectiveCamera> ToPerspective(const Ref<UserCamera>& cam);

        virtual Ref<Camera> GetCamera() const = 0;

    };
    
}

