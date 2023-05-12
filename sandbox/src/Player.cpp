#include "Player.hpp"

namespace name
{
    Player::Player()
    {
        _rect = Rectangle::Create({0.f, 0.f, 0.f}, {3.f, 3.f}, {0.8f, 0.4f, 0.4f});
        _rect2 = Rectangle::Create({{5.f, 0.f, 0.f}, 45.f, {2.f, 2.f}}, {0.4f, 0.7f, 0.7f});
        _movementComponent = MovementComponent::Create(&_transform, 15.f, 70.f, 25.f);

        AddComponent(_movementComponent);
        AddChild(_rect);
        _rect->AddChild(_rect2);
    }

    Player::~Player() {}

    void Player::Update()
    {
        UpdateChildren();

        _rect2->transform->Rotation += 5.f;
        _movementComponent->Update();
        _movementComponent->Move(Input::GetAxis(Axis::Horizontal), Input::GetAxis(Axis::Vertical));
    }

    void Player::Draw()
    {   
        _rect->Draw();
        _rect2->Draw();
    }

    Ref<Rectangle> Player::GetRect()
    {
        return _rect;
    }
}
