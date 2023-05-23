#include "TileMap.hpp"

#include <Core/Core.hpp>
#include <Core/Utils/Files.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

namespace rvl
{
    TileMap::TileMap(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex)
    {
        _tileSet = tileSet;
        _zIndex = zIndex;
        _scale = scale;

        std::string tlmText = utils::GetTextFromFile(tileMapFilePath);
        auto tlmLines = utils::SplitStr(tlmText, '\n');

        for (int i = 0; i < tlmLines.size(); i++)
        {
            auto tokens = utils::SplitStr(tlmLines[i], ' ');

            if (tokens.size() < 3)
                continue;

            try
            {
                auto tileSprite = Sprite::Create(glm::vec3(0.f, 0.f, zIndex), _scale);

                tileSprite->LoadTexture(_tileSet->GetTexture());
                tileSprite->SetSubTexture((*_tileSet)[tokens[0]]);

                _anyTileSize = glm::vec3(tileSprite->transform->Scale, 0.f);

                tileSprite->transform->Position = glm::vec3((float)std::stoi(tokens[1]), (float)std::stoi(tokens[2]), zIndex) * _anyTileSize;
                _mapTiles.push_back(Tile(tileSprite, {std::stoi(tokens[1]), std::stoi(tokens[2])}));

            }
            catch (const std::invalid_argument& err)
            {
                throw Error(std::string("invalid data in tile-map file, more info: \n").append(err.what()), RVL_RUNTIME_ERROR);
            }
        }
    }

    TileMap::TileMap(const Ref<TileSet>& tileSet, int scale, float zIndex)
    {
        _tileSet = tileSet;
        _zIndex = zIndex;
        _scale = scale;
    }

    TileMap::~TileMap() {}

    void TileMap::Draw()
    {
        for (auto& tile : _mapTiles)
        {
            tile.GetSprite()->Draw();
        }
    }
    
    void TileMap::AddTile(const std::string& name, int x, int y, int zIndex)
    {
        auto tileSprite = Sprite::Create(glm::vec3(0.f, 0.f, zIndex), _scale);
        tileSprite->LoadTexture(_tileSet->GetTexture());
        tileSprite->SetSubTexture((*_tileSet)[name]);

        if (_anyTileSize == glm::vec3(0.f, 0.f, 0.f))
            _anyTileSize = glm::vec3(tileSprite->transform->Scale, 0.f);

        tileSprite->transform->Position = glm::vec3(x, y, zIndex) * _anyTileSize; 

        Tile tile = {tileSprite, {x, y}};

        auto it = std::find_if(_mapTiles.begin(), _mapTiles.end(), [x, y](auto& tile)
            {
                return tile.GetMapPosition().x == x && tile.GetMapPosition().y == y;
            }
        );

        if (it != _mapTiles.end())
            *it = tile;
        else
            _mapTiles.push_back(tile);
    }
    
    glm::ivec2 TileMap::SpimplifyPos(float x, float y)
    {
        return glm::round(glm::vec2(x, y) / glm::vec2(_anyTileSize.x, _anyTileSize.y));
    }
    
    glm::ivec2 TileMap::SpimplifyPos(const glm::vec2& pos)
    {
        return glm::round(pos / glm::vec2(_anyTileSize.x, _anyTileSize.y));
    }
}
