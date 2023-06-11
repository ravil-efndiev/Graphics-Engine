#ifndef RVL_TILEMAP_COMPONENT_HPP
#define RVL_TILEMAP_COMPONENT_HPP

#include <API/Objects/TileSet.hpp>
#include <Rendering/Renderer/Transform.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

namespace Rvl
{
    class Tile
    {
    public:
        Tile(const std::string& name, const Ref<SubTexture>& subtexture, const glm::ivec2& pos, float scale, float zIndex)
            : _subtexture(subtexture), _mapPosition(pos), _name(name) 
        {
            float ratio = _subtexture->GetWidth() / _subtexture->GetHeight();
            _transform.Scale = glm::vec2(ratio * scale, scale);

            _transform.Position = glm::vec3(glm::vec2(_mapPosition) * _transform.Scale, zIndex);
        }

        glm::ivec2 GetMapPosition() const { return _mapPosition; }
        glm::vec3 GetRealPosition() const { return _transform.Position; }

        Ref<SubTexture> GetSubtexture() const { return _subtexture; }
        Transform GetTransform() const { return _transform; }
        std::string GetName() const { return _name; }

    private:
        Ref<SubTexture> _subtexture;
        glm::ivec2 _mapPosition;
        std::string _name;
        Transform _transform;
    };

    class TileMapComponent
    {
    public:
        TileMapComponent() = default;
        TileMapComponent(const TileMapComponent&) = default;
        TileMapComponent(const Ref<TileSet>& tileSet, const std::string& TileMapFilePath, int scale, float zIndex);
        TileMapComponent(const Ref<TileSet>& tileSet, int scale, float zIndex);
        ~TileMapComponent();

        void AddTile(const std::string& name, const glm::ivec2& mapPos, float zIndex);
        void RemoveTile(const glm::ivec2& mapPos);

        glm::ivec2 SpimplifyPos(float x, float y);
        glm::ivec2 SpimplifyPos(const glm::vec2& pos);

        std::string GetString() const;
        void SaveToFile(const char* path);

        std::string GetPath() const;
        glm::vec2 GetTileSize() const;

        std::string GetNameByCoords(const glm::ivec2& pos);

        const std::vector<Tile>& GetTiles() const;

    private:
        Ref<TileSet> _tileSet;
        std::vector<Tile> _mapTiles;
        float _zIndex;
        int _scale;

        glm::vec3 _anyTileSize { 0.f, 0.f, 0.f };

        std::string _path;
    };
}

#endif 
