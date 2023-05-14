#include "Player.hpp"

namespace name
{
    Player::Player()
    {
        _rect = Rectangle::Create({0.f, 0.f, 0.02f}, {3.f, 3.f}, {0.8f, 0.4f, 0.4f});
        _rect2 = Rectangle::Create({{5.f, 0.f, 0.02f}, 45.f, {2.f, 2.f}}, {0.4f, 0.7f, 0.7f});
        _movementComponent = MovementComponent::Create(&_transform, 15.f, 70.f, 25.f);

        _sprite = Sprite::Create({-5.f, 0.f, 0.02f}, 3.f);
        _sprite->LoadTexture("assets/textures/map.png");

        _spriteAnimationComponent = AnimationComponent::Create(_sprite);
        _spriteAnimationComponent->AddAnimation("TEST", 50.f, 0.f, 3.f, 5.f, 3.f, 128.f, 128.f);

        AddComponent(_movementComponent);

        AddChild(_rect);
        AddChild(_sprite);
        _rect->AddChild(_rect2);
        
        _sprite->AddComponent(_spriteAnimationComponent);
    }

    Player::~Player() {}

    void Player::Update()
    {
        UpdateChildren();

        _spriteAnimationComponent->Play("TEST");

        _rect2->transform->Rotation += 5.f;
        _movementComponent->Update();
        _movementComponent->Move(Input::GetAxis(Axis::Horizontal), Input::GetAxis(Axis::Vertical));
    }

    void Player::Draw()
    {   
        _rect->Draw();
        _rect2->Draw();
        _sprite->Draw();
    }

    Ref<Rectangle> Player::GetRect()
    {
        return _rect;
    }
}
