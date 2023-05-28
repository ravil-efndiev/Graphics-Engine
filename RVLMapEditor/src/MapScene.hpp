#ifndef RVL_MAPSCENE_HPP
#define RVL_MAPSCENE_HPP

#include <RVL.hpp>
#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>
#include <API/Objects/Rectangle.hpp>

namespace rvl
{
    struct Action
    {
        enum ActionType
        {
            TilePlace, TileRemove, TileReplace
        };

        ActionType Type;
        glm::ivec2 Position;
        std::string TileName;
        std::string PrevTileName;
    };

    class MapScene : public RvlScene
    {
    public:
        MapScene(const std::string& projName, const std::string& texturePath);
        MapScene(const std::string& projName, const Ref<TileSet>& tls);
        MapScene(const std::string& projName, const Ref<TileSet>& tls, const Ref<TileMap>& tlm);
        MapScene(const std::string& projName);
        ~MapScene();

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
        Ref<TileMap> _tlm;
        Ref<Sprite> _tilePreview;

        float _cameraSpeed = 7.f;
        float _cameraZoom = 10.f;

        int _scale = 1.f;
        float _zIndex = 0.01f;
        bool _projectExists, _tileSetExists, _tileMapExists;
        std::string _tlmPath, _tlsPath, _tlmText, _tlsText;
    
        std::stack<Action> _actions;
        std::stack<Action> _undoActions;

    private:
        void RenderUI();
    };
}

#endif
