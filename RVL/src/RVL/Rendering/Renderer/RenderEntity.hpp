#pragma once
#include "Mesh.hpp"
#include "RenderApi.hpp"

namespace Rvl
{
    class RenderEntity
    {
    public:
        RenderEntity(Mesh* mesh, size_t size, bool repeatUV, RenderType type = RenderType::Normal);
        ~RenderEntity();

        Mesh* GetMesh();
        size_t GetMeshSize() const;
        RenderType GetType() const;
        bool RepeatUV() const;

        void SetMesh(Mesh* mesh, size_t size);
        void SetType(RenderType type);
        void SetRepeatUV(bool repeatUV);

    private:
        Mesh* _mesh;
        size_t _size;
        RenderType _type;
        bool _repeatUV;
    };
}
