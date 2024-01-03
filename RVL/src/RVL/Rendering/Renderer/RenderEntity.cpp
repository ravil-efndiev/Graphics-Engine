#include "RenderEntity.hpp"

namespace Rvl
{
    RenderEntity::RenderEntity(Mesh* mesh, size_t size, bool repeatUV, RenderType type)
    {
        _mesh = mesh;
        _type = type;
        _size = size;
        _repeatUV = repeatUV;
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

    bool RenderEntity::RepeatUV() const
    {   
        return _repeatUV;
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
    
    void RenderEntity::SetRepeatUV(bool repeatUV)
    {
        _repeatUV = repeatUV;
    }
}
