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
        _camera = Camera::Create({0.f, 0.f}, 5.f);

        _rect = Rectangle::Create({0.f, 0.f, 0.f}, {3.f, 3.f}, {0.8f, 0.4f, 0.4f});

        _sprite = Sprite::Create({0.f, 0.f, 0.f}, 2.f);
        _sprite->LoadTexture("a.jpg");

        _sprite1 = Sprite::Create({3.f, 3.f, 0.f}, 2.f);
        _sprite1->LoadTexture("floor1.png");


        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                _bg[i][j] = Rectangle::Create({{i + 2.f, j + 2.f, 0.f}, 0.f, {1.5f, 1.5f}}, {0.3f, 0.3f, 0.3f});
            }
        }
    }

    void MainScene::Update() 
    {
        if (Input::IsKeyPressed(Keys::RVL_KEY_D))
            _rect->transform->Position.x += 5.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_A))
            _rect->transform->Position.x -= 5.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_W))
            _rect->transform->Position.y += 5.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_S))
            _rect->transform->Position.y -= 5.f * Time::DeltaTime();

        _camera->Follow(_rect, Axis::Horizontal | Axis::Vertical, true, _smoothSpeed);
    }

    void MainScene::Render()
    {
        RenderImGui();

        _rect->Draw();

        _sprite->Draw();
        _sprite1->Draw();
    }

    void MainScene::RenderImGui()
    {
        ImGui::Begin("Properties");
        ImGui::ColorPicker3("Rectangle color", _rect->GetColorPtr());
        ImGui::SliderFloat("camera smooth speed", &_smoothSpeed, 0.f, 20.f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Application immidieate %.3f ms/frame (%.1f FPS)", 1000.f / (1.f / Time::DeltaTime()), 1.f / Time::DeltaTime());
        ImGui::End();
    }
}
