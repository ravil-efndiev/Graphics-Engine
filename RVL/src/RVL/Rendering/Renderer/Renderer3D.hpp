#pragma once
#include <Core/Core.hpp>
#include "Camera.hpp"
#include "Mesh.hpp"
#include "RenderApi.hpp"
#include "RenderEntity.hpp"
#include "API/ECS/General/Transform.hpp"
#include "API/ECS/3D/Material.hpp"

namespace Rvl
{
    class GLVertexArray;
    class GLVertexBuffer;
    class GLShaderProgram;
    class GLTexture;

    class Renderer3D
    {
    public:
        static void BeginContext(const Ref<Camera>& camera, float viewportWidth, float viewportHeight);
        static void EndContext();

        static void SubmitVa(GLVertexArray& vertexArray, GLShaderProgram& shader);
        static void SubmitVa(const Ref<GLVertexArray>& vertexArray, const Ref<GLShaderProgram>& shader);

        static void SubmitMesh(const Mesh& mesh, const Material& material, const Transform& transform);
        static void SubmitMeshInstanced(Mesh& mesh, const Material& material, std::vector<Transform>& transform, bool reallocBuffer, bool repeatUV = false);

        static void SubmitEntity(RenderEntity& entity, const Material& material, const Transform& trnasform);
        static void SubmitEntityInstanced(RenderEntity& entity, const Material& material, std::vector<Transform>& transform, bool reallocBuffer, bool repeatUV = false);

        struct Statistics
        {
            int DrawCalls = 0;
        };

        static Statistics GetStats();
        static void ResetStats();

    private:
        static void SetMaterialParams(const Material& material, const std::optional<Transform>& trnasform);
        static void SetInstanceVbos(Mesh& mesh, std::vector<Transform>& transform, bool reallocBuffer, bool repeatUV);

    private:
        static glm::mat4 _projview;

        static Statistics _stats;
    };
}

