#ifndef RVL_MATH_HPP
#define RVL_MATH_HPP

#include <glm/glm.hpp>

namespace rvl
{
    class Math
    {
    public:
        static float Lerp(float current, float target, float t);
        static float Lerp(float current, float target, float t, float deadZone);
        static glm::vec3 Lerp(const glm::vec3& current, const glm::vec3& target, float t);
    };
}

#endif
