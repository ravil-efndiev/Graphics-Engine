#include "MainState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <API/Objects/TileSet.hpp>

#include "Rendering/Renderer/Renderer3D.hpp"

#include "TestScript.hpp"

MainState::MainState() : State(RenderMode::Mode_3D) {}
MainState::~MainState() {}

void MainState::Start()
{
    _camera = UserPerspectiveCamera::New(glm::vec3(0.f, 0.f, 3.f), 45.f);

    _model = NewRef<Model>("./assets/textures/backpack.obj");

    _mShader = NewRef<GLShaderProgram>("assets/shaders/a.vert", "assets/shaders/a.frag");
    _mShader->Link();
}

void MainState::Update()
{
    if (Input::IsKeyPressed(Keys::Key_W))
        UserCamera::ToPerspective(_camera)->Move(Direction::ForwardHorizontal, 5.f);

    if (Input::IsKeyPressed(Keys::Key_S))
        UserCamera::ToPerspective(_camera)->Move(Direction::BackHorizontal, 5.f);

    if (Input::IsKeyPressed(Keys::Key_A))
        UserCamera::ToPerspective(_camera)->Move(Direction::Left, 5.f);
        
    if (Input::IsKeyPressed(Keys::Key_D))
        UserCamera::ToPerspective(_camera)->Move(Direction::Right, 5.f);

    if (Input::IsKeyPressed(Keys::Key_Space))
        UserCamera::ToPerspective(_camera)->Position->y += 5.f * Time::DeltaTime();

    if (Input::IsKeyPressed(Keys::Key_LeftShift))
        UserCamera::ToPerspective(_camera)->Position->y -= 5.f * Time::DeltaTime();

    if (Input::IsKeyPressedOnce(Keys::Key_T))
    {
        _lock = !_lock;
        App::GetInstance()->SetCursorLocked(_lock);
    }

    if (_lock)
    {
        int vp[2];
        RenderCommand::GetViewport(vp);

        _camRotation += Input::GetCursorDelta() / (float)vp[1] * 2.f;
        
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

void MainState::Tick()
{
}

void MainState::Render()
{
    RenderImGui();

    _model->Draw(_mShader);
}

void MainState::RenderImGui()
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

    ImGui::SliderFloat3("Light position", glm::value_ptr(_light), -10.f, 10.f);
    ImGui::End();

    Renderer::ResetStats();
}
