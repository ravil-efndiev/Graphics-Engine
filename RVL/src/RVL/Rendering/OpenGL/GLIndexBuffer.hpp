#pragma once

#include <Rvlglpch.hpp>
#include <Core/Core.hpp>

namespace Rvl
{
    class GLIndexBuffer
    {
    public:
        GLIndexBuffer(const std::vector<u32>& indicies);
        ~GLIndexBuffer();

        void Bind();
        void Unbind();

        u32 GetIndiciesCount();

    private:
        GLuint _bufferId;

        u32 _indiciesCount;

    };
}

