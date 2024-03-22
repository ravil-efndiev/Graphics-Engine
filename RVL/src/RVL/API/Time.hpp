#pragma once
#include "Core/Core.hpp"

namespace Rvl
{
    struct TimeStep
    {
        public:
            TimeStep(f32 time = 0.f) : _time(time) {}

            operator f32 () const { return _time; }
            TimeStep operator+=(TimeStep ts) { _time += ts; return *this; }

            f32 AsMiliseconds() const { return _time * 1000.f; }

        private:
            f32 _time;
    };

    class Time
    {
    public:
        static void Update();

        static TimeStep Current();
        static TimeStep DeltaTime();
        static TimeStep LastTime();
        static TimeStep FixedDeltaTime();

    private:
        static TimeStep _lastTime;
        static TimeStep _deltaTime;
        static TimeStep _time;
    };
}

