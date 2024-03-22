#include "TileSet.hpp"

#include <Core/Utils/Files.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>

#include <yaml-cpp/yaml.h>

namespace Rvl
{
    TileSet::TileSet(const Ref<GLTexture>& mainTexture)
    {
        _path = "";
        _mapTexture = mainTexture;
        _tiles = {};
    }

    TileSet::TileSet(const std::string& path)
    {
        _path = path;

        std::ifstream stream (_path);
        std::stringstream strStream;
        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());       

        _mapTexture = NewRef<GLTexture>(data["Texture"].as<std::string>());

        if (data["Tiles"])
        {
            auto tiles = data["Tiles"];
            
            for (auto ytile : tiles)
            {
                _tiles.emplace(ytile.first.as<std::string>(),
                    SubTexture::New(_mapTexture,
                        ytile.second[0].as<f32>(), 
                        ytile.second[1].as<f32>(), 
                        ytile.second[2].as<f32>(), 
                        ytile.second[3].as<f32>()
                ));
            }
        }
    }

    TileSet::~TileSet() {}

    const Ref<GLTexture> TileSet::GetTexture() const
    {
        return _mapTexture;
    }

    Ref<SubTexture> TileSet::operator[](const std::string& name)
    {
        return _tiles[name];
    }

    const std::unordered_map<std::string, Ref<SubTexture>>& TileSet::GetTiles() const
    {
        return _tiles;
    }

    void TileSet::AddTile(const std::string& name, f32 texX, f32 texY, f32 texWidth, f32 texHeight)
    {
        if (_tiles.find(name) != _tiles.end())
            throw Error("tile names in tileSet must be unique", RVL_RUNTIME_ERROR);
        _tiles.emplace(name, SubTexture::New(_mapTexture, texX, texY, texWidth, texHeight));
    }

    void TileSet::RemoveTile(const std::string& name)
    {
        _tiles.erase(name);   
    }

    void TileSet::Clear()
    {
        for (auto tile : _tiles)
            RemoveTile(tile.first);
    }

    std::string TileSet::GetString() const
    {
        std::string text = "";

        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Texture" << YAML::Value << _mapTexture->GetPath();
        emitter << YAML::Key << "Tiles" << YAML::Value << YAML::BeginMap;

        for (const auto& tile : _tiles)
        {
            emitter << YAML::Key << tile.first << YAML::Value << glm::vec4(
                (i32)tile.second->GetX(),
                (i32)tile.second->GetY(),
                (i32)tile.second->GetWidth(),
                (i32)tile.second->GetHeight()
            );
        }   

        emitter << YAML::EndMap << YAML::EndMap;

        text = emitter.c_str();
        return text;
    }

    void TileSet::SaveToFile(const char* path)
    {
        Utils::SaveTextToFile(path, GetString());
    }
    
    std::string TileSet::GetPath() const
    {
        return _path;
    }
}
