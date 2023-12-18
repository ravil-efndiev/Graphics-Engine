#pragma once

#include "System.hpp"

namespace Rvl
{
    void Sprite2DSystem(const std::vector<Entity>& entities);

    void Movement2DSystem(const std::vector<Entity>& entities);

    void Animation2DSystem(const std::vector<Entity>& entities);

    void MaterialSystem(const std::vector<Entity>& entities);

    void LightSystem(const std::vector<Entity>& entities);

    void ModelLoaderSystem(const std::vector<Entity>& entities);
}
