#pragma once

#include "API/Objects/TileSet.hpp"
#include "API/ECS/General/Transform.hpp"
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
            _scale = glm::vec3(ratio * scale, scale, 0.f);

            _relativePos = glm::vec3(glm::vec2(_mapPosition) * glm::vec2(_scale), zIndex);
        }

        glm::ivec2 GetMapPosition() const { return _mapPosition; }
        glm::vec3 GetRelativePosition() const { return _relativePos; }
        glm::vec3& GetWorldPosition() { return _worldPos; }
        glm::vec3 GetScale() const { return _scale; }

        Ref<SubTexture> GetSubtexture() const { return _subtexture; }
        std::string GetName() const { return _name; }

    private:
        Ref<SubTexture> _subtexture;
        std::string _name;

        glm::ivec2 _mapPosition;
        glm::vec3 _relativePos;
        glm::vec3 _worldPos;
        glm::vec3 _scale;
    };

    struct TileMap
    {
        TileMap(const TileMap&) = default;
        TileMap(const Ref<TileSet>& tileSet, const std::string& TileMapFilePath, int scale, float zIndex);
        TileMap(const Ref<TileSet>& tileSet, int scale, float zIndex);
        ~TileMap();

        void AddTile(const std::string& name, const glm::ivec2& mapPos, float zIndex);
        void RemoveTile(const glm::ivec2& mapPos);

        glm::ivec2 SpimplifyPos(float x, float y);
        glm::ivec2 SpimplifyPos(const glm::vec2& pos);

        std::string GetString() const;
        void SaveToFile(const char* path);
        std::string GetNameByCoords(const glm::ivec2& pos);

        float ZIndex;
        int Scale;

        Ref<TileSet> Tileset;
        std::vector<Tile> MapTiles;

        std::string Path;
        glm::vec3 TileSize { 0.f, 0.f, 0.f };
    };
}

