#include "MainScene.hpp"

namespace name
{
    using namespace rvl;

    MainScene::MainScene() {}
    MainScene::~MainScene() {}

    void MainScene::Start()
    {
        _camera = Camera::Create();
        _rect = Rectangle::Create(0.f, 0.f, 2.f, 3.f, {0.f, 1.f, 1.f});

        _sprite1 = Sprite::Create(-3.f, 0.f);
        _sprite1->LoadTexture("a.jpg");

        _sprite2 = Sprite::Create(3.f, 0.f);
        _sprite2->LoadTexture("container.jpg");

        _sprite3 = Sprite::Create(0.f, -3.f);
        _sprite3->LoadTexture("floor1.png");
    }

    void MainScene::Update()
    {
        if (Input::IsKeyPressed(Keys::RVL_KEY_A))
            _rect->Position->X -= 7.f * Time::DeltaTime();
            
        if (Input::IsKeyPressed(Keys::RVL_KEY_D))
            _rect->Position->X += 7.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_S))
            _rect->Position->Y -= 7.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_W))
            _rect->Position->Y += 7.f * Time::DeltaTime();

        _camera->Position = _rect->Position();

        if (Input::IsKeyPressedOnce(Keys::RVL_KEY_SPACE))
            _rect->SetColor({0.5f, 1.f, 1.f});
    }

    void MainScene::Render()
    {
        _rect->Draw();
        _sprite1->Draw();
        _sprite2->Draw();
        _sprite3->Draw();
    }
}
