#ifndef RVL_TILEMAP_HPP
#define RVL_TILEMAP_HPP

#include "Sprite.hpp"
#include "Renderable.hpp"
#include "TileSet.hpp"

namespace rvl
{
    struct Tile
    {
    public:
        Tile(const Ref<Sprite>& sprite, const glm::ivec2 pos)
            : _sprite(sprite), _mapPosition(pos) {}

        glm::ivec2 GetMapPosition() const { return _mapPosition; }
        glm::vec3 GetRealPosition() const { return _sprite->transform->Position; }

        Ref<Sprite> GetSprite() { return _sprite; }

    private:
        Ref<Sprite> _sprite;
        glm::ivec2 _mapPosition;
    };

    class TileMap : public Entity, public IRenderable
    {
    public:
        TileMap(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex);
        TileMap(const Ref<TileSet>& tileSet, int scale, float zIndex);
        ~TileMap();

        void Draw() override;

        void AddTile(const std::string& name, int x, int y, int zIndex);
        glm::ivec2 SpimplifyPos(float x, float y);
        glm::ivec2 SpimplifyPos(const glm::vec2& pos);

    private:
        Ref<TileSet> _tileSet;
        std::vector<Tile> _mapTiles;
        int _zIndex, _scale;

        glm::vec3 _anyTileSize { 0.f, 0.f, 0.f };
    };
}

#endif 
