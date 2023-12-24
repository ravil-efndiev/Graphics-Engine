#include "TileMap.hpp"

#include <Core/Core.hpp>
#include <Core/Utils/Files.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

#include <yaml-cpp/yaml.h>

namespace Rvl
{
    TileMap::TileMap(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex)
    {
        _tileSet = tileSet;
        _zIndex = zIndex;
        _scale = scale;

        _path = tileMapFilePath;

        std::ifstream stream (_path);
        std::stringstream strStream;
        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());       

        if (data["Tiles"])
        {
            auto tiles = data["Tiles"];
            
            for (auto ytile : tiles)
            {
                Tile tile (
                    ytile.first.as<std::string>(),
                    (*_tileSet)[ytile.first.as<std::string>()],
                    glm::ivec2(ytile.second[0].as<int>(), ytile.second[1].as<int>()),
                    _scale, _zIndex
                );

                _mapTiles.push_back(tile);

                if (_anyTileSize == glm::vec3(0.f, 0.f, 0.f))
                    _anyTileSize = tile.GetTransform().Scale;
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

    void TileMap::AddTile(const std::string& name, const glm::ivec2& mapPos, float zIndex)
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

        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Tiles" << YAML::Value << YAML::BeginMap;

        for (const Tile& tile : _mapTiles)
        {
            emitter << YAML::Key << tile.GetName() << YAML::Value << tile.GetMapPosition();
        }   

        emitter << YAML::EndMap << YAML::EndMap;

        text = emitter.c_str();
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
    
    const std::vector<Tile>& TileMap::GetTiles() const
    {
        return _mapTiles;
    }

    Ref<TileSet> TileMap::GetTileSet() const
    {
        return _tileSet;
    }

}
