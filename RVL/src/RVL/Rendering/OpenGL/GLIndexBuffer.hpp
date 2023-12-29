#pragma once

#include <Rvlglpch.hpp>
#include <Core/Core.hpp>

namespace Rvl
{
    class GLIndexBuffer
    {
    public:
        GLIndexBuffer(const std::vector<uint32_t>& indicies);
        ~GLIndexBuffer();

        void Bind();
        void Unbind();

        int GetIndiciesCount();

    private:
        GLuint _bufferId;

        int _indiciesCount;

    };
}

