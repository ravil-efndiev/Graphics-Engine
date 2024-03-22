#include "Random.hpp"

namespace Rvl
{
    std::mt19937 Random::_generator;

    void Random::Init()
    {
        std::random_device rd;
        _generator = std::mt19937(rd());
    }

    i32 Random::NextInt()
    {
        std::uniform_int_distribution<> distr;
        return distr(_generator);
    }

    i32 Random::NextInt(i32 max)
    {
        return IntRange(0, max);
    }

    u32 Random::NextUint()
    {
        return IntRange(0, std::numeric_limits<u32>::max());
    }

    u32 Random::NextUint(u32 max)
    {
        return IntRange(0, max);
    }

    f64 Random::NextDouble()
    {
        return DoubleRange(std::numeric_limits<f64>::min(), std::numeric_limits<f64>::max());
    }

    f64 Random::NextDouble(f64 max)
    {
        return DoubleRange(0, max);
    }

    f32 Random::NextFloat()
    {
        return FloatRange(std::numeric_limits<f32>::min(), std::numeric_limits<f32>::max());
    }

    f32 Random::NextFloat(f32 max)
    {
        return FloatRange(0, max);
    }

    i32 Random::IntRange(i32 min, i32 max)
    {
        std::uniform_int_distribution<> distr (min, max);
        return distr(_generator);
    }

    u32 Random::UintRange(u32 min, u32 max)
    {
        std::uniform_int_distribution<> distr (min, max);
        return static_cast<u32>(distr(_generator));
    }

    f64 Random::DoubleRange(f64 min, f64 max)
    {
        std::uniform_real_distribution<> distr (min, max);
        return distr(_generator);
    }

    f32 Random::FloatRange(f32 min, f32 max)
    {
        std::uniform_real_distribution<> distr (min, max);
        return static_cast<f32>(distr(_generator));
    }

    bool Random::PercentChance(f64 chance)
    {
        return DoubleRange(0.f, 1.f) <= chance;
    }
}
