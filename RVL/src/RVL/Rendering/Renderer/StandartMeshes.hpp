#pragma once
#include "Mesh.hpp"
#include "3D/Material.hpp"
#include "Core/Core.hpp"

namespace Rvl
{
    class StandartMeshes
    {
    public:
        static void Init();

        static std::vector<Mesh> Get(const std::string& name);
        static Material GetMaterial();
        
    private:
        static std::unordered_map<std::string, std::vector<Mesh>> _meshes;
        static Material _material;
    };
}

