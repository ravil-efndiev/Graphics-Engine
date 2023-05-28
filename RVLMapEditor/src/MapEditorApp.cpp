#include "MapEditorApp.hpp"
#include "MapScene.hpp"

#include <RVL/Core/EntryPoint.hpp>
#include <RVL/Core/Utils/Files.hpp>

RVL_IMPL_INIT(rvl::MapEditorApp);

namespace rvl
{
    struct AppUIData
    {
        bool ProjectCreation, ProjectOpen, PrjCreateWindowOpen = true;
        bool DeleteFileWindow = false;
        bool DeleteTileSet = false, DeleteTileMap = true;
        bool UseTls = false, UseTlm = false;

        static constexpr size_t MaxNameSize = 100;
        char ProjectName[MaxNameSize];

        static constexpr size_t MaxFilenameSize = 1000;
        char TlmName[MaxFilenameSize];
        char TlsName[MaxFilenameSize];

        char TexName[MaxFilenameSize] = "./assets/maps/test.rtls";

        ImGuiWindowFlags ProjectWinFlags;

        std::string DeletingTlsPath, DeletingTlmPath, DeletingProjectName;
    };

    static AppUIData UIData;

    MapEditorApp::MapEditorApp() : RvlApp(1000, 700, "RVL Map Editor") {}
    MapEditorApp::~MapEditorApp() {}

    void MapEditorApp::Start()
    {
        SetClearColor({0.0f, 0.3f, 0.3f});

        _prjfileText = Utils::GetTextFromFile("./rvmData/projects.rvm");

        if (_prjfileText != "")
        {
            auto prjLines = Utils::SplitStr(_prjfileText, '\n');
            for (int i = 0; i < prjLines.size() - 1; i++)
            {
                _projectLineTokens.push_back(Utils::SplitStr(prjLines[i], ' '));
            }

            UIData.ProjectCreation = false;
            UIData.ProjectOpen = true;
        }
        else
        {
            UIData.ProjectCreation = true;
            UIData.ProjectOpen = false;
        }

        SetDefaults();
    }

    void MapEditorApp::Update()
    {
        DockspaceAndMenu();

        if (UIData.ProjectCreation)
            ProjectWindow();

        if (UIData.ProjectOpen)
            ProjectOpenWindow();
        else
            UIData.ProjectWinFlags &= ~ImGuiWindowFlags_NoInputs;

        if (!UIData.PrjCreateWindowOpen)
        {
            UIData.ProjectCreation = false;
            if (_currentScene)
                dynamic_cast<MapScene*>(_currentScene.get())->InputsEnabled(true);
        }


        if (!UIData.ProjectCreation && !UIData.ProjectOpen && _currentScene)
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
                    UIData.ProjectCreation = true;
                    UIData.PrjCreateWindowOpen = true;
                    SetDefaults();
                }                 
                if (ImGui::MenuItem("Open Project", nullptr, false))
                {
                    UIData.ProjectOpen = true;
                    SetDefaults();
                } 
                if (ImGui::MenuItem("Save", nullptr, false,  _currentScene != nullptr))
                    dynamic_cast<MapScene*>(_currentScene.get())->Save();

                if (ImGui::MenuItem("Exit", nullptr, false)) Close();

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", nullptr, false, _currentScene != nullptr))
                    dynamic_cast<MapScene*>(_currentScene.get())->Undo();

                if (ImGui::MenuItem("Redo", nullptr, false, _currentScene != nullptr))
                    dynamic_cast<MapScene*>(_currentScene.get())->Redo();

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

