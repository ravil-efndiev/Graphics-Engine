#include "MainScene.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace name
{
    using namespace rvl;

    MainScene::MainScene() {}
    MainScene::~MainScene() {}

    void MainScene::Start()
    {
        _camera = Camera::Create({0.f, 0.f}, 15.f);

        _rect = Rectangle::Create({0.f, 0.f, 0.f}, {3.f, 3.f}, {0.8f, 0.4f, 0.4f});

        _texture = CreateRef<GLTexture>("container.jpg");
        _texture2 = CreateRef<GLTexture>("floor1.png");

        _sprite = Sprite::Create({-5.f, -5.f, 0.f}, 2.f);
        _sprite->LoadTexture("a.jpg");
    }

    void MainScene::Update() 
    {
        _camera->UpdateZoomChange();
        _camera->UpdateMovement(_camSpeed);

        if (Input::IsKeyPressed(Keys::RVL_KEY_D))
            _rect->transform->Position.x += 5.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_A))
            _rect->transform->Position.x -= 5.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_W))
            _rect->transform->Position.y += 5.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_S))
            _rect->transform->Position.y -= 5.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_SPACE))
            _sprite->transform->Rotation += 10.f;
            
        ImGui::Begin("Properties");
        ImGui::ColorPicker3("Rectangle color", _rect->GetColorPtr());
        ImGui::DragFloat("Camera speed", &_camSpeed, 0.5f, 0.f, 100.f);
        ImGui::End();
    }

    void MainScene::Render()
    {
        Renderer::DrawRect({{1.5f, -1.f, 0.f}, 0.f, {5.f, 3.f}}, {1.f, 0.3f, 1.f});
        Renderer::DrawRect({{-3.f, 5.f, 0.f}, 0.f, {2.f, 4.f}}, {0.5f, 0.5f, 1.f});

        Renderer::DrawRect({{4.f, 4.f, 0.f}, 45.f, {2.f, 2.f}}, *_texture);
        Renderer::DrawRect({{-4.f, -4.f, 0.f}, 0.f, {2.f, 2.f}}, *_texture2);

        // Renderer::DrawRect(_rect->transform, _rect->GetColor());
        // Renderer::DrawRect(_sprite->transform, *_sprite->GetTexture());

        _rect->Draw();
        _sprite->Draw();

    }
}
