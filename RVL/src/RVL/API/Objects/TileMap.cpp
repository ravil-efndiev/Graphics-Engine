#include "TileMap.hpp"

#include <Core/Core.hpp>
#include <Core/Utils/Files.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

namespace rvl
{
    TileMap::TileMap(const Ref<TileSet>& tileSet, const std::string& tileMapFilePath, int scale, float zIndex)
    {
        _tileSet = tileSet;

        std::string tlmText = utils::GetTextFromFile(tileMapFilePath);
        auto tlmLines = utils::SplitStr(tlmText, '\n');

        for (int i = 0; i < tlmLines.size(); i++)
        {
            auto tokens = utils::SplitStr(tlmLines[i], ' ');

            if (tokens.size() < 3)
                continue;

            try
            {
                _mapTiles.push_back(Sprite::Create({(float)std::stoi(tokens[1]), (float)std::stoi(tokens[2]), zIndex}, scale));

                _mapTiles[i]->LoadTexture(_tileSet->GetTexture());
                _mapTiles[i]->SetSubTexture((*_tileSet)[tokens[0]]);

                _mapTiles[i]->transform->Position = glm::vec3((float)std::stoi(tokens[1]), (float)std::stoi(tokens[2]), zIndex) * glm::vec3(_mapTiles[i]->transform->Scale, 0.f);
            }
            catch (const std::invalid_argument& err)
            {
                throw Error(std::string("invalid data in tile-map file, more info: \n").append(err.what()), RVL_RUNTIME_ERROR);
            }
        }
    }

    TileMap::~TileMap() {}

    void TileMap::Draw()
    {
        for (auto& tile : _mapTiles)
        {
            tile->Draw();
        }
    }
}
