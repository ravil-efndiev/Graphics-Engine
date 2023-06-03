#include "MapEditorState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Core/Utils/Files.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rvl
{
    struct SceneUIData
    {
        bool AddTilePopup = false;
        bool MapviewFocused = false;
        bool ShowErrorText = false;

        bool SaveTilesetWindow = false;
        bool SaveTilemapWindow = false;

        bool BigIcons = true;

        const uint64 MaxNameSize = 1000;
        char InputTileName[1000] = "";
        int32 InputCoordX = 0, InputCoordY = 0;
        int32 InputWidth = 0, InputHeight = 0;

        char InputTilesetPath[1000] = "";
        char InputTilemapPath[1000] = "";

        ImGuiWindowFlags GlobalWinFlags = 0;

        ImVec2 MainWindowPosition = {0.f, 0.f};
        ImVec2 SceneWindowPosition = {0.f, 0.f};

        glm::vec3 BackgroundColor = {0.23f, 0.25f, 0.29f};
    };

    static SceneUIData UIData;

    MapEditorState::MapEditorState(const std::string& projName, const std::string& texturePath)
    {
        _projectExists = false;
        _tileSetExists = false;
        _tileMapExists = false;
        _projectName = projName;
        _tls = NewRef<TileSet>(NewRef<GLTexture>(texturePath));
    }

    MapEditorState::MapEditorState(const std::string& projName, const Ref<TileSet>& tls)
    {
        _projectExists = false;
        _tileSetExists = true;
        _tileMapExists = false;
        _projectName = projName;
        _tls = tls;
    }

    MapEditorState::MapEditorState(const std::string& projName, const Ref<TileSet>& tls, const Ref<TileMap>& tlm)
    {
        _projectExists = false;
        _tileSetExists = true;
        _tileMapExists = true;
        _projectName = projName;
        _tls = tls;
        _tlm = tlm;
        _tlsPath = _tls->GetPath();
        _tlmPath = _tlm->GetPath();
    }

    MapEditorState::MapEditorState(const std::string& projName)
    {
        _projectName = projName;
        auto prjfileText = Utils::GetTextFromFile("./rvmData/projects.rvm");
        
        auto prjLines = Utils::SplitStr(prjfileText, '\n');
        for (int i = 0; i < prjLines.size() - 1; i++)
        {
            auto tokens = Utils::SplitStr(prjLines[i], ' ');
            if (tokens[0] == _projectName)
            {
                _projectExists = true;
                _tileSetExists = true;
                _tileMapExists = true;
                _tlsPath = tokens[1];
                _tlmPath = tokens[2];
                _tls = NewRef<TileSet>(_tlsPath);
                _tlm = NewRef<TileMap>(_tls, _tlmPath, _scale, -0.01f);
                break;
            }
        }

        _tlmText = Utils::GetTextFromFile(_tlmPath);
        _tlsText = Utils::GetTextFromFile(_tlsPath);
    }

    MapEditorState::~MapEditorState() {}
    
    void MapEditorState::Start()
    {
        _camera = UserOrthographicCamera::Create({0.f, 0.f}, _cameraZoom);
        AddFrameBuffer(NewRef<GLFrameBuffer>(500, 350));

        if (!_tlm)
            _tlm = NewRef<TileMap>(_tls, _scale, _zIndex);

        _tilePreview = Sprite::Create({0.f, 0.f, 0.02f}, _scale);
        _tilePreview->LoadTexture(_tls->GetTexture());
        _tilePreview->SetSubTexture(0, 0, 0, 0);
    }

    void MapEditorState::Undo()
    {
        if (_actions.top().Type == Action::TilePlace && _actions.size() > 0)
        {
            _undoActions.push({Action::TileRemove, _actions.top().Position, _tlm->GetNameByCoords(_actions.top().Position), ""});
            _tlm->RemoveTile(_actions.top().Position);
            _actions.pop();
        }

        if (_actions.top().Type == Action::TileRemove && _actions.size() > 0)
        {
            _undoActions.push({Action::TilePlace, _actions.top().Position, _actions.top().TileName, ""});
            _tlm->AddTile(_actions.top().TileName, _actions.top().Position, _zIndex);
            _actions.pop();
        }

        if (_actions.top().Type == Action::TileReplace && _actions.size() > 0)
        {
            _undoActions.push({Action::TileReplace, _actions.top().Position, _actions.top().PrevTileName, _actions.top().TileName});
            _tlm->RemoveTile(_actions.top().Position);
            _tlm->AddTile(_actions.top().PrevTileName, _actions.top().Position, _zIndex);
            _actions.pop();
        }
    }

    void MapEditorState::Redo()
    {
        if (_undoActions.top().Type == Action::TilePlace && _undoActions.size() > 0)
        {
            _actions.push({Action::TileRemove, _undoActions.top().Position, _undoActions.top().TileName});
            _tlm->RemoveTile(_undoActions.top().Position);
            _undoActions.pop();
        }

        if (_undoActions.top().Type == Action::TileRemove && _undoActions.size() > 0)
        {
            _actions.push({Action::TilePlace, _undoActions.top().Position, _undoActions.top().TileName});
            _tlm->AddTile(_undoActions.top().TileName, _undoActions.top().Position, _zIndex);
            _undoActions.pop();
        }

        if (_undoActions.top().Type == Action::TileReplace && _undoActions.size() > 0)
        {
            _actions.push({Action::TileReplace, _undoActions.top().Position, _undoActions.top().PrevTileName, _undoActions.top().TileName});
            _tlm->RemoveTile(_undoActions.top().Position);
            _tlm->AddTile(_undoActions.top().PrevTileName, _undoActions.top().Position, _zIndex);
            _undoActions.pop();
        }
    }

    void MapEditorState::Update()
    {
        _camera->SetZoom(_cameraZoom);

        if (Input::IsKeyPressed(Keys::Key_LeftControl))
        {
            if (Input::IsKeyPressedOnce(Keys::Key_S))
                Save();
            
            if (Input::IsKeyPressedOnce(Keys::Key_Z))
                Undo();

            if (Input::IsKeyPressedOnce(Keys::Key_Y))
                Redo();
        }
        else
        {
            if ((UIData.GlobalWinFlags & ImGuiWindowFlags_NoInputs) == 0 && UIData.MapviewFocused)
            {
                _camera->SetPosition({
                    _camera->GetPosition().x + Input::GetAxis(Axis::Horizontal) * _cameraSpeed * Time::DeltaTime(),
                    _camera->GetPosition().y + Input::GetAxis(Axis::Vertical) * _cameraSpeed * Time::DeltaTime()
                });
                    
                if (Input::IsKeyPressed(Keys::Key_LeftAlt))
                {
                    if (Input::IsMouseButtonPressedOnce(Mouse::Left))
                    {
                        glm::vec2 cursor = Input::GetCursorPositionRelative(ImToGlmVec2(UIData.MainWindowPosition), ImToGlmVec2(UIData.SceneWindowPosition));
                        _selectedTile = _tlm->GetNameByCoords(_tlm->SpimplifyPos(cursor));
                    }
                }
                else
                {
                    if (Input::IsMouseButtonPressed(Mouse::Left) && _selectedTile != "")
                    {
                        glm::vec2 cursor = Input::GetCursorPositionRelative(ImToGlmVec2(UIData.MainWindowPosition), ImToGlmVec2(UIData.SceneWindowPosition));
                        if (_tlm->GetNameByCoords(_tlm->SpimplifyPos(cursor)) == "")
                        {
                            if (_tlm->GetNameByCoords(_tlm->SpimplifyPos(cursor)) != _selectedTile)
                            {
                                _actions.push({
                                    Action::TilePlace,
                                    _tlm->SpimplifyPos(cursor), "", ""
                                });
                            }
                            _tlm->AddTile(_selectedTile, _tlm->SpimplifyPos(cursor), 0.01f);
                        }   
                        else
                        {
                            if (_tlm->GetNameByCoords(_tlm->SpimplifyPos(cursor)) != _selectedTile)
                            {
                                _actions.push({
                                    Action::TileReplace,
                                    _tlm->SpimplifyPos(cursor),
                                    _selectedTile,
                                    _tlm->GetNameByCoords(_tlm->SpimplifyPos(cursor))
                                });
                            }
                            _tlm->RemoveTile(_tlm->SpimplifyPos(cursor));
                            _tlm->AddTile(_selectedTile, _tlm->SpimplifyPos(cursor), 0.01f);
                        }
                    }
                    if (Input::IsMouseButtonPressed(Mouse::Right))
                    {
                        glm::vec2 cursor = Input::GetCursorPositionRelative(ImToGlmVec2(UIData.MainWindowPosition), ImToGlmVec2(UIData.SceneWindowPosition));
                        if (_tlm->GetNameByCoords(_tlm->SpimplifyPos(cursor)) != "")
                        {
                            _actions.push({
                                Action::TileRemove,
                                _tlm->SpimplifyPos(cursor),
                                _tlm->GetNameByCoords(_tlm->SpimplifyPos(cursor)), ""
                            });

                            _tlm->RemoveTile(_tlm->SpimplifyPos(cursor));
                        }
                    }
                }

                if (_selectedTile != "")
                {
                    _tilePreview->transform->Position = glm::vec3(glm::vec2(_tlm->SpimplifyPos(Input::GetCursorPositionRelative(ImToGlmVec2(UIData.MainWindowPosition), ImToGlmVec2(UIData.SceneWindowPosition)))) * _tlm->GetTileSize(), _tilePreview->transform->Position.z);
                    _tilePreview->SetSubTexture((*_tls)[_selectedTile]);
                }
            }
        }
    }

    void MapEditorState::Render()
    {
        Renderer::SetClearColor(UIData.BackgroundColor);

        _tlm->Draw();

        if (_selectedTile != "")
          _tilePreview->Draw({1.f, 1.f, 1.f, 0.5f});

        RenderUI();
    }

    void MapEditorState::InputsEnabled(bool flag)
    {
        if (flag)
        {
            UIData.GlobalWinFlags &= ~ImGuiWindowFlags_NoInputs; 
        }
        else if (!flag && (UIData.GlobalWinFlags & ImGuiWindowFlags_NoInputs) == 0)
        {
            UIData.GlobalWinFlags |= ImGuiWindowFlags_NoInputs;
        }
    }

    std::string MapEditorState::GetTilemapPath() const
    {
        return _tlmPath;
    }

    std::string MapEditorState::GetTilesetPath() const
    {
        return _tlsPath;
    }

    std::string MapEditorState::GetProjectName() const
    {
        return _projectName;
    }

    void MapEditorState::Save()
    {
        if (_projectExists)
        {
            _tlm->SaveToFile(_tlmPath.c_str());
            _tls->SaveToFile(_tlsPath.c_str());
        }
        else
        {
            if (!_tileSetExists)
                UIData.SaveTilesetWindow = true;
            if (!_tileMapExists)
                UIData.SaveTilemapWindow = true;
            else
            {
                _tlm->SaveToFile(_tlmPath.c_str());
                _tls->SaveToFile(_tlsPath.c_str());

                std::string projectsData = Utils::GetTextFromFile("./rvmData/projects.rvm");
                projectsData.append(_projectName + " " + _tlsPath + " " + _tlmPath + "\n");
                Utils::SaveTextToFile("./rvmData/projects.rvm", projectsData);
                _projectExists = true;
            }
        }
    }

    void MapEditorState::RenderUI()
    {

        UIData.MainWindowPosition = ImGui::GetMainViewport()->Pos;
        ImGui::Begin("Tile Pallete", nullptr, UIData.GlobalWinFlags);

        if (ImGui::RadioButton("Big Icons", UIData.BigIcons))
        {
            UIData.BigIcons = true;
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Small Icons", !UIData.BigIcons))
        {
            UIData.BigIcons = false;
        }

        static float padding = 16.f;
        static float imageSize = 50.f;
        float cellSize = padding + imageSize;

        ImGui::Spacing();

        if (!UIData.BigIcons)
        {
            ImGui::SliderFloat("Padding", &padding, 0, 64);
            ImGui::SliderFloat("Image size", &imageSize, 20, 128);
        }

        if (!UIData.BigIcons) ImGui::Columns(ImGui::GetContentRegionAvail().x / cellSize, nullptr, false);

        int id = 0;
        for (auto& tile : _tls->GetTiles())
        {
            if (UIData.BigIcons) ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 3);
            ImGui::Text("%s", tile.first.c_str());
            ImGui::PushID(id);
  
            ImVec2 iconSize = UIData.BigIcons ? ImVec2(ImGui::GetContentRegionAvail().x / 1.5f, ImGui::GetContentRegionAvail().x / 1.5f) : ImVec2(imageSize, imageSize);

            if (ImGui::ImageButton((ImTextureID)tile.second->GetTexture()->GetId(), iconSize, ImVec2(tile.second->GetMin().x, tile.second->GetMax().y), ImVec2(tile.second->GetMax().x, tile.second->GetMin().y)))
                _selectedTile = tile.first;
            ImGui::PopID();
            if (UIData.BigIcons) ImGui::Separator();
            if (!UIData.BigIcons) ImGui::NextColumn();
            id++;
        }

        ImGui::Columns(1);

        if (ImGui::Button("+", ImVec2(50, 50)))
        {
            UIData.AddTilePopup = true;
        }
        ImGui::End();

        if (UIData.AddTilePopup)
        {
            InputsEnabled(false);
            ImGui::Begin("Add Tile", &UIData.AddTilePopup, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);
            ImGui::Text("Tile Name");
            ImGui::InputText("##TileNameInput", UIData.InputTileName, UIData.MaxNameSize);
            ImGui::Text("Subtexture X");
            ImGui::InputInt("##CrdXInput", &UIData.InputCoordX);
            ImGui::Text("Subtexture Y");
            ImGui::InputInt("##CrdYInput", &UIData.InputCoordY);
            ImGui::Text("Subtexture Width");
            ImGui::InputInt("##WidthInput", &UIData.InputWidth);
            ImGui::Text("Subtexture Height");
            ImGui::InputInt("##HeightInput", &UIData.InputHeight);
            ImGui::Text("\n");

            if (ImGui::Button("Submit", ImVec2(ImGui::GetContentRegionAvail().x, 30)))
            {
                if (strlen(UIData.InputTileName) <= 0)
                {
                    UIData.ShowErrorText = true;
                }
                else
                {
                    _tls->AddTile(UIData.InputTileName, UIData.InputCoordX, UIData.InputCoordY, UIData.InputWidth, UIData.InputHeight);
                    InputsEnabled(true);
                    UIData.AddTilePopup = false;
                }
            }

            if (UIData.ShowErrorText)
                ImGui::TextColored(ImVec4(0.8f, 0.3f, 0.3f, 1.f), "Tile must have a name");

            ImGui::End();
        }
        else
        {
            InputsEnabled(true);
        }

        ImGui::Begin("Properties", nullptr, UIData.GlobalWinFlags);
        ImGui::InputFloat("Camera Speed##SpeedInput", &_cameraSpeed);
        ImGui::InputFloat("Camera Zoom##ZoomInput", &_cameraZoom);
        ImGui::DragFloat("Camera Speed##SpeedDrag", &_cameraSpeed, 0.4f, 0.f, 100.f);
        ImGui::DragFloat("Camera Zoom##ZoomDrag", &_cameraZoom, 0.4f, 0.f, 100.f);
        ImGui::Separator();
        ImGui::Text("Background Color");
        ImGui::ColorPicker3("##bgcol", glm::value_ptr(UIData.BackgroundColor));
        ImGui::End();

        ImGui::Begin("Map View", nullptr, UIData.GlobalWinFlags);
        bool parentFocused = ImGui::IsWindowFocused();
        ImGui::BeginChild("GameRender");
        
        UIData.MapviewFocused = ImGui::IsWindowFocused() || parentFocused;
        
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (_viewportSize != ImToGlmVec2(viewportSize))
        {
            _viewportSize = {viewportSize.x, viewportSize.y};
            _fbo->RescaleFrameBuffer(viewportSize.x, viewportSize.y);
        }

        UIData.SceneWindowPosition = ImGui::GetWindowPos();

        ImGui::Image(
            (ImTextureID)_fbo->GetColorAttachment(), 
            ImGui::GetContentRegionAvail(), 
            ImVec2(0, 1), 
            ImVec2(1, 0)
        );
        ImGui::EndChild();
        ImGui::End();

        if (UIData.SaveTilesetWindow || UIData.SaveTilemapWindow)
        {
            ImGui::Begin("Save");
            
            if (UIData.SaveTilesetWindow)
            {
                ImGui::Text("New tileset path: ");
                ImGui::InputText("##tlsSave", UIData.InputTilesetPath, UIData.MaxNameSize);
            }
            else
            {
                strncpy(UIData.InputTilesetPath, _tls->GetPath().c_str(), UIData.MaxNameSize);   
            }

            if (UIData.SaveTilemapWindow)
            {
                ImGui::Text("New tilemap path: ");
                ImGui::InputText("##tlmSave", UIData.InputTilemapPath, UIData.MaxNameSize);
            }
            else
            {
                strncpy(UIData.InputTilemapPath, _tlm->GetPath().c_str(), UIData.MaxNameSize);   
            }

            if (ImGui::Button("Save##saveBtn", ImVec2(100, 20)))
            {
                _tlm->SaveToFile(UIData.InputTilemapPath);
                _tls->SaveToFile(UIData.InputTilesetPath);

                std::string projectsData = Utils::GetTextFromFile("./rvmData/projects.rvm");
                projectsData.append(_projectName + " " + UIData.InputTilesetPath + " " + UIData.InputTilemapPath + "\n");
                Utils::SaveTextToFile("./rvmData/projects.rvm", projectsData);

                _tlsPath = UIData.InputTilesetPath;
                _tlmPath = UIData.InputTilemapPath;

                _tileSetExists = true;
                _tileMapExists = true;
                _projectExists = true;
                UIData.SaveTilesetWindow = false;
                UIData.SaveTilemapWindow = false;
            }

            ImGui::End();
        }

        ImGui::Begin("Log Console", nullptr, UIData.GlobalWinFlags);
        ImGui::Button("Clear", {40, 20});
        ImGui::SameLine();
        ImGui::Button("Save", {40, 20});
        ImGui::Separator();
        ImGui::Text("[14.49] Initialized app");
        ImGui::Text("[14.49] Undid action 'Add tile' on (1, 2)");
        ImGui::Text("[14.55] Saved project");
        ImGui::End();
    }
}
