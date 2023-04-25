#ifndef RVL_TIME_HPP
#define RVL_TIME_HPP

namespace rvl
{
    struct TimeStep
    {
        public:
            TimeStep(float time = 0.f) : _time(time) {}

            operator float () const { return _time; }
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

    private:
        static TimeStep _lastTime;
        static TimeStep _deltaTime;
        static TimeStep _time;
    };
}

#endif
