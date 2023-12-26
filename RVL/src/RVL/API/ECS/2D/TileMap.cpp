#include "TileMap.hpp"

#include <Core/Core.hpp>
#include <Core/Utils/Files.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

#include <yaml-cpp/yaml.h>

namespace Rvl
{
    TileMap::TileMap(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex)
    {
        Load(tileSet, tileMapFilePath, scale, zIndex);   
    }

    TileMap::TileMap(const Ref<TileSet>& tileSet, int scale, float zIndex)
    {
        Tileset = tileSet;
        ZIndex = zIndex;
        Scale = scale;
        Path = "";
    }

    void TileMap::Load(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex)
    {
        Tileset = tileSet;
        ZIndex = zIndex;
        Scale = scale;

        Path = tileMapFilePath;

        std::ifstream stream (Path);
        std::stringstream strStream;
        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());       
        MapTiles.clear();

        if (data["Tiles"])
        {
            auto tiles = data["Tiles"];
            
            for (auto ytile : tiles)
            {
                Tile tile (
                    ytile.first.as<std::string>(),
                    (*Tileset)[ytile.first.as<std::string>()],
                    glm::ivec2(ytile.second[0].as<int>(), ytile.second[1].as<int>()),
                    Scale, ZIndex
                );

                MapTiles.push_back(tile);

                if (TileSize == glm::vec3(0.f, 0.f, 0.f))
                    TileSize = tile.GetScale();
            }
        }
    }

    TileMap::~TileMap() {}

    void TileMap::AddTile(const std::string& name, const glm::ivec2& mapPos, float zIndex)
    {
        Tile tile (name, (*Tileset)[name], {mapPos.x, mapPos.y}, Scale, ZIndex);
        MapTiles.push_back(tile);

        if (TileSize == glm::vec3(0.f, 0.f, 0.f))
            TileSize = tile.GetScale();

        auto it = std::find_if(MapTiles.begin(), MapTiles.end(), [mapPos](auto& tile)
            {
                return tile.GetMapPosition().x == mapPos.x && tile.GetMapPosition().y == mapPos.y;
            }
        );

        if (it != MapTiles.end())
            *it = tile;
        else
            MapTiles.push_back(tile);
    }

    void TileMap::RemoveTile(const glm::ivec2& mapPos)
    {
        auto it = std::find_if(MapTiles.begin(), MapTiles.end(), [mapPos](auto& tile)
            {
                return tile.GetMapPosition().x == mapPos.x && tile.GetMapPosition().y == mapPos.y;
            }
        );

        if (it != MapTiles.end())
        {
            MapTiles.erase(it);
        } 
    }
    
    glm::ivec2 TileMap::SpimplifyPos(float x, float y)
    {
        return glm::round(glm::vec2(x, y) / glm::vec2(TileSize.x, TileSize.y));
    }
    
    glm::ivec2 TileMap::SpimplifyPos(const glm::vec2& pos)
    {
        return glm::round(pos / glm::vec2(TileSize.x, TileSize.y));
    }
    
    std::string TileMap::GetString() const
    {
        std::string text = "";

        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Tiles" << YAML::Value << YAML::BeginMap;

        for (const Tile& tile : MapTiles)
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
    
    std::string TileMap::GetNameByCoords(const glm::ivec2& pos)
    {
        for (Tile& tile : MapTiles)
        {
            if (tile.GetMapPosition() == pos)
                return tile.GetName();                
        }
        return "";
    }
}
