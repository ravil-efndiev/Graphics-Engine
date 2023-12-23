#pragma once
#include "Scene.hpp"
#include <yaml-cpp/yaml.h>
#include "Entity.hpp"

namespace Rvl
{
    class SceneSerializer
    {
    public:
        SceneSerializer(const Ref<Scene>& scene);

        void Serialize(const std::string& path);
        void Deserialize(const std::string& path);

    private:
        Ref<Scene> _scene;
    
    private:
        void SerializeEntity(YAML::Emitter& emitter, Entity entity);
    };
}

