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
        float RotationRate = 0.1f;
        float LifeTime = 1.f;
    };

    class ParticleEmitter
    {
    public:
        struct Particle
        {
            glm::vec3 Position;
            glm::vec3 Velocity;
            glm::vec4 ColorStart, ColorEnd;
            float Rotation = 0.f;
            float RotationRate;
            float SizeStart, SizeEnd;

            float LifeTime = 1.f;
            float LifeRemaining = 0.f;

            bool Active = false;
        };

        ParticleEmitter() = default;
        ParticleEmitter(uint32 count);

        void Emit(int32 times);
        void SetCount(uint32 count);

        std::vector<Particle> Particles;
        ParticleProperties Properties;        

    private:
        uint32 _index = 999;
    };
}

