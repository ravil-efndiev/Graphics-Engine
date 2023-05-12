#ifndef SB_PLAYER_HPP
#define SB_PLAYER_HPP

#include <RVL.hpp>
#include <API/Components/MovementComponent.hpp>

namespace name
{
    using namespace rvl;
    class Player : public Entity, public IRenderable
    {
    public:
        Player();
        ~Player();

        void Update();
        void Draw() override;

        Ref<Rectangle> GetRect();

    private:
        Ref<Rectangle> _rect;
        Ref<Rectangle> _rect2;
        Ref<MovementComponent> _movementComponent;
    };
}

#endif