    void MapEditorApp::ProjectWindow()
    {
        if (_currentScene)
            dynamic_cast<MapScene*>(_currentScene.get())->InputsEnabled(false);

        ImGui::Begin("Project", &UIData.PrjCreateWindowOpen, UIData.ProjectWinFlags);
        ImGui::Text("Create New Project: \n\n");

        ImGui::Text("Project name (max 100 symbols)");
        ImGui::InputText("##prjNameInput", UIData.ProjectName, UIData.MaxNameSize);
        ImGui::Text("\n");

        ImGui::Checkbox("Use existing tileset", &UIData.UseTls);
        ImGui::Checkbox("Use existing tilemap", &UIData.UseTlm);
        ImGui::Text("Texture path or Tileset path");
        ImGui::InputText("##textlmPathInput", UIData.TexName, UIData.MaxFilenameSize);
        ImGui::Text("Tilemap path (can be left empty)");
        ImGui::InputText("##tlmPathInput", UIData.TlmName, UIData.MaxFilenameSize);

        if (ImGui::Button("Create Project", ImVec2(ImGui::GetContentRegionAvail().x, 40)))
        {
            if (!UIData.UseTls && !UIData.UseTlm)
            {
                _currentScene = NewPtr<MapScene>(UIData.ProjectName, UIData.TexName);
                _currentScene->Start();
            }
            else if (UIData.UseTls && !UIData.UseTlm)
            {
                Ref<TileSet> tls = NewRef<TileSet>(UIData.TexName);
                _currentScene = NewPtr<MapScene>(UIData.ProjectName, tls);
                _currentScene->Start();
            }
            else if (UIData.UseTls && UIData.UseTlm)
            {
                Ref<TileSet> tls = NewRef<TileSet>(UIData.TexName);
                Ref<TileMap> tlm = NewRef<TileMap>(tls, UIData.TlmName, 2, 0.01f);
                _currentScene = NewPtr<MapScene>(UIData.ProjectName, tls, tlm);
                _currentScene->Start();
            }
            else
                throw Error("usuck", RVL_CLIENT_ERROR);
                
            UIData.ProjectCreation = false;
        }

        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 100);
        ImGui::Separator();
        ImGui::Text("Or: \n");

        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(232, 108, 108, 255));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(255, 128, 128, 255));
        if (ImGui::Button("Cancel", ImVec2(ImGui::GetContentRegionAvail().x / 2 - 10, 30)))
        {
            UIData.ProjectCreation = false;

            if (_currentScene)            
                dynamic_cast<MapScene*>(_currentScene.get())->InputsEnabled(true);
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::SameLine();

        if (ImGui::Button("Open Existing", ImVec2(ImGui::GetContentRegionAvail().x - 10, 30)))
        {
            UIData.ProjectWinFlags |= ImGuiWindowFlags_NoInputs;
            UIData.ProjectOpen = true;
        }

        ImGui::End();
    }

    void MapEditorApp::ProjectOpenWindow()
    {
        ImGui::Begin("Projects", &UIData.ProjectOpen,  ImGuiWindowFlags_NoDocking);

        auto rofl = Utils::GetTextFromFile("./rvmData/projects.rvm");
        if (_prjfileText != rofl)
        {
            _prjfileText = rofl;
            auto prjLines = Utils::SplitStr(_prjfileText, '\n');

            _projectLineTokens.clear();

            for (int i = 0; i < prjLines.size() - 1; i++)
            {
                _projectLineTokens.push_back(Utils::SplitStr(prjLines[i], ' '));
            }
        }        

        for (int i = 0; i < _projectLineTokens.size(); i++)
        {
            std::string project = std::to_string(i + 1).append(". ").append(_projectLineTokens[i][0]).append(" (").append(_projectLineTokens[i][2]).append(" ").append(_projectLineTokens[i][1]).append(")");
            ImGui::Text(project.c_str());
            ImGui::SameLine();
            ImGui::PushID(i);
            if (ImGui::Button("Open", ImVec2(50, 20)))
            {
                _currentScene = NewPtr<MapScene>(_projectLineTokens[i][0]);
                _currentScene->Start();
                UIData.ProjectOpen = false;
                UIData.ProjectCreation = false;
            }
            ImGui::PopID();

            ImGui::PushID(i + 1);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(232, 94, 94, 255));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(255, 108, 108, 255));
            if (ImGui::Button("Delete", ImVec2(50, 20)))
            {
                UIData.DeletingProjectName = _projectLineTokens[i][0];
                UIData.DeletingTlsPath = _projectLineTokens[i][1];
                UIData.DeletingTlmPath = _projectLineTokens[i][2];
                UIData.DeleteFileWindow = true;
            }
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopID();
        }

        if (ImGui::Button("Create New", ImVec2(100, 25)))
        {
            UIData.ProjectWinFlags &= ~ImGuiWindowFlags_NoInputs;
            UIData.ProjectOpen = false;
            UIData.ProjectCreation = true;
        }

        ImGui::End();

        if (UIData.DeleteFileWindow)
        {
            ImGui::Begin("Delete Project", &UIData.DeleteFileWindow, ImGuiWindowFlags_NoDocking);
                ImGui::Checkbox("Delete tile set", &UIData.DeleteTileSet);
                ImGui::Checkbox("Delete tile map", &UIData.DeleteTileMap);
                if (ImGui::Button("OK", ImVec2(50, 20)))
                {
                    if (_currentScene)
                    {
                        if (dynamic_cast<MapScene*>(_currentScene.get())->GetProjectName() == UIData.DeletingProjectName)
                        {
                            MapScene* scn = dynamic_cast<MapScene*>(_currentScene.release());
                            delete scn;
                        }
                    }

                    if (UIData.DeleteTileSet)
                        std::filesystem::remove(UIData.DeletingTlsPath);

                    if (UIData.DeleteTileMap)
                        std::filesystem::remove(UIData.DeletingTlmPath);

                    int n = 0;
                    for (int i = 0; i < _projectLineTokens.size(); i++)
                    {
                        if (_projectLineTokens[i][0] == UIData.DeletingProjectName)
                        {
                            n = i;
                            break;
                        }
                    }

                    Utils::DeleteLineFromFile("./rvmData/projects.rvm", n);

                    UIData.DeletingTlsPath = "";
                    UIData.DeletingTlmPath = "";
                    UIData.DeletingProjectName = "";

                    UIData.DeleteFileWindow = false;
                }
            ImGui::End();
        }
    }
    
    void MapEditorApp::SetDefaults()
    {
        UIData.ProjectName[0] = '\0';

        UIData.DeleteTileMap = true;
        UIData.DeleteTileSet = false;

        UIData.ProjectWinFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking;
    }
}
