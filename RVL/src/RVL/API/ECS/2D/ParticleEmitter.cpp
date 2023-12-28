#include "ParticleEmitter.hpp"
#include "Rendering/Renderer/ShaderLibrary.hpp"
#include "Random.hpp"
#include "Math/Math.hpp"
#include <Rendering/Renderer/Renderer.hpp>

namespace Rvl
{
    ParticleEmitter::ParticleEmitter(uint32 count)
    {
        SetCount(count);
    }

    void ParticleEmitter::SetCount(uint32 count)
    {
        _index = count - 1;
        Particles.resize(count);
    }

    void ParticleEmitter::Emit(int32 times)
    {
        for (int i = 0; i < times; i++)
        {
            Particle& particle = Particles[_index];
            particle.Active = true;
            particle.Position = Properties.Position;
            particle.Rotation = Random::NextFloat() * 2.f * Math::PI;
            particle.RotationRate = Properties.RotationRate;
            
            particle.Velocity = Properties.Velocity;
            particle.Velocity.x += Properties.VelocityVariation.x * Random::FloatRange(-0.5f, 0.5f);
            particle.Velocity.y += Properties.VelocityVariation.y * Random::FloatRange(-0.5f, 0.5f);
            
            particle.ColorStart = Properties.ColorStart;
            particle.ColorEnd = Properties.ColorEnd;

            particle.LifeTime = Properties.LifeTime;
            particle.LifeRemaining = Properties.LifeTime;
            particle.SizeStart = Properties.SizeStart * Properties.SizeVariation * Random::FloatRange(-0.5f, 0.5f);
            particle.SizeEnd = Properties.SizeEnd;

            _index = --_index % Particles.size();
        }
    }

}
