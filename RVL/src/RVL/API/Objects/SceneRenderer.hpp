#pragma once
#include "UserCamera.hpp"
#include <API/ECS/Scene.hpp>

namespace Rvl
{
    class ParticleEmitter;
    struct EntityData;

    class SceneRenderer
    {
    public:
        static void Render(const Ref<Scene>& scene, const Ref<UserCamera>& camera);

        static void DrawSprite(Entity entity);
        static void DrawTileMap(Entity entity);
        static void DrawModel(Entity entity, const glm::vec3& cameraPos, EntityData& data);

    private:
        static void DrawParticleEmitters(const std::vector<Entity>& entities);
        static void DrawParticles(ParticleEmitter& emitter, const glm::vec3& tfPos);
    };
}

