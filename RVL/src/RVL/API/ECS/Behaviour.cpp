#include "Behaviour.hpp"

#include "Entity.hpp"

namespace Rvl
{
    Behaviour::Behaviour(Entity& self) : 
        _self(self), 
        _transform(_self.Get<Transform>()) {}

    Behaviour::~Behaviour() {}
}
