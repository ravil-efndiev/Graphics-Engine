#include "TileMapComponent.hpp"

#include <Core/Core.hpp>
#include <Core/Utils/Files.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

namespace Rvl
{
    TileMapComponent::TileMapComponent(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex)
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
                Tile tile (tokens[0], (*_tileSet)[tokens[0]], {std::stoi(tokens[1]), std::stoi(tokens[2])}, _scale, _zIndex);
                _mapTiles.push_back(tile);

                if (_anyTileSize == glm::vec3(0.f, 0.f, 0.f))
                    _anyTileSize = tile.GetTransform().Scale;
            }
            catch (const std::invalid_argument& err)
            {
                throw Error(std::string("invalid data in tile-map file, more info: \n").append(err.what()), RVL_RUNTIME_ERROR);
            }
        }
    }

    TileMapComponent::TileMapComponent(const Ref<TileSet>& tileSet, int scale, float zIndex)
    {
        _tileSet = tileSet;
        _zIndex = zIndex;
        _scale = scale;
        _path = "";
    }

    TileMapComponent::~TileMapComponent() {}

    void TileMapComponent::AddTile(const std::string& name, const glm::ivec2& mapPos, float zIndex)
    {
        Tile tile (name, (*_tileSet)[name], {mapPos.x, mapPos.y}, _scale, _zIndex);
        _mapTiles.push_back(tile);

        if (_anyTileSize == glm::vec3(0.f, 0.f, 0.f))
            _anyTileSize = tile.GetTransform().Scale;

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

    void TileMapComponent::RemoveTile(const glm::ivec2& mapPos)
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
    
    glm::ivec2 TileMapComponent::SpimplifyPos(float x, float y)
    {
        return glm::round(glm::vec2(x, y) / glm::vec2(_anyTileSize.x, _anyTileSize.y));
    }
    
    glm::ivec2 TileMapComponent::SpimplifyPos(const glm::vec2& pos)
    {
        return glm::round(pos / glm::vec2(_anyTileSize.x, _anyTileSize.y));
    }
    
    std::string TileMapComponent::GetString() const
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

    void TileMapComponent::SaveToFile(const char* path)
    {
        Utils::SaveTextToFile(path, GetString());
    }
    
    std::string TileMapComponent::GetPath() const
    {
        return _path;
    }
    
    glm::vec2 TileMapComponent::GetTileSize() const
    {
        return _anyTileSize;
    }
    
    std::string TileMapComponent::GetNameByCoords(const glm::ivec2& pos)
    {
        for (Tile& tile : _mapTiles)
        {
            if (tile.GetMapPosition() == pos)
                return tile.GetName();                
        }
        return "";
    }
    
    const std::vector<Tile>& TileMapComponent::GetTiles() const
    {
        return _mapTiles;
    }
}
