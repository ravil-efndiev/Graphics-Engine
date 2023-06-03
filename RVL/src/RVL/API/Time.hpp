#ifndef RVL_TIME_HPP
#define RVL_TIME_HPP

namespace Rvl
{
    struct TimeStep
    {
        public:
            TimeStep(float time = 0.f) : _time(time) {}

            operator float () const { return _time; }
            TimeStep operator+=(TimeStep ts) { _time += ts; return *this; }

            float AsMiliseconds() const { return _time * 1000.f; }

        private:
            float _time;
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

#endif
