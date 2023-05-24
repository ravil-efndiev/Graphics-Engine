#include "MapEditorApp.hpp"
#include "MapScene.hpp"

#include <RVL/Core/EntryPoint.hpp>

RVL_IMPL_INIT(rvl::MapEditorApp);

namespace rvl
{
    struct AppUIData
    {
        bool ProjectCreation, ProjectOpen, PrjCreateWindowOpen = true;
        bool OpenFromTls = false;

        static constexpr size_t MaxNameSize = 100;
        char ProjectName[MaxNameSize];

        static constexpr size_t MaxFilenameSize = 1000;
        char TlmName[MaxFilenameSize];
        char TlsName[MaxFilenameSize];

        char TexName[MaxFilenameSize] = "./assets/textures/map.png";

        ImGuiWindowFlags ProjectWinFlags;
    };

    static AppUIData AppUiData;

    MapEditorApp::MapEditorApp() : RvlApp(1000, 700, "RVL Map Editor") {}
    MapEditorApp::~MapEditorApp() {}

    void MapEditorApp::Start()
    {
        SetClearColor({0.0f, 0.3f, 0.3f});
        AppUiData.ProjectCreation = true;
        AppUiData.ProjectOpen = false;

        SetDefaults();
    }

    void MapEditorApp::Update()
    {
        DockspaceAndMenu();

        if (AppUiData.ProjectCreation)
            ProjectWindow();

        if (AppUiData.ProjectOpen)
            ProjectOpenWindow();
        else
            AppUiData.ProjectWinFlags &= ~ImGuiWindowFlags_NoInputs;

        if (!AppUiData.PrjCreateWindowOpen && !_currentScene)
            Close();
        
        if (!AppUiData.PrjCreateWindowOpen && _currentScene)
        {
            AppUiData.ProjectCreation = false;
            std::dynamic_pointer_cast<MapScene>(_currentScene)->InputsEnabled(true);
        }

        if (!AppUiData.ProjectCreation && !AppUiData.ProjectOpen && _currentScene)
        {
            _currentScene->Update();
        }
    }

    void MapEditorApp::DockspaceAndMenu()
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
                if (ImGui::MenuItem("New Project", nullptr, false))
                {
                    AppUiData.ProjectCreation = true;
                    AppUiData.PrjCreateWindowOpen = true;
                    SetDefaults();
                } 
                if (ImGui::MenuItem("Exit", nullptr, false)) Close();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

    void MapEditorApp::ProjectWindow()
    {
        if (_currentScene)
            std::dynamic_pointer_cast<MapScene>(_currentScene)->InputsEnabled(false);

        ImGui::Begin("Project", &AppUiData.PrjCreateWindowOpen, AppUiData.ProjectWinFlags);
        ImGui::Text("Create New Project: \n\n");

        ImGui::Text("Project name (max 100 symbols)");
        ImGui::InputText("##prjNameInput", AppUiData.ProjectName, AppUiData.MaxNameSize);
        ImGui::Text("\n");

        ImGui::Checkbox("Open from tileset", &AppUiData.OpenFromTls);
        ImGui::Text("Texture path or Tileset path");
        ImGui::InputText("##texPathInput", AppUiData.TexName, AppUiData.MaxFilenameSize);

        if (ImGui::Button("Create Project", ImVec2(ImGui::GetContentRegionAvail().x, 40)))
        {
            if (!AppUiData.OpenFromTls)
                _currentScene = NewRef<MapScene>(AppUiData.TexName);
            else
            {
                Ref<TileSet> tls = NewRef<TileSet>(AppUiData.TexName);
                _currentScene = NewRef<MapScene>(tls);
            }
            _currentScene->Start();
            AppUiData.ProjectCreation = false;
        }

        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 100);
        ImGui::Separator();
        ImGui::Text("Or: \n");

        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(232, 108, 108, 255));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(255, 128, 128, 255));
        if (ImGui::Button("Cancel", ImVec2(ImGui::GetContentRegionAvail().x / 2 - 10, 30)))
        {
            AppUiData.ProjectCreation = false;

            if (_currentScene)            
                std::dynamic_pointer_cast<MapScene>(_currentScene)->InputsEnabled(true);

            if (!_currentScene)
                Close();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::SameLine();

        if (ImGui::Button("Open Existing", ImVec2(ImGui::GetContentRegionAvail().x - 10, 30)))
        {
            AppUiData.ProjectWinFlags |= ImGuiWindowFlags_NoInputs;
            AppUiData.ProjectOpen = true;
        }

        ImGui::End();
    }

    void MapEditorApp::ProjectOpenWindow()
    {
        ImGui::Begin("Open Existing Project", &AppUiData.ProjectOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);

        ImGui::Text("TileMap file path (.rtlm)");
        ImGui::InputText("##tlmName", AppUiData.TlmName, AppUiData.MaxFilenameSize);
        ImGui::Text("\nTileSet file path (.rtls)");
        ImGui::InputText("##tlsName", AppUiData.TlsName, AppUiData.MaxFilenameSize);
        ImGui::Text("\n");

        if (ImGui::Button("Open", ImVec2(ImGui::GetContentRegionAvail().x / 1.5, 20)))
        {
            //_currentScene = NewRef<MapScene>();
            //_currentScene->Start();
            AppUiData.ProjectOpen = false;
            AppUiData.ProjectCreation = false;
        }

        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(232, 108, 108, 255));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(255, 128, 128, 255));

        if (ImGui::Button("Cancel", ImVec2(ImGui::GetContentRegionAvail().x / 1.5, 20)))
        {
            AppUiData.ProjectWinFlags &= ~ImGuiWindowFlags_NoInputs;
            AppUiData.ProjectOpen = false;
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();

        ImGui::End();
    }
    
    void MapEditorApp::SetDefaults()
    {
        AppUiData.ProjectName[0] = '\0';
        
        AppUiData.ProjectWinFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking;
    }
}
