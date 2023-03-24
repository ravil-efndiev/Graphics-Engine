#ifndef RVL_RENDERER_HPP
#define RVL_RENDERER_HPP

#include <Rvlpch.hpp>
#include <Rvlglpch.hpp>

namespace rvl
{
    class GLVertexArray;
    class GLShaderProgram;
    class PerspectiveCamera;

    class Renderer
    {
    public:
        static void SubmitGeometry(GLVertexArray& vertexArray, GLShaderProgram& shader);

        static void Clear(GLclampf red = 0.f, GLclampf green = 0.f, GLclampf blue = 0.f, GLclampf alpha = 1.f);

        static void CreateScene(const PerspectiveCamera& camera, float winWidth, float winHeight);

        static void GetVeiwport(int rViewport[2]);

    private:
        static inline void DrawIndicies(GLVertexArray& vertexArray);

        static glm::mat4 _projview;

    };
}

#endif
