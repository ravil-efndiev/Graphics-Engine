#pragma once

#include <Core/Core.hpp>

#define RVL_PCT(percent) (f64)percent / 100.0

namespace Rvl
{
    class Random
    {
    public:
        static void Init();

        static i32 NextInt();
        static i32 NextInt(i32 max);

        static u32 NextUint();
        static u32 NextUint(u32 max);

        static f64 NextDouble();
        static f64 NextDouble(f64 max);

        static f32 NextFloat();
        static f32 NextFloat(f32 max);

        static i32 IntRange(i32 min, i32 max);
        static u32 UintRange(u32 min, u32 max);
        static f64 DoubleRange(f64 min, f64 max);
        static f32 FloatRange(f32 min, f32 max);

        static bool PercentChance(f64 chance);

    private:
        static std::mt19937 _generator;
    };
}

