#ifndef RVL_ENTITY_HPP
#define RVL_ENTITY_HPP

#include <API/Math/math.hpp>

namespace rvl
{
    class Entity
    {
    friend class RvlScene;

    public:
        Entity();
        Entity(float x, float y);
        Entity(const Vector2f& position);
        virtual ~Entity();

        Vector2f& Position();

        virtual void Draw() = 0;

    protected:
        Vector2f _position;

    };
}

#endif
