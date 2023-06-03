#ifndef RVL_PROPERTY_HPP
#define RVL_PROPERTY_HPP

#include <Core/Core.hpp>

namespace Rvl
{
    template <class T>
    class Property
    {
    public:
        Property();
        Property(T* valuePtr);
        Property(
            T* valuePtr,
            const std::function<T()>& get,
            const std::function<void(const T&)>& set
        );
        ~Property();

        T operator()() const;
        operator const T& () const;
        
        Property<T>& operator= (const T& value);

        Property<T>& operator+= (const T& value);
        Property<T>& operator-= (const T& value);
        Property<T>& operator*= (const T& value);
        Property<T>& operator/= (const T& value);

        bool operator> (const T& value);
        bool operator< (const T& value);
        bool operator==(const T& value);
        bool operator>=(const T& value);
        bool operator<=(const T& value);

        T* operator-> ();
        T* GetValuePtr();

    private:
        std::function<T()> _get;
        std::function<void(const T&)> _set;
        T* _valuePtr;
    };

}

//// implementation
namespace Rvl
{
    template <class T>
    Property<T>::Property()
    {   
        _valuePtr = nullptr;
        _get = nullptr;
        _set = nullptr;
    }

    template <class T>
    Property<T>::Property(T* valuePtr)
    {
        _valuePtr = valuePtr;
        _get = [this]() -> const T&
        {
            return *_valuePtr;
        };
        _set = [this](const T& value) -> void
        {
            *_valuePtr = value;
        };
    }

    template <class T>
    inline Property<T>::Property(T* valuePtr, const std::function<T()>& get, const std::function<void(const T &)>& set)
    {
        _valuePtr = valuePtr;
        _get = get;
        _set = set;
    }

    template <class T> Property<T>::~Property(){}

    template <class T>
    T Property<T>::operator()() const
    {
        return _get();
    }

    template<class T>
    inline Property<T>::operator const T& () const
    {
        return _get();
    }

    template <class T>
    Property<T>& Property<T>::operator=(const T &value)
    {
        _set(value);
        return *this; 
    }

    template <class T>
    Property<T> &Property<T>::operator+=(const T &value)
    {
        _set(*_valuePtr + value);
        return *this; 
    }

    template <class T>
    Property<T> &Property<T>::operator-=(const T &value)
    {
        _set(*_valuePtr - value);
        return *this; 
    }

    template <class T>
    Property<T> &Property<T>::operator*=(const T &value)
    {
        _set(*_valuePtr * value);
        return *this; 
    }

        template <class T>
    Property<T> &Property<T>::operator/=(const T &value)
    {
        _set(*_valuePtr / value);
        return *this; 
    }

    template <class T>
    T* Property<T>::operator->()
    {
        return _valuePtr;
    }

    template<class T>
    inline T* Property<T>::GetValuePtr()
    {
        return _valuePtr;
    }

    template <class T>
    inline bool Property<T>::operator>(const T &value)
    {
        return _get() > value;
    }

    template <class T>
    inline bool Property<T>::operator<(const T &value)
    {
        return _get() < value;
    }

    template <class T>
    inline bool Property<T>::operator==(const T &value)
    {
        return _get() == value;
    }

    template <class T>
    inline bool Property<T>::operator>=(const T &value)
    {
        return _get() >= value;
    }

    template <class T>
    inline bool Property<T>::operator<=(const T &value)
    {
        return _get() <= value;
    }
}

#endif
