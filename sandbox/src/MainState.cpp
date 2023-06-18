#include "MainState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <API/ECS/MovementComponent.hpp>
#include <API/ECS/AnimationComponent.hpp>
#include <API/ECS/SpriteComponent.hpp>
#include <API/ECS/TileMapComponent.hpp>
#include <API/Objects/TileSet.hpp>

#include "Rendering/Renderer/Renderer3D.hpp"

#include "TestScript.hpp"

MainState::MainState() {}
MainState::~MainState() {}

struct Vertex
{
    glm::vec3 Position;
    glm::vec4 Color;
};

void MainState::Start()
{
    _camera = UserPerspectiveCamera::Create(glm::vec3(0.f, 0.f, 3.f), 45.f);

    _vao = NewRef<GLVertexArray>();

    std::vector<Vertex> verticies =
    {
        { {-1.0, -1.0, 1.0}, { 1.f, 0.f, 0.f, 1.f } },
        { {1.0,  -1.0, 1.0}, { 1.f, 0.f, 0.f, 1.f } },
        { {1.0,  1.0,  1.0}, { 1.f, 0.f, 0.f, 1.f } },
        { {-1.0, 1.0,  1.0}, { 1.f, 0.f, 0.f, 1.f } },

        { {-1.0, -1.0, -1.0}, { 1.f, 0.f, 0.f, 1.f } },
        { {1.0,  -1.0, -1.0}, { 1.f, 0.f, 0.f, 1.f } },
        { {1.0,  1.0,  -1.0}, { 1.f, 0.f, 0.f, 1.f } },
        { {-1.0, 1.0,  -1.0}, { 1.f, 0.f, 0.f, 1.f } },
    };

    _vbo = NewRef<GLVertexBuffer>(verticies);
    _vbo->SetLayout({
        LayoutElement { ElementType::Vec3, 0, sizeof(Vertex), false },
        LayoutElement { ElementType::Vec4, offsetof(Vertex, Color), sizeof(Vertex), false }
    });

    RVL_LOG(offsetof(Vertex, Color));

    Ref<GLIndexBuffer> ibo = NewRef<GLIndexBuffer>(std::vector<uint32>({
		0, 1, 2, 2, 3, 0,
		1, 5, 6, 6, 2, 1,
		7, 6, 5, 5, 4, 7,
		4, 0, 3, 3, 7, 4,
		4, 5, 1, 1, 0, 4,
		3, 2, 6, 6, 7, 3
    }));

    _vao->SetSingleVertexBuffer(_vbo);
    _vao->AddIndexBuffer(ibo);

    _shader = NewRef<GLShaderProgram>("assets/shaders/sigma.vert", "assets/shaders/sigma.frag");
    _shader->BindAttribute(0, "position");
    _shader->BindAttribute(1, "color");
    _shader->Link();
}

void MainState::Update()
{
    if (Input::IsKeyPressed(Keys::Key_W))
        UserCamera::ToPerspective(_camera)->Move(Direction::ForwardHorizontal, 10.f);

    if (Input::IsKeyPressed(Keys::Key_S))
        UserCamera::ToPerspective(_camera)->Move(Direction::BackHorizontal, 10.f);

    if (Input::IsKeyPressed(Keys::Key_A))
        UserCamera::ToPerspective(_camera)->Move(Direction::Left, 10.f);
        
    if (Input::IsKeyPressed(Keys::Key_D))
        UserCamera::ToPerspective(_camera)->Move(Direction::Right, 10.f);

    if (Input::IsKeyPressed(Keys::Key_Space))
        UserCamera::ToPerspective(_camera)->Position->y += 10.f * Time::DeltaTime();

    if (Input::IsKeyPressed(Keys::Key_LeftShift))
        UserCamera::ToPerspective(_camera)->Position->y -= 10.f * Time::DeltaTime();

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
}

void MainState::Tick()
{
}

void MainState::Render()
{
    RenderImGui();

    Renderer3D::Submit(_vao, _shader);
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
    ImGui::End();

    Renderer::ResetStats();
}
