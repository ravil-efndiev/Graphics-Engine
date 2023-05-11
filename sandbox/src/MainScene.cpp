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

        _sprite = Sprite::Create({0.f, 0.f, 0.f}, 2.f);
        _sprite->LoadTexture("assets/textures/a.jpg");

        _sprite1 = Sprite::Create({3.f, 3.f, 0.f}, 2.f);
        _sprite1->LoadTexture("assets/textures/floor1.png");
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

        if (Input::IsKeyPressed(Keys::RVL_KEY_SPACE))
            _rect->transform->Rotation += 50.f * Time::DeltaTime();

        _camera->Follow(_rect, Axis::Horizontal | Axis::Vertical, true, _smoothSpeed);
    }

    void MainScene::Render()
    {
        RenderImGui();

        _sprite1->Draw();
        _sprite->Draw();
        _rect->Draw();

        for (float i = -40.f; i < 40.f; i += 0.5f)
        {
            for (float j = -40.f; j < 40.f; j += 0.5f)
            {
                glm::vec4 color = {(i + 40.f) / 80.f, 0.3f, (j + 40.f) / 80.f, 1.f};
                Renderer::DrawRect({{j, i, 0.f}, 0.f, {0.45f, 0.45f}}, color);
            }
        }
    }

    void MainScene::RenderImGui()
    {
        auto stats = Renderer::GetStats();

        ImGui::Begin("Properties");
        ImGui::ColorPicker3("Rectangle color", _rect->GetColorPtr());
        ImGui::SliderFloat("camera smooth speed", &_smoothSpeed, 0.f, 20.f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Application immidieate %.3f ms/frame (%.1f FPS)", 1000.f / (1.f / Time::DeltaTime()), 1.f / Time::DeltaTime());
        ImGui::Text("Renderer statistics:");
        ImGui::Text("Draw calls count: %d", stats.DrawCalls);
        ImGui::Text("Rectangles count: %d", stats.RectCount);
        ImGui::Text("Verticies count: %d", stats.VerticiesCount);
        ImGui::Text("Indicies count: %d", stats.IndiciesCount);
        ImGui::End();

        Renderer::ResetStats();
    }
}
