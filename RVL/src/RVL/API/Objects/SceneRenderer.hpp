#pragma once
#include "UserCamera.hpp"
#include <API/ECS/Scene.hpp>

namespace Rvl
{

    class SceneRenderer
    {
    public:
        static void Render(Scene& scene, const Ref<UserCamera>& camera);

    private:

    };
}

