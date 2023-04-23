#ifndef RVL_ENTITY_HPP
#define RVL_ENTITY_HPP

#include <API/Math/math.hpp>
#include <API/Property.hpp>

namespace rvl
{
    class Entity
    {
    friend class RvlScene;

    protected:
        Vector2f _position;

        virtual void ResetPosition();

    public:
        Property<Vector2f> Position
        {
            &_position,
            [this]() -> const Vector2f&
            {
                return _position;
            },
            [this](const Vector2f& value)
            {
                _position = value;
                ResetPosition();
            }
        };

        Entity();
        Entity(float x, float y);
        Entity(const Vector2f& position);
        virtual ~Entity();

        virtual void Draw() = 0;

    };
}

#endif
