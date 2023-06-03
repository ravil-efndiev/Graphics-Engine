#include "Random.hpp"

namespace Rvl
{
    std::mt19937 Random::_generator;

    void Random::Init()
    {
        std::random_device rd;
        _generator = std::mt19937(rd());
    }

    int Random::NextInt()
    {
        std::uniform_int_distribution<> distr;
        return distr(_generator);
    }

    int Random::NextInt(int max)
    {
        return IntRange(0, max);
    }

    uint32_t Random::NextUint()
    {
        return IntRange(0, std::numeric_limits<uint32_t>::max());
    }

    uint32_t Random::NextUint(uint32_t max)
    {
        return IntRange(0, max);
    }

    double Random::NextDouble()
    {
        return DoubleRange(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
    }

    double Random::NextDouble(double max)
    {
        return DoubleRange(0, max);
    }

    float Random::NextFloat()
    {
        return FloatRange(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    }

    float Random::NextFloat(float max)
    {
        return FloatRange(0, max);
    }

    int Random::IntRange(int min, int max)
    {
        std::uniform_int_distribution<> distr (min, max);
        return distr(_generator);
    }

    uint32_t Random::UintRange(uint32_t min, uint32_t max)
    {
        std::uniform_int_distribution<> distr (min, max);
        return static_cast<uint32_t>(distr(_generator));
    }

    double Random::DoubleRange(double min, double max)
    {
        std::uniform_real_distribution<> distr (min, max);
        return distr(_generator);
    }

    float Random::FloatRange(float min, float max)
    {
        std::uniform_real_distribution<> distr (min, max);
        return static_cast<float>(distr(_generator));
    }
}
