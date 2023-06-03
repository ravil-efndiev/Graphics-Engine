#ifndef SB_PLAYER_HPP
#define SB_PLAYER_HPP

#include <RVL.hpp>
#include <API/Components/MovementComponent.hpp>
#include <API/Components/AnimationComponent.hpp>

namespace sb
{
    using namespace Rvl;
    class Player : public Entity, public Renderable
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
        Ref<Sprite> _sprite;
        Ref<MovementComponent> _movementComponent;
        Ref<AnimationComponent> _spriteAnimationComponent;
    };
}

#endif
