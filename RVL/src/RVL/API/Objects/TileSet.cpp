#include "TileSet.hpp"

#include <Core/Utils/Files.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>

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
        std::string tlsText = Utils::GetTextFromFile(path);
        _path = path;

        auto tlsLines = Utils::SplitStr(tlsText, '\n');

        _mapTexture = NewRef<GLTexture>(tlsLines[0]);

        for (int i = 1; i < tlsLines.size(); i++)
        {
            auto tokens = Utils::SplitStr(tlsLines[i], ' ');

            if (tokens.size() < 5)
                continue;

            try 
            {
                _tiles.emplace(tokens[0], SubTexture::Create(_mapTexture,
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

    void TileSet::AddTile(const std::string& name, float texX, float texY, float texWidth, float texHeight)
    {
        if (_tiles.find(name) != _tiles.end())
            throw Error("tile names in tileSet must be unique", RVL_RUNTIME_ERROR);
        _tiles.emplace(name, SubTexture::Create(_mapTexture, texX, texY, texWidth, texHeight));
    }

    std::string TileSet::GetString() const
    {
        std::string text = _mapTexture->GetPath().append("\n");

        for (auto& tile : _tiles)
        {
            text = text.append(tile.first)
                .append(" ")
                .append(std::to_string((int)tile.second->GetX()))
                .append(" ")
                .append(std::to_string((int)tile.second->GetY()))
                .append(" ")
                .append(std::to_string((int)tile.second->GetWidth()))
                .append(" ")
                .append(std::to_string((int)tile.second->GetHeight()))
                .append("\n");
        }

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
