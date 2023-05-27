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

        _path = tileMapFilePath;

        std::string tlmText = Utils::GetTextFromFile(tileMapFilePath);
        auto tlmLines = Utils::SplitStr(tlmText, '\n');

        for (int i = 0; i < tlmLines.size(); i++)
        {
            auto tokens = Utils::SplitStr(tlmLines[i], ' ');

            if (tokens.size() < 3)
                continue;

            try
            {
                auto tileSprite = Sprite::Create(glm::vec3(0.f, 0.f, zIndex), _scale);

                tileSprite->LoadTexture(_tileSet->GetTexture());
                tileSprite->SetSubTexture((*_tileSet)[tokens[0]]);

                _anyTileSize = glm::vec3(tileSprite->transform->Scale, 0.f);

                tileSprite->transform->Position = glm::vec3((float)std::stoi(tokens[1]), (float)std::stoi(tokens[2]), zIndex) * _anyTileSize;
                _mapTiles.push_back(Tile(tokens[0], tileSprite, {std::stoi(tokens[1]), std::stoi(tokens[2])}));

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
        _path = "";
    }

    TileMap::~TileMap() {}

    void TileMap::Draw()
    {
        for (auto& tile : _mapTiles)
        {
            tile.GetSprite()->Draw();
        }
    }
    
    void TileMap::AddTile(const std::string& name, const glm::ivec2& mapPos, float zIndex)
    {
        auto tileSprite = Sprite::Create(glm::vec3(0.f, 0.f, zIndex), _scale);
        tileSprite->LoadTexture(_tileSet->GetTexture());
        tileSprite->SetSubTexture((*_tileSet)[name]);

        if (_anyTileSize == glm::vec3(0.f, 0.f, 0.f))
            _anyTileSize = glm::vec3(tileSprite->transform->Scale, 0.f);

        tileSprite->transform->Position = glm::vec3(mapPos.x, mapPos.y, zIndex) * _anyTileSize; 

        Tile tile (name, tileSprite, {mapPos.x, mapPos.y});

        auto it = std::find_if(_mapTiles.begin(), _mapTiles.end(), [mapPos](auto& tile)
            {
                return tile.GetMapPosition().x == mapPos.x && tile.GetMapPosition().y == mapPos.y;
            }
        );

        if (it != _mapTiles.end())
            *it = tile;
        else
            _mapTiles.push_back(tile);
    }

    void TileMap::RemoveTile(const glm::ivec2& mapPos)
    {
        auto it = std::find_if(_mapTiles.begin(), _mapTiles.end(), [mapPos](auto& tile)
            {
                return tile.GetMapPosition().x == mapPos.x && tile.GetMapPosition().y == mapPos.y;
            }
        );

        if (it != _mapTiles.end())
        {
            _mapTiles.erase(it);
        } 
    }
    
    glm::ivec2 TileMap::SpimplifyPos(float x, float y)
    {
        return glm::round(glm::vec2(x, y) / glm::vec2(_anyTileSize.x, _anyTileSize.y));
    }
    
    glm::ivec2 TileMap::SpimplifyPos(const glm::vec2& pos)
    {
        return glm::round(pos / glm::vec2(_anyTileSize.x, _anyTileSize.y));
    }
    
    std::string TileMap::GetString() const
    {
        std::string text = "";

        for (const Tile& tile : _mapTiles)
        {
            text.append(tile.GetName())
                .append(" ")
                .append(std::to_string(tile.GetMapPosition().x))
                .append(" ")
                .append(std::to_string(tile.GetMapPosition().y))
                .append("\n");
        }   

        return text;
    }

    void TileMap::SaveToFile(const char* path)
    {
        Utils::SaveTextToFile(path, GetString());
    }
    
    std::string TileMap::GetPath() const
    {
        return _path;
    }
    
    glm::vec2 TileMap::GetTileSize() const
    {
        return _anyTileSize;
    }
    
    std::string TileMap::GetNameByCoords(const glm::ivec2& pos)
    {
        for (Tile& tile : _mapTiles)
        {
            if (tile.GetMapPosition() == pos)
                return tile.GetName();                
        }
        return "";
    }
}
