#include "MainScene.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <API/Components/MovementComponent.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace name
{
    using namespace rvl;

    MainScene::MainScene() {}
    MainScene::~MainScene() {}

    void MainScene::Start()
    {
        _camera = Camera::Create({0.f, 0.f}, 15.f);

        _player = NewRef<Player>();

        _sprite = Sprite::Create({0.f, 0.f, 0.f}, 2.f);
        _sprite->LoadTexture("assets/textures/a.jpg");

        _sprite1 = Sprite::Create({3.f, 3.f, 0.01f}, 2.f);
        _sprite1->LoadTexture("assets/textures/floor1.png");

        _subtextureEx = Sprite::Create({-3.f, -5.f, 0.01f}, 5.f);
        _subtextureEx->LoadTexture("assets/textures/map.png");
        _subtextureEx->SetSubTexture(0, 3, 128, 128);
    }

    void MainScene::Update()
    {
        _player->Update();
    }

    void MainScene::Tick()
    {
        _camera->Follow(_player, Axis::Horizontal | Axis::Vertical, true, _smoothSpeed, 0.05f, Time::FixedDeltaTime());
    }

    void MainScene::Render()
    {
        RenderImGui();

        _sprite->Draw();

        for (int i = -80; i < 80; i++)
        {
            for (int j = -80; j < 80; j++)
            {
                glm::vec4 color = {(i + 80.f) / 160.f, 0.3f, (j + 80.f) / 160.f, 0.5f};
                Renderer::DrawRect({{j, i, 0.f}, 0.f, {0.8f, 0.8f}}, color);
            }
        }
        _sprite1->Draw();
        _subtextureEx->Draw();
        _player->Draw();
    }

    void MainScene::RenderImGui()
    {
        auto stats = Renderer::GetStats();

        ImGui::Begin("Properties");
        ImGui::ColorPicker3("Rectangle color", _player->GetRect()->GetColorPtr());
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
