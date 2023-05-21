#ifndef RVL_TILEMAP_HPP
#define RVL_TILEMAP_HPP

#include "Sprite.hpp"
#include "Renderable.hpp"
#include "TileSet.hpp"

namespace rvl
{
    class TileMap : public Entity, public IRenderable
    {
    public:
        TileMap(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex);
        ~TileMap();

        void Draw() override;

    private:
        Ref<TileSet> _tileSet;
        std::vector<Ref<Sprite>> _mapTiles;
    };
}

#endif 
