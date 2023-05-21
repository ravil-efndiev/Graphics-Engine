#ifndef RVL_TILESET_HPP
#define RVL_TILESET_HPP

#include <Core/Core.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

namespace rvl
{
    class TileSet
    {
    public:
        TileSet(const std::string& path);
        ~TileSet();

        const Ref<GLTexture> GetTexture() const;
        
        Ref<SubTexture> operator[](const std::string& name);

    private:
        Ref<GLTexture> _mapTexture;
        std::unordered_map<std::string, Ref<SubTexture>> _tiles;
    };
}

#endif
