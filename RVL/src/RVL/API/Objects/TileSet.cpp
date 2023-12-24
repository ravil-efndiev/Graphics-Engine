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
                        ytile.second[0].as<float>(), 
                        ytile.second[1].as<float>(), 
                        ytile.second[2].as<float>(), 
                        ytile.second[3].as<float>()
                ));
            }
        }
        /*std::string tlsText = Utils::GetTextFromFile(path);

        auto tlsLines = Utils::SplitStr(tlsText, '\n');

        _mapTexture = NewRef<GLTexture>(tlsLines[0]);

        for (int i = 1; i < tlsLines.size(); i++)
        {
            auto tokens = Utils::SplitStr(tlsLines[i], ' ');

            if (tokens.size() < 5)
                continue;

            try 
            {
                _tiles.emplace(tokens[0], SubTexture::New(_mapTexture,
                    (float)std::stoi(tokens[1]), 
                    (float)std::stoi(tokens[2]),
                    (float)std::stoi(tokens[3]), 
                    (float)std::stoi(tokens[4])
                ));
            }
            catch (const std::invalid_argument& err)
            {
                throw Error(std::string("invalid data in tile-set file, more info: \n").append(err.what()), RVL_RUNTIME_ERROR);
            }
        }*/
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

    void TileSet::AddTile(const std::string& name, float texX, float texY, float texWidth, float texHeight)
    {
        if (_tiles.find(name) != _tiles.end())
            throw Error("tile names in tileSet must be unique", RVL_RUNTIME_ERROR);
        _tiles.emplace(name, SubTexture::New(_mapTexture, texX, texY, texWidth, texHeight));
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
                (int)tile.second->GetX(),
                (int)tile.second->GetY(),
                (int)tile.second->GetWidth(),
                (int)tile.second->GetHeight()
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
