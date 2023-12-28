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
        static constexpr double PI = 3.14159265358979323846264338;

        static float Lerp(float current, float target, float t);
        static float Lerp(float current, float target, float t, float deadZone);
        static glm::vec3 Lerp(const glm::vec3& current, const glm::vec3& target, float t);
        static glm::vec4 Lerp(const glm::vec4& current, const glm::vec4& target, float t);
    };
}

