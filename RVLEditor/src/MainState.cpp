#include "MainState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>
#include "TestScript.hpp"

MainState::MainState() : State((RenderMode)(RenderMode_3D | RenderMode_2D)) {}
MainState::~MainState() {}

struct EditorUIData 
{
    ImGuiWindowFlags GlobalWinFlags;
    glm::vec2 FBOViewport;
};

static EditorUIData UIData;

void MainState::Start()
{
    CreateFrameBuffer({1000, 600});

    _camera = UserPerspectiveCamera::New({0.f, 0.f, 0.f}, 45.f);

    _directionalLight = _currentScene.NewEntity();
    _directionalLight.AddComponent<DirectionalLightComponent>(glm::vec3(0.9f, 0.9f, 0.9f));
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
    _sprite.AddComponent<PointLightComponent>(glm::vec3(0.4f, 0.9f, 0.5f), 0.09f, 0.032f);
}

void MainState::Update()
{
    UserCamera::ToPerspective(_camera)->UpdateControls(ControllerType::InPlane, 5.f);
    DockspaceAndMenu();
    
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

    ImGui::Begin("Properties", nullptr, UIData.GlobalWinFlags);
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

    ImGui::Begin("Scene", nullptr, UIData.GlobalWinFlags);
        ImGui::BeginChild("Render");
        
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (UIData.FBOViewport != ImToGlmVec2(viewportSize))
        {
            UIData.FBOViewport = {viewportSize.x, viewportSize.y};
            _fbo->Resize(viewportSize.x, viewportSize.y);
        }

        ImGui::Image(
            (ImTextureID)_fbo->GetColorAttachment(), 
            ImGui::GetContentRegionAvail(), 
            ImVec2(0, 1), 
            ImVec2(1, 0)
        );
        ImGui::EndChild();
    ImGui::End();

    Renderer::ResetStats();
}


void MainState::DockspaceAndMenu()
{
    static bool dockspaceOpen = true;
    static bool optFullscreen = true;
    static bool optPadding = false;

    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        windowFlags |= ImGuiWindowFlags_NoBackground;

    if (!optPadding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);
    if (!optPadding)
        ImGui::PopStyleVar();

    if (optFullscreen)
        ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))   
        {
            ImGui::MenuItem("File");
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}
