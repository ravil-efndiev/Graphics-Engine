#include "MainState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>
#include "TestScript.hpp"

MainState::MainState() : State((RenderMode)(RenderMode_3D | RenderMode_2D)) {}
MainState::~MainState() {}

void MainState::Start()
{
    _camera = UserPerspectiveCamera::New({0.f, 0.f, 0.f}, 45.f);

    _directionalLight = _currentScene->NewEntity();
    _directionalLight.Add<DirectionalLight>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(0.5f, 0.5f, 0.5f));
    _dlTf = &_directionalLight.Get<Transform>();

    _model = _currentScene->NewEntity();
    _model.Add<Model>().Meshes = StandartMeshes::Get("Cube");
    _mat = &_model.Add<Material>(glm::vec3(0.9f, 0.8f, 0.5f), 0.5f);

    _sprite = _currentScene->NewEntity(glm::vec3{5.f, 0.f, 5.f});
    (_sTf = &_sprite.Get<Transform>());
    _sprite.Add<Sprite>("assets/textures/container.jpg", 1.f);
    _sprite.Add<PointLight>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(0.5f, 0.5f, 0.5f), 0.09f, 0.032f);
}

void MainState::Update()
{
    UserCamera::ToPerspective(_camera)->UpdateControls(ControllerType::InPlane, 5.f);
    
    if (Input::IsKeyPressedOnce(Keys::Key_Escape))
    {
        _lock = !_lock;
        App::GetInstance()->SetCursorLocked(_lock);
    }

    if (_lock)
        UserCamera::ToPerspective(_camera)->UpdateCursorRotation(2.f);

    _mat->SetUniform("u_ViewPos", UserCamera::ToPerspective(_camera)->Position());
    _dlTf->Rotation = _light;
    _sTf->Position = _lightPosition;
}

void MainState::Render()
{
    RenderImGui();
    SceneRenderer::Render(_currentScene, _camera);    
}

void MainState::PostRender()
{
}

void MainState::RenderImGui()
{
    auto stats = Renderer::GetStats();

    ImGui::Begin("Properties");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Application immidieate %.3f ms/frame (%.1f FPS)", 1000.f / (1.f / Time::DeltaTime()), 1.f / Time::DeltaTime());
    ImGui::Separator();
    ImGui::SliderFloat3("Light direction", glm::value_ptr(_light), -1.f, 1.f);
    ImGui::SliderFloat3("Light Position", glm::value_ptr(_lightPosition), -10.f, 10.f);
    ImGui::Separator();
    ImGui::Text("Draw calls: %d", stats.DrawCalls);
    ImGui::Text("Total verticies: %d", stats.VerticiesCount);
    ImGui::Text("Total indicies: %d", stats.IndiciesCount);
    ImGui::Text("Total Rectangles: %d", stats.RectCount);
    ImGui::End();


    Renderer::ResetStats();
}
