#include "MainScene.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <API/ECS/MovementComponent.hpp>
#include <API/ECS/AnimationComponent.hpp>
#include <API/ECS/SpriteComponent.hpp>
#include <API/ECS/TileMapComponent.hpp>
#include <API/Objects/TileSet.hpp>

#include "TestScript.hpp"

MainScene::MainScene() {}
MainScene::~MainScene() {}

void MainScene::Start()
{
    _camera = Camera::Create({0.f, 0.f}, 15.f);
    _test = _currentScene.NewEntity();
    _tileMap = _currentScene.NewEntity();
    
    _tileMap.AddComponent<TileMapComponent>(NewRef<TileSet>("assets/maps/test.rtls"), "assets/maps/test.rtlm", 2.f, 0.f);
    _sc = &_test.AddComponent<SpriteComponent>(&_test, "assets/textures/floor1.png", 2.f);
    _tc = &_test.GetComponent<TransformComponent>();

    _sc->UseColorAsTint(true);

    _currentScene.AddBehaviour(&_test.AddComponent<TestScript>(_test));
}

void MainScene::Update()
{
    _sc->SetColor(_tintColor);

    _camera->Follow(_tc, Axis::Horizontal | Axis::Vertical, false);
}

void MainScene::Tick()
{
}

void MainScene::Render()
{
    RenderImGui();

    for (int i = -80; i < 80; i++)
    {
        for (int j = -80; j < 80; j++)
        {
            glm::vec4 color = {(i + 80.f) / 160.f, 0.3f, (j + 80.f) / 160.f, 0.5f};
            Renderer::DrawRect({{j, i, -0.01f}, 0.f, {0.8f, 0.8f}}, color);
        }
    }

    _currentScene.DrawSprite(_test);
    _currentScene.DrawTileMap(_tileMap);
}

void MainScene::RenderImGui()
{
    auto stats = Renderer::GetStats();

    ImGui::Begin("Properties");
    ImGui::SliderFloat("camera smooth speed", &_smoothSpeed, 0.f, 20.f);
    ImGui::ColorEdit4("Tint color", glm::value_ptr(_tintColor));
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
