#pragma once
#include "UserCamera.hpp"
#include <API/ECS/Scene.hpp>

namespace Rvl
{

    class SceneRenderer
    {
    public:
        static void Render(const Ref<Scene>& scene, const Ref<UserCamera>& camera);

        static void DrawSprite(Entity entity);
        static void DrawTileMap(Entity entity);
        static void DrawModel(Entity entity, const glm::vec3& cameraPos);
        static void DrawParticles(Entity entity);
    };
}

