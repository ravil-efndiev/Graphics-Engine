#include "RenderEntity.hpp"

namespace Rvl
{
    RenderEntity::RenderEntity(Mesh* mesh, size_t size, RenderType type)
    {
        _mesh = mesh;
        _type = type;
        _size = size;
    }

    RenderEntity::~RenderEntity() {}
    
    Mesh* RenderEntity::GetMesh()
    {
        return _mesh;
    }

    size_t RenderEntity::GetMeshSize() const
    {
        return _size;
    }
    
    RenderType RenderEntity::GetType() const
    {
        return _type;
    }
    
    void RenderEntity::SetMesh(Mesh* mesh, size_t size)
    {
        _mesh = mesh;
        _size = size;
    }
    
    void RenderEntity::SetType(RenderType type)
    {
        _type = type;
    }
}
