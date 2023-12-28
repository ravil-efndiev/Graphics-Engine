#include "ParticleEmitter.hpp"
#include "Rendering/Renderer/ShaderLibrary.hpp"
#include "Random.hpp"
#include "Math/Math.hpp"
#include <Rendering/Renderer/Renderer.hpp>

namespace Rvl
{
    ParticleEmitter::ParticleEmitter(uint32 count, const ParticleProperties& props)
    {
        Properties = props;
        SetCount(count);
    }

    void ParticleEmitter::SetCount(uint32 count)
    {
        Particles.resize(count);
    }

    void ParticleEmitter::Emit(int32 times)
    {
        Emit(times, Properties);   
    }

    void ParticleEmitter::Emit(int32 times, const ParticleProperties& props)
    {
        for (int i = 0; i < times; i++)
        {
            if (_index >= Particles.size())
                _index = 0;
                
            Particle& particle = Particles[_index];
            particle.Active = true;
            particle.Position = props.Position;
            particle.Rotation = Random::NextFloat() * 2.f * Math::PI;
            
            particle.Velocity = props.Velocity;
            particle.Velocity.x += props.VelocityVariation.x * Random::FloatRange(-0.5f, 0.5f);
            particle.Velocity.y += props.VelocityVariation.y * Random::FloatRange(-0.5f, 0.5f);
            particle.Velocity.z += props.VelocityVariation.z * Random::FloatRange(-0.5f, 0.5f);
            
            particle.ColorStart = props.ColorStart;
            particle.ColorEnd = props.ColorEnd;
            particle.Texture = props.Texture;
            particle.UseTexture = props.UseTexture;

            particle.LifeTime = props.LifeTime;
            particle.LifeRemaining = props.LifeTime;
            particle.SizeStart = props.SizeStart * props.SizeVariation * Random::FloatRange(-0.5f, 0.5f);
            particle.SizeEnd = props.SizeEnd;

            _index++;
        }
    }
}
