#include "MainState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>
#include "TestScript.hpp"

MainState::MainState() : State((RenderMode)(RenderMode_3D | RenderMode_2D)) {}
MainState::~MainState() {}

void MainState::Start()
{
    CreateFrameBuffer({1000, 600});

    _camera = UserPerspectiveCamera::New({0.f, 0.f, 0.f}, 45.f);

    _directionalLight = _currentScene.NewEntity();
    _directionalLight.AddComponent<DirectionalLightComponent>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(0.5f, 0.5f, 0.5f));
    _dlTf = &_directionalLight.GetComponent<TransformComponent>();

    _model = _currentScene.NewEntity();
    _model.AddComponent<ModelComponent>("./assets/textures/backpack.obj");
    _mat = &_model.AddComponent<MaterialComponent>(StandartShaderLib::Get("Light"));
    _mat->ProcessLightSources(true);

    _mat->Set("u_Material.diffuse",  glm::vec3(0.5f, 0.5f, 0.5f));
    _mat->Set("u_Material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    _mat->Set("u_Material.ambient",  glm::vec3(1.0f, 0.5f, 0.31f));
    _mat->Set("u_Material.shininess", 32.f);

    _sprite = _currentScene.NewEntity();
    (_sTf = &_sprite.GetComponent<TransformComponent>())->Position->x = 5.f;
    _sprite.AddComponent<SpriteComponent>("assets/textures/container.jpg", 1.f);
    _sprite.AddComponent<PointLightComponent>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(0.5f, 0.5f, 0.5f), 0.09f, 0.032f);
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
    {
        glm::vec2 viewport = RenderCommand::GetViewport();

        _camRotation += Input::GetCursorDelta() / (float)viewport.y * 2.f;
        
        if (_camRotation.y > glm::radians(89.f))
            _camRotation.y = glm::radians(89.f);

        if (_camRotation.y < -glm::radians(89.f))
            _camRotation.y = -glm::radians(89.f);

        UserCamera::ToPerspective(_camera)->Rotate(_camRotation.y, _camRotation.x, 0.f);
    }

    _mat->Set("u_ViewPos", glm::vec4((glm::vec3)UserCamera::ToPerspective(_camera)->Position, 0.f));
    _dlTf->Rotation = _light;
    _sTf->Position = _lightPosition;
}

void MainState::Render()
{
    RenderImGui();
    
    _currentScene.DrawModel(_model);
    _currentScene.DrawSprite(_sprite);
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

    ImGui::Image(
        (ImTextureID)_fbo->GetColorAttachment(),
        ImVec2(1000, 600), 
        ImVec2(0, 1), 
        ImVec2(1, 0)
    );
    ImGui::End();


    Renderer::ResetStats();
}
