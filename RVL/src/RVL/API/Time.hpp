#ifndef RVL_TIME_HPP
#define RVL_TIME_HPP

namespace rvl
{
    class Time
    {
    public:
        static void Update();

        static float Now();
        static float DeltaTime();
        static float LastTime();

    private:
        static float _lastTime;
        static float _deltaTime;
        static float _time;
    };
}

#endif
