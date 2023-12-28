#pragma once
#include <Core/Core.hpp>
#include "Time.hpp"

namespace Rvl
{
    class GLTexture;
    class GLShaderProgram;

    struct ParticleProperties
    {
        glm::vec3 Position {0.f};
        glm::vec3 Velocity {0.f}, VelocityVariation {0.f};
        glm::vec4 ColorStart {1.f}, ColorEnd {0.f};
        float SizeStart = 1.f, SizeEnd = 0.1f, SizeVariation = 0.f;
        float LifeTime = 1.f;
        bool UseTexture = false;
        Ref<GLTexture> Texture;
    };

    class ParticleEmitter
    {
    public:
        struct Particle
        {
            glm::vec3 Position, Velocity;
            glm::vec4 ColorStart, ColorEnd;
            float Rotation = 0.f;
            float SizeStart, SizeEnd;

            float LifeTime = 1.f;
            float LifeRemaining = 0.f;

            bool Active = false, UseTexture = false;
            Ref<GLTexture> Texture;
        };

        ParticleEmitter() = default;
        ParticleEmitter(uint32 count, const ParticleProperties& props = {});

        void Emit(int32 times);
        void Emit(int32 times, const ParticleProperties& props);
        void SetCount(uint32 count);

        std::vector<Particle> Particles;
        ParticleProperties Properties;     
        bool AdditiveBlend = false;   

    private:
        uint32 _index = 0;
    };
}

