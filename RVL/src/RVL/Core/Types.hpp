#pragma once

#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <yaml-cpp/yaml.h>

namespace Rvl
{
    typedef int64_t i64;
    typedef int32_t i32;
    typedef int16_t i16;
    typedef int8_t  i8;

    typedef uint64_t u64;
    typedef uint32_t u32;
    typedef uint16_t u16;
    typedef uint8_t  u8;

    typedef u8 byte;

    typedef float  f32;
    typedef double f64;
    
    extern ImVec2 GlmToImVec2(const glm::vec2& vec);
    extern glm::vec2 ImToGlmVec2(const ImVec2& vec);

    YAML::Emitter& operator<< (YAML::Emitter&, const glm::vec3&);
    YAML::Emitter& operator<< (YAML::Emitter&, const glm::vec4&);
    YAML::Emitter& operator<< (YAML::Emitter&, const glm::vec2&);
    YAML::Emitter& operator<< (YAML::Emitter&, const glm::ivec2&);
}
