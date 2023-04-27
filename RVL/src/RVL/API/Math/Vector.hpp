#ifndef RVL_VECTOR_HPP
#define RVL_VECTOR_HPP

#include <API/Property.hpp>

namespace rvl
{
    template<class T, int Cmp>
    class Vector
    {
    public:
        Vector() : _x(0), _y(0), _z(0), _w(0) {}
        ~Vector() {}

    private:
        T _x, _y, _z, _w;
    };

    template<class T>
    class Vector<T, 2>
    {
    private:
        T _x, _y;

        std::function<void()> _onChangeCallback = nullptr;

    public:
        Property<T> X =
        {
            &_x,
            [this]() -> const T&
            {
                return _x;
            },
            [this](const T& value) -> void
            {
                _x = value;
                if (_onChangeCallback != nullptr)
                    _onChangeCallback();
            }
        };

        Property<T> Y =
        {
            &_y,
            [this]() -> const T&
            {
                return _y;
            },
            [this](const T& value) -> void
            {
                _y = value;
                if (_onChangeCallback != nullptr)
                    _onChangeCallback();
            }
        };

        Vector() : _x(0), _y(0) {}
        Vector(T x, T y) : _x(x), _y(y) {}
        ~Vector() {}

        void SetOnChangeCallback(const std::function<void()>& callback)
        {
            _onChangeCallback = callback;
        }

        float Magnitude() const
        {
            return sqrt((_x * _x) + (_y * _y));
        }

        void operator=(const Vector& vec)
        {
            _x = vec._x;
            _y = vec._y;
        }
        void operator+=(const Vector& vec)
        {
            _x += vec._x; 
            _y += vec._y; 
        }
        Vector operator+(const Vector& vec)
        {
            return Vector(_x + vec._x, _y + vec._y);
        }

        static Vector<T, 2> Zero()
        {
            return Vector<T, 2>(0, 0);
        }
    };

     template<class T>
    class Vector<T, 3>
    {
    public:
        Vector() : _x(0), _y(0), _z(0) {}
        Vector(T x, T y, T z) : _x(x), _y(y), _z(z) {}
        Vector(const Vector<T, 2>& vec2, T z)
        {
            _x = vec2._x;
            _y = vec2._y;
            _z = z;
        }
        ~Vector() {}

        T X() const { return _x; }
        T Y() const { return _y; }
        T Z() const { return _z; }

        float Magnitude() const
        {
            return sqrt((_x * _x) + (_y * _y) + (_z * _z));
        }

        void SetX(T x) { _x = x; }
        void SetY(T y) { _y = y; }
        void SetZ(T z) { _z = z; }

        void operator=(const Vector& vec)
        {
            _x = vec._x;
            _y = vec._y;
            _z = vec._z;
        }
        void operator+=(const Vector& vec)
        {
            _x += vec._x; 
            _y += vec._y; 
            _z += vec._z; 
        }
        Vector operator+(const Vector& vec)
        {
            return Vector(_x + vec._x, _y + vec._y, _z + vec._z);
        }

        static Vector<T, 3> Zero()
        {
            return Vector<T, 3>(0, 0, 0);   
        }

    private:
        T _x, _y, _z;
    };
}

#endif
