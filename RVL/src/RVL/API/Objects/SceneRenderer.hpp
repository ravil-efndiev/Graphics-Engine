#pragma once
#include <API/ECS/Scene.hpp>

namespace Rvl
{

    class SceneRenderer
    {
    public:
        enum class PriorityComponent { Sprite, Model };

        static void Render(Scene& scene, PriorityComponent priority = PriorityComponent::Model);

    private:

    };
}

