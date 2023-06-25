#pragma once

#include <glm/glm.hpp>
#include <Core/Core.hpp>

namespace Rvl
{
    class Entity;

    using System = std::function<void(const std::vector<Entity>&)>;
}
