#include "Types.hpp"

namespace Rvl
{
    ImVec2 GlmToImVec2(const glm::vec2& vec)
    {
        return ImVec2(vec.x, vec.y);
    }

    glm::vec2 ImToGlmVec2(const ImVec2& vec)
    {
        return glm::vec2(vec.x, vec.y);
    }

    YAML::Emitter& operator<< (YAML::Emitter& emitter, const glm::vec3& vec)
    {
        emitter << YAML::Flow;
        emitter << YAML::BeginSeq << vec.x << vec.y << vec.z << YAML::EndSeq;
        return emitter;
    }

    YAML::Emitter& operator<< (YAML::Emitter& emitter, const glm::vec4& vec)
    {
        emitter << YAML::Flow;
        emitter << YAML::BeginSeq << vec.x << vec.y << vec.z << vec.w << YAML::EndSeq;
        return emitter;
    }

    YAML::Emitter& operator<< (YAML::Emitter& emitter, const glm::vec2& vec)
    {
        emitter << YAML::Flow;
        emitter << YAML::BeginSeq << vec.x << vec.y << YAML::EndSeq;
        return emitter;
    }

    YAML::Emitter& operator<< (YAML::Emitter& emitter, const glm::ivec2& vec)
    {
        emitter << YAML::Flow;
        emitter << YAML::BeginSeq << vec.x << vec.y << YAML::EndSeq;
        return emitter;
    }
}