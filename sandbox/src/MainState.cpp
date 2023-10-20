#include "MainState.hpp"

#include <3D/ModelComponent.hpp>
#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>
#include <Rendering/Renderer/RenderCommand.hpp>
#include "TestScript.hpp"
#include <Rendering/OpenGL/GLFrameBuffer.hpp>

MainState::MainState() : State((RenderMode)(RenderMode_3D | RenderMode_2D)) {}
MainState::~MainState() {}

void MainState::Start()
{
    _camera = UserPerspectiveCamera::New({0.f, 0.f, 0.f}, 45.f);

    _model = _currentScene.NewEntity();
    _model.AddComponent<ModelComponent>("./assets/textures/backpack.obj");
    RVL_ADD_BEHAVIOUR(_currentScene, _model, TestScript);
    
    (_mShader = NewRef<GLShaderProgram>("assets/shaders/light"))->Link();

    CreateFrameBuffer();
    _postProcess = NewRef<PostProcess>(_fbo, "assets/shaders/screen");

    _sprite = _currentScene.NewEntity();
    _sprite.GetComponent<TransformComponent>().Position->x = 5.f;
    _sprite.AddComponent<SpriteComponent>("assets/textures/container.jpg", 1.f);
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
    
    
    _mShader->Bind();
    _mShader->SetUniformVec4("u_Direction", glm::vec4(_light, 0.f));
    _mShader->SetUniformVec4("u_ViewPos", glm::vec4((glm::vec3)UserCamera::ToPerspective(_camera)->Position, 0.f));
}

void MainState::Tick() {}

void MainState::Render()
{
    RenderImGui();
    _postProcess->Begin();
    _currentScene.DrawSprite(_sprite);
    _currentScene.DrawModel(_model, _mShader);
}

void MainState::PostRender()
{
    _postProcess->End();
}

void MainState::RenderImGui()
{
    auto stats = Renderer::GetStats();

    ImGui::Begin("Properties");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Application immidieate %.3f ms/frame (%.1f FPS)", 1000.f / (1.f / Time::DeltaTime()), 1.f / Time::DeltaTime());
    ImGui::SliderFloat3("Light direction", glm::value_ptr(_light), -10.f, 10.f);
    ImGui::Separator();
    ImGui::Text("Draw calls: %d", stats.DrawCalls);
    ImGui::Text("Total verticies: %d", stats.VerticiesCount);
    ImGui::Text("Total indicies: %d", stats.IndiciesCount);
    ImGui::Text("Total Rectangles: %d", stats.RectCount);
    ImGui::End();

    Renderer::ResetStats();
}
