#include "MapScene.hpp"

#include <Rendering/Renderer/Renderer.hpp>

namespace rvl
{
    struct SceneUIData
    {
        bool AddTilePopup = false;

        const uint64 MaxNameSize = 100;
        char InputTileName[100] = "";
        int32 InputCoordX = 0, InputCoordY = 0;
        int32 InputWidth = 0, InputHeight = 0;

        ImGuiWindowFlags GlobalWinFlags = 0;

        ImVec2 MainWindowPosition = {0.f, 0.f};
        ImVec2 SceneWindowPosition = {0.f, 0.f};
    };

    static SceneUIData SceneUiData;

    MapScene::MapScene(const std::string& texturePath)
    {
        _tls = NewRef<TileSet>(NewRef<GLTexture>(texturePath));
    }

    MapScene::MapScene(const Ref<TileSet>& tls)
    {
        _tls = tls;
    }

    MapScene::~MapScene() {}
    
    void MapScene::Start()
    {
        _camera = UserOrthographicCamera::Create({0.f, 0.f}, _cameraZoom);
        AddFrameBuffer(NewRef<GLFrameBuffer>(500, 350));

        _tlm = NewRef<TileMap>(_tls, _scale, _zIndex);
    }

    void MapScene::Update()
    {
        if ((SceneUiData.GlobalWinFlags & ImGuiWindowFlags_NoInputs) == 0)
        {
            _camera->SetZoom(_cameraZoom);
            _camera->SetPosition({
                _camera->GetPosition().x + Input::GetAxis(Axis::Horizontal) * _cameraSpeed * Time::DeltaTime(),
                _camera->GetPosition().y + Input::GetAxis(Axis::Vertical) * _cameraSpeed * Time::DeltaTime()
            });
                
            if (Input::IsKeyPressedOnce(Keys::Key_Space) && _selectedTile != "")
            {
                glm::vec2 cursor = Input::GetCursorPositionRelative(ImToGlmVec2(SceneUiData.MainWindowPosition), ImToGlmVec2(SceneUiData.SceneWindowPosition));
                _tlm->AddTile(_selectedTile, _tlm->SpimplifyPos(cursor).x, _tlm->SpimplifyPos(cursor).y, 0.01f);
            }
        }
    }

    void MapScene::Render()
    {
        _tlm->Draw();

        RenderUI();
    }

    void MapScene::InputsEnabled(bool flag)
    {
        if (flag)
        {
            SceneUiData.GlobalWinFlags &= ~ImGuiWindowFlags_NoInputs; 
        }
        else if (!flag && (SceneUiData.GlobalWinFlags & ImGuiWindowFlags_NoInputs) == 0)
        {
            SceneUiData.GlobalWinFlags |= ImGuiWindowFlags_NoInputs;
        }
    }
    
    void MapScene::RenderUI()
    {
        SceneUiData.MainWindowPosition = ImGui::GetMainViewport()->Pos;
        ImGui::Begin("Tile Pallete", nullptr, SceneUiData.GlobalWinFlags);

        int id = 0;
        for (auto& tile : _tls->GetTiles())
        {
            ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 3);
            ImGui::Text(tile.first.c_str());
            ImGui::PushID(id);
            if (ImGui::ImageButton((ImTextureID)tile.second->GetTexture()->GetId(), {150, 150}, ImVec2(tile.second->GetMin().x, tile.second->GetMax().y), ImVec2(tile.second->GetMax().x, tile.second->GetMin().y)))
                _selectedTile = tile.first;
            ImGui::PopID();
            ImGui::Separator();
            id++;
        }

        if (ImGui::Button("+", ImVec2(50, 50)))
        {
            SceneUiData.AddTilePopup = true;
        }
        ImGui::End();

        if (SceneUiData.AddTilePopup)
        {
            InputsEnabled(false);
            ImGui::Begin("Add Tile", &SceneUiData.AddTilePopup, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);
              ImGui::Text("Tile Name");
              ImGui::InputText("##TileNameInput", SceneUiData.InputTileName, SceneUiData.MaxNameSize);
              ImGui::Text("Subtexture X");
              ImGui::InputInt("##CrdXInput", &SceneUiData.InputCoordX);
              ImGui::Text("Subtexture Y");
              ImGui::InputInt("##CrdYInput", &SceneUiData.InputCoordY);
              ImGui::Text("Subtexture Width");
              ImGui::InputInt("##WidthInput", &SceneUiData.InputWidth);
              ImGui::Text("Subtexture Height");
              ImGui::InputInt("##HeightInput", &SceneUiData.InputHeight);
              ImGui::Text("\n");

            if (ImGui::Button("Submit", ImVec2(ImGui::GetContentRegionAvail().x, 30)))
            {
                _tls->AddTile(SceneUiData.InputTileName, SceneUiData.InputCoordX, SceneUiData.InputCoordY, SceneUiData.InputWidth, SceneUiData.InputHeight);
                InputsEnabled(true);
                SceneUiData.AddTilePopup = false;
            }

            ImGui::End();
        }
        else
        {
            InputsEnabled(true);
        }

        ImGui::Begin("Tools", nullptr, SceneUiData.GlobalWinFlags);
          ImGui::Text("tool name");
        ImGui::End();

        ImGui::Begin("Properties", nullptr, SceneUiData.GlobalWinFlags);
          ImGui::InputFloat("Camera Speed##SpeedInput", &_cameraSpeed);
          ImGui::InputFloat("Camera Zoom##ZoomInput", &_cameraZoom);
          ImGui::DragFloat("Camera Speed##SpeedDrag", &_cameraSpeed, 0.4f, 0.f, 100.f);
          ImGui::DragFloat("Camera Zoom##ZoomDrag", &_cameraZoom, 0.4f, 0.f, 100.f);
        ImGui::End();

        ImGui::Begin("Console", nullptr, SceneUiData.GlobalWinFlags);
          ImGui::Text("LOG => initialized app");
          ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.3f, 1.0f), "WARINIG => Unused parameter 'bruh_u_suck'");
          ImGui::Text("LOG => Starting ...");
          ImGui::Text("LOG => Success: 1 warinig, 0 errors generated");
        ImGui::End();
 
        ImGui::Begin("Map View", nullptr, SceneUiData.GlobalWinFlags);
          ImGui::BeginChild("GameRender");
            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            if (_viewportSize != ImToGlmVec2(viewportSize))
            {
                _viewportSize = {viewportSize.x, viewportSize.y};
                _fbo->RescaleFrameBuffer(viewportSize.x, viewportSize.y);
            }

            SceneUiData.SceneWindowPosition = ImGui::GetWindowPos();

            ImGui::Image(
                (ImTextureID)_fbo->GetColorAttachment(), 
                ImGui::GetContentRegionAvail(), 
                ImVec2(0, 1), 
                ImVec2(1, 0)
            );
          ImGui::EndChild();
        ImGui::End();
    }
}
