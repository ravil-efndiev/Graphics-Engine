#include "EditorState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>

struct EditorUIData 
{
    ImGuiWindowFlags GlobalWinFlags;
    glm::vec2 FBOViewport;
};

static EditorUIData UIData;

EditorState::EditorState() : State((RenderMode)(RenderMode_3D | RenderMode_2D)) {}
EditorState::~EditorState() {}

void EditorState::Start()
{
    CreateFrameBuffer({1000, 600});

    _camera = UserPerspectiveCamera::New({0.f, 0.f, 0.f}, 45.f);

    _directionalLight = _currentScene.NewEntity("Directional light");
    _directionalLight.Add<DirectionalLightComponent>(glm::vec3(0.9f, 0.9f, 0.9f));
    _dlTf = &_directionalLight.Get<TransformComponent>();

    _model = _currentScene.NewEntity("Model");
    _model.Add<ModelComponent>("./assets/textures/backpack.obj");
    _mat = &_model.Add<MaterialComponent>(StandartShaderLib::Get("Light"));
    _mat->ProcessLightSources(true);

    _mat->Set("u_Material.diffuse",  glm::vec3(0.5f, 0.5f, 0.5f));
    _mat->Set("u_Material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    _mat->Set("u_Material.ambient",  glm::vec3(1.0f, 0.5f, 0.31f));
    _mat->Set("u_Material.shininess", 32.f);

    _sprite = _currentScene.NewEntity("Sprite");
    (_sTf = &_sprite.Get<TransformComponent>())->Position->x = 5.f;
    _sprite.Add<SpriteComponent>("assets/textures/container.jpg", 1.f);
    _sprite.Add<PointLightComponent>(glm::vec3(0.4f, 0.9f, 0.5f), 0.09f, 0.032f);

    _hierarchy = NewRef<HierarchyWindow>(_currentScene);
    _inspector = NewRef<InspectorWindow>();
}

void EditorState::Update()
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
}

void EditorState::Render()
{
    RenderImGui();
    
    _currentScene.DrawModel(_model);
    _currentScene.DrawSprite(_sprite);
}

void EditorState::RenderImGui()
{
    auto stats = Renderer::GetStats();

    ImGui::Begin("Properties", nullptr, UIData.GlobalWinFlags);
        ImGui::Text("Application average %.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
        ImGui::Text("Application immidieate %.1f FPS (%.3f ms/frame)", 1.f / Time::DeltaTime(), 1000.f / (1.f / Time::DeltaTime()));
        ImGui::Separator();
        ImGui::Text("Draw calls: %d", stats.DrawCalls);
        ImGui::Text("Total verticies: %d", stats.VerticiesCount);
        ImGui::Text("Total indicies: %d", stats.IndiciesCount);
        ImGui::Text("Total Rectangles: %d", stats.RectCount);

    ImGui::End();

    _hierarchy->ImGuiRender();

    _inspector->SetSelected(_hierarchy->GetSelected());
    _inspector->ImGuiRedner();

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


void EditorState::DockspaceAndMenu()
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
