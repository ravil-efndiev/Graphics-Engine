#include "StandartMeshes.hpp"
#include "ModelLoader.hpp"

namespace Rvl
{
    std::unordered_map<std::string, std::vector<Mesh>> StandartMeshes::_meshes;
    Material StandartMeshes::_material;

    void StandartMeshes::Init()
    {
        ModelLoader loader;

        loader.LoadModel("standart_assets/obj/cube.obj");
        _meshes.emplace("Cube", loader.GetMeshes());
        _material = loader.GetMaterial();

        loader.LoadModel("standart_assets/obj/sphere.obj");
        _meshes.emplace("Sphere", loader.GetMeshes());
        
        loader.LoadModel("standart_assets/obj/cylinder.obj");
        _meshes.emplace("Cylinder", loader.GetMeshes());
    }
    
    std::vector<Mesh> StandartMeshes::Get(const std::string& name)
    {
        auto it = _meshes.find(name);
        if (it != _meshes.end())
            return it->second;
        return {};
    }
    
    Material StandartMeshes::GetMaterial()
    {
        return _material;
    }
}