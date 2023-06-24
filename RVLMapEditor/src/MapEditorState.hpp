#pragma once

#include <RVL.hpp>
#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>
#include "ConfigParser.hpp"

namespace Rvl
{
    struct Action
    {
        enum ActionType { TilePlace, TileRemove, TileReplace };

        ActionType Type;
        glm::ivec2 Position;
        std::string TileName;
        std::string PrevTileName;
    };

    class MapEditorState : public State
    {
    public:
        MapEditorState(const std::string& projName, const std::string& texturePath);
        MapEditorState(const std::string& projName, const Ref<TileSet>& tls);
        MapEditorState(const std::string& projName, const Ref<TileSet>& tls, const std::string& tlmPath, float scale, float zIndex);
        MapEditorState(const std::string& projName);
        ~MapEditorState();

        void Start() override;
        void Update() override;
        void Render() override;

        void InputsEnabled(bool flag);

        std::string GetTilemapPath() const;
        std::string GetTilesetPath() const;

        std::string GetProjectName() const;

        void Save();
        void Undo();
        void Redo();

    private:
        glm::vec2 _viewportSize {0.f}; 
        std::string _projectName;
        std::string _selectedTile = "";

        Ref<TileSet> _tls;
        Entity _tlmEntity;
        Entity _tilePreviewEntity;

        TileMapComponent* _tlm;
        SpriteComponent* _tilePreview;

        float _cameraSpeed = 7.f;
        float _cameraZoom = 10.f;

        int _scale = 1.f;
        float _zIndex = 0.01f;
        bool _projectExists, _tileSetExists, _tileMapExists;
        std::string _tlmPath, _tlsPath, _tlmText, _tlsText;
    
        std::stack<Action> _actions;
        std::stack<Action> _undoActions;

        ConfigParser _parser { "settings/projects.rconfig" };

        Ref<UserOrthographicCamera> _oCamera;

    private:
        void RenderUI();
    };
}
