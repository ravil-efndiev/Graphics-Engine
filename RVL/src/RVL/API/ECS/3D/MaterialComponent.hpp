#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    class GLShaderProgram;
    class MaterialComponent
    {
    public:
        MaterialComponent() = default;
        MaterialComponent(const Ref<GLShaderProgram>& shader);
        MaterialComponent(const MaterialComponent& other);
        ~MaterialComponent() {}

        Ref<GLShaderProgram> GetShader() const;
        void SetShader(const Ref<GLShaderProgram>& shader);

        void ProcessLightSources(bool flag);
        bool ShouldProcessLightSources() const;

#define GET_VALUE(mapName) \
    auto it = mapName.find(name); \
    if (it != mapName.end()) { return it->second; } \
    return 0; \

        template <class T> 
        inline T Get(const std::string& name) const
        {
            if constexpr (std::is_same<T, float>()) { GET_VALUE(_floats) }
            if constexpr (std::is_same<T, glm::vec2>()) { GET_VALUE(_vec2s) }
            if constexpr (std::is_same<T, glm::vec3>()) { GET_VALUE(_vec3s) }
            if constexpr (std::is_same<T, glm::vec4>()) { GET_VALUE(_vec4s) }
        }

        template <class T> 
        inline void Set(const std::string& name, const T& value)
        {
            if constexpr (std::is_same<T, float>()) { _floats[name] = value; } 
            if constexpr (std::is_same<T, glm::vec2>()) { _vec2s[name] = value; }
            if constexpr (std::is_same<T, glm::vec3>()) { _vec3s[name] = value; }
            if constexpr (std::is_same<T, glm::vec4>()) { _vec4s[name] = value; }
        }

#undef GET_VALUE

        void Update();

    private:
        Ref<GLShaderProgram> _shader;

        std::unordered_map<std::string, float> _floats;
        std::unordered_map<std::string, glm::vec2> _vec2s;
        std::unordered_map<std::string, glm::vec3> _vec3s;
        std::unordered_map<std::string, glm::vec4> _vec4s;

        bool _processLightSources = false;
    };
}

