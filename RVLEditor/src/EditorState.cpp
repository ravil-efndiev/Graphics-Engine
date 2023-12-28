#include "EditorState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>
#include <nfd.h>
#include <Core/Utils/Files.hpp>

struct EditorUIData 
{
    ImGuiWindowFlags GlobalWinFlags;
    ImVec2 SceneWindowPosition, MainWindowPosition;
    glm::vec2 FBOViewport;
};

static EditorUIData UIData;

EditorState::EditorState() : State(RenderMode_Any) {}
EditorState::~EditorState() {}

void EditorState::Start()
{
    _first = NewRef<GLFrameBuffer>(FrameBufferSpecification{500, 600, 4});
    _second = NewRef<GLFrameBuffer>(FrameBufferSpecification{500, 600, 1});

    _camera = UserPerspectiveCamera::New({0.f, 0.f, 0.f}, 45.f);

    _directionalLight = _currentScene->NewEntity("Directional light");
    _directionalLight.Add<DirectionalLight>(glm::vec3(0.9f, 0.9f, 0.9f));

    _tlm = _currentScene->NewEntity("tilemap");
    emitter = &_tlm.Add<ParticleEmitter>(1000);

    _directionalLight.AddChild(_tlm);

    _hierarchy = NewRef<HierarchyWindow>(_currentScene);
    _inspector = NewRef<InspectorWindow>();
}

void EditorState::Update()
{
    if (Input::IsKeyPressedOnce(Keys::Key_Escape))
    {
        _lock = !_lock;
        App::GetInstance()->SetCursorLocked(_lock);
    }

    UserCamera::ToPerspective(_camera)->UpdateControls(ControllerType::InPlane, 5.f);

    if (_lock) UserCamera::ToPerspective(_camera)->UpdateCursorRotation(2.f);
}

void EditorState::Render()
{
    _first->Bind();
    RenderCommand::Clear();

    SceneRenderer::Render(_currentScene, _camera);
}

void EditorState::PostRender()
{
    _first->Bind2(_second);
    _first->Unbind();
    
    DockspaceAndMenu();
    RenderImGui();
}
void EditorState::RenderImGui()
{
    auto stats = Renderer::GetStats();
    UIData.MainWindowPosition = ImGui::GetMainViewport()->Pos;

    ImGui::Begin("Statistics", nullptr, UIData.GlobalWinFlags);
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
            _first->Resize(viewportSize.x, viewportSize.y);
            _second->Resize(viewportSize.x, viewportSize.y);
        }

        UIData.SceneWindowPosition = ImGui::GetWindowPos();

        ImGui::Image(
            reinterpret_cast<ImTextureID>(_second->GetColorAttachment()), 
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
            if (ImGui::MenuItem("Save"))
            {
                SceneSerializer sz (_currentScene);

                if (!_scenePath.empty())
                    sz.Serialize(_scenePath);
                else
                {
                    nfdchar_t* openPath = nullptr;
                    nfdresult_t result = NFD_SaveDialog("rscn", "assets/", &openPath);

                    if (result == NFD_OKAY)
                    {
                        sz.Serialize(openPath);
                        _scenePath = openPath;
                        free(openPath);
                    }
                }
            }

            if (ImGui::MenuItem("Save As"))
            {
                nfdchar_t* openPath = nullptr;
                nfdresult_t result = NFD_SaveDialog("rscn", "assets/", &openPath);

                if (result == NFD_OKAY)
                {
                    SceneSerializer sz (_currentScene);
                    sz.Serialize(openPath);
                    _scenePath = openPath;
                    free(openPath);
                }
            }

            if (ImGui::MenuItem("Open"))
            {
                nfdchar_t* openPath = nullptr;
                nfdresult_t result = NFD_OpenDialog("rscn", "assets/", &openPath);

                if (result == NFD_OKAY)
                {
                    _currentScene = NewRef<Scene>();
                    SceneSerializer sz (_currentScene);
                    sz.Deserialize(openPath);
                    _hierarchy->SetScene(_currentScene);
                    _scenePath = openPath;
                    free(openPath);
                }

            }

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}
