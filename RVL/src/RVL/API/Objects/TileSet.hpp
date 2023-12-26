#pragma once

#include <Core/Core.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

namespace Rvl
{
    class TileSet
    {
    public:
        TileSet(const Ref<GLTexture>& mainTexture);
        TileSet(const std::string& path);
        ~TileSet();

        const Ref<GLTexture> GetTexture() const;
        
        Ref<SubTexture> operator[](const std::string& name);
        const std::unordered_map<std::string, Ref<SubTexture>>& GetTiles() const;

        void AddTile(const std::string& name, float texX, float texY, float texWidth, float texHeight);
        void RemoveTile(const std::string& name);
        void Clear();

        std::string GetString() const;
        void SaveToFile(const char* path);

        std::string GetPath() const;

    private:
        Ref<GLTexture> _mapTexture;
        std::unordered_map<std::string, Ref<SubTexture>> _tiles;
        std::string _path;
    };
}

