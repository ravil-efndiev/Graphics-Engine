#ifndef RVL_TILEMAP_HPP
#define RVL_TILEMAP_HPP

#include "Sprite.hpp"
#include "Renderable.hpp"
#include "TileSet.hpp"

namespace Rvl
{
    class Tile
    {
    public:
        Tile(const std::string& name, const Ref<Sprite>& sprite, const glm::ivec2 pos)
            : _sprite(sprite), _mapPosition(pos), _name(name) {}

        glm::ivec2 GetMapPosition() const { return _mapPosition; }
        glm::vec3 GetRealPosition() const { return _sprite->transform->Position; }

        Ref<Sprite> GetSprite() { return _sprite; }
        std::string GetName() const { return _name; }

    private:
        Ref<Sprite> _sprite;
        glm::ivec2 _mapPosition;
        std::string _name;
    };

    class TileMap : public Entity, public Renderable
    {
    public:
        TileMap(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex);
        TileMap(const Ref<TileSet>& tileSet, int scale, float zIndex);
        ~TileMap();

        void Draw() override;

        void AddTile(const std::string& name, const glm::ivec2& mapPos, float zIndex);
        void RemoveTile(const glm::ivec2& mapPos);

        glm::ivec2 SpimplifyPos(float x, float y);
        glm::ivec2 SpimplifyPos(const glm::vec2& pos);

        std::string GetString() const;
        void SaveToFile(const char* path);

        std::string GetPath() const;
        glm::vec2 GetTileSize() const;

        std::string GetNameByCoords(const glm::ivec2& pos);

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
