#include "Types.hpp"

ImVec2 rvl::GlmToImVec2(const glm::vec2& vec)
{
    return ImVec2(vec.x, vec.y);
}

glm::vec2 rvl::ImToGlmVec2(const ImVec2& vec)
{
    return glm::vec2(vec.x, vec.y);
}
