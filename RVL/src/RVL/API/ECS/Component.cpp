#include "Component.hpp"

namespace Rvl
{
    Component::Component(Entity* self)
    {
        _self = self;
    }

    Component::~Component() {}
}