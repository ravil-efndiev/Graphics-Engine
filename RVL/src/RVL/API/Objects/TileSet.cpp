#include "TileSet.hpp"

#include <Core/Utils/Files.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>

namespace rvl
{
    TileSet::TileSet(const std::string& path)
    {
        std::string tlsText = utils::GetTextFromFile(path);

        auto tlsLines = utils::SplitStr(tlsText, '\n');

        _mapTexture = NewRef<GLTexture>(tlsLines[0]);

        for (int i = 1; i < tlsLines.size(); i++)
        {
            auto tokens = utils::SplitStr(tlsLines[i], ' ');

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
}
