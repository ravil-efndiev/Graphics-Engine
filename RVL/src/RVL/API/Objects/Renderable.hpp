#ifndef RVL_RENDERABLE_HPP
#define RVL_RENDERABLE_HPP

#include <glm/glm.hpp>

namespace Rvl
{
    class Renderable
    {
    public:
        virtual ~Renderable() {}

        virtual void Draw() = 0;
        virtual void Draw(const glm::vec4&) {}

    };
}

#endif
