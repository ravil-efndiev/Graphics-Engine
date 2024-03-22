#pragma once

#include <glm/glm.hpp>
#include <Core/Core.hpp>

namespace Rvl
{
    enum class Axis
    {
        None       = BIT(0),
        Vertical   = BIT(1),
        Horizontal = BIT(2),
    };

    inline Axis operator|(Axis a, Axis b)
    {
        return static_cast<Axis>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline Axis operator&(Axis a, Axis b)
    {
        return static_cast<Axis>(static_cast<int>(a) & static_cast<int>(b));
    }

    class Math
    {
    public:
        static constexpr f64 PI = 3.14159265358979323846264338;

        static f32 Lerp(f32 current, f32 target, f32 t);
        static f32 Lerp(f32 current, f32 target, f32 t, f32 deadZone);
        static glm::vec3 Lerp(const glm::vec3& current, const glm::vec3& target, f32 t);
        static glm::vec4 Lerp(const glm::vec4& current, const glm::vec4& target, f32 t);
    };
}
