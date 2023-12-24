#pragma once

#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <yaml-cpp/yaml.h>

namespace Rvl
{
    typedef signed long  int64;
    typedef signed int   int32;
    typedef signed short int16;
    typedef signed char  int8;

    typedef unsigned long  uint64;
    typedef unsigned int   uint32;
    typedef unsigned short uint16;
    typedef unsigned char  uint8;

    typedef uint8   byte;

    typedef float  float32;
    typedef double float64;
    
    extern ImVec2 GlmToImVec2(const glm::vec2& vec);
    extern glm::vec2 ImToGlmVec2(const ImVec2& vec);

    YAML::Emitter& operator<< (YAML::Emitter&, const glm::vec3&);
    YAML::Emitter& operator<< (YAML::Emitter&, const glm::vec4&);
    YAML::Emitter& operator<< (YAML::Emitter&, const glm::vec2&);
    YAML::Emitter& operator<< (YAML::Emitter&, const glm::ivec2&);
}

