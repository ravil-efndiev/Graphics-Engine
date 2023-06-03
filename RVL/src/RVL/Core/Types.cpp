#include "Types.hpp"

ImVec2 Rvl::GlmToImVec2(const glm::vec2& vec)
{
    return ImVec2(vec.x, vec.y);
}

glm::vec2 Rvl::ImToGlmVec2(const ImVec2& vec)
{
    return glm::vec2(vec.x, vec.y);
}
