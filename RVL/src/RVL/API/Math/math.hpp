#pragma once

#include <glm/glm.hpp>

namespace Rvl
{
    enum class Axis
    {
        None       = 1 << 0,
        Vertical   = 1 << 1,
        Horizontal = 1 << 2,
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
        static float Lerp(float current, float target, float t);
        static float Lerp(float current, float target, float t, float deadZone);
        static glm::vec3 Lerp(const glm::vec3& current, const glm::vec3& target, float t);
    };
}

