#include "Renderer3D.hpp"

#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"

namespace Rvl
{
    glm::mat4 Renderer3D::_projview;
    Renderer3D::Statistics Renderer3D::_stats;

    static bool lol = true;

    struct MeshInstanceVertex
    {
        glm::vec3 Scale;
        glm::mat4 Transform;
    };

    void Renderer3D::BeginContext(const Ref<Camera>& camera, float viewportWidth, float viewportHeight)
    {
        _projview = camera->GetProjectionMatrix(viewportWidth, viewportHeight) * camera->GetViewMatrix();
    }

    void Renderer3D::EndContext()
    {
    }

    void Renderer3D::SubmitVa(GLVertexArray& vertexArray, GLShaderProgram& shader)
    {
        shader.Bind();
        shader.SetUniformMat4("u_Projview", _projview);
        RenderApi::DrawIndicies(vertexArray, RenderType::Normal);
        shader.Unbind();
    }

    void Renderer3D::SubmitVa(const Ref<GLVertexArray>& vertexArray, const Ref<GLShaderProgram>& shader)
    {
        shader->Bind();
        shader->SetUniformMat4("u_Projview", _projview);
        RenderApi::DrawIndicies(vertexArray, RenderType::Normal);
        shader->Unbind();
    }   

    void Renderer3D::SubmitMesh(const Mesh& mesh, const Material& material, const Transform& transform)
    {
        SetMaterialParams(material, transform);
        RenderApi::DrawIndicies(mesh.GetVao(), RenderType::Normal);
        GLTexture::BindTextureUnit(0, 0);
    }

    void Renderer3D::SubmitMeshInstanced(Mesh& mesh, const Material& material, std::vector<Transform>& transform, bool reallocBuffer, bool repeatUV)
    {
        SetInstanceVbos(mesh, transform, reallocBuffer, repeatUV);

        SetMaterialParams(material, std::nullopt);
        RenderApi::DrawIndiciesInstanced(mesh.GetVao(), RenderType::Normal, transform.size());
        GLTexture::BindTextureUnit(0, 0);
        _stats.DrawCalls++;
    }

    void Renderer3D::SubmitEntity(RenderEntity& entity, const Material& material, const Transform& transform)
    {
        SetMaterialParams(material, transform);

        Mesh* mesh = entity.GetMesh();
        for (int i = 0; i < entity.GetMeshSize(); i++)
        {
            RenderApi::DrawIndicies(mesh[i].GetVao(), entity.GetType());
        }

        GLTexture::BindTextureUnit(0, 0);
    }

    void Renderer3D::SubmitEntityInstanced(RenderEntity& entity, const Material& material, std::vector<Transform>& transform, bool reallocBuffer, bool repeatUV)
    {
        SetMaterialParams(material, std::nullopt);

        Mesh* mesh = entity.GetMesh();
        for (int i = 0; i < entity.GetMeshSize(); i++)
        {
            SetInstanceVbos(mesh[i], transform, reallocBuffer, repeatUV);

            RenderApi::DrawIndiciesInstanced(mesh[i].GetVao(), entity.GetType(), transform.size());
        }

        GLTexture::BindTextureUnit(0, 0);
    }

    void Renderer3D::SetMaterialParams(const Material& material, const std::optional<Transform>& transform)
    {
        int diffuseNr = 1;
        int specularNr = 1;

        auto textures = material.Textures;
        auto shader = material.Shader;

        shader->Bind();
        shader->SetUniformMat4("u_Projview", _projview);
        if (transform)
            shader->SetUniformMat4("u_Transform", transform.value().GetMatrix());
        shader->SetUniformInt("u_HasTexture", (int)material.UseTexture);
        shader->SetUniformVec3("u_Material.diffuse",  material.Diffuse);
        shader->SetUniformVec3("u_Material.specular", material.Specular);
        shader->SetUniformVec3("u_Material.ambient",  material.Ambient);
        shader->SetUniformFloat("u_Material.shininess", material.Shininess);
        
        for (int i = 0; i < textures.size(); i++)
        {
            GLTexture::ActivateTexture(i);
            std::string number;
            std::string name = textures[i].Type;
            
            if (name == RVL_TEXTURE_DIFFUSE)
                number = std::to_string(diffuseNr++);
                
            else if (name == RVL_TEXTURE_SPECULAR)
                number = std::to_string(specularNr++);

            shader->SetUniformInt(name + number, i);
            
            GLTexture::BindTextureUnit(textures[i].Id, i);
        }
    }

    void Renderer3D::SetInstanceVbos(Mesh& mesh, std::vector<Transform>& transform, bool reallocBuffer, bool repeatUV)
    {
        auto vao = mesh.GetVao();
        if (!mesh._instanceVboLoaded)
        {
            Ref<GLVertexBuffer> instanceVbo = NewRef<GLVertexBuffer>();
            instanceVbo->SetLayout({
                LayoutElement{ElementType::Vec3, 0, sizeof(MeshInstanceVertex), false},
                LayoutElement{ElementType::Mat4, offsetof(MeshInstanceVertex, Transform), sizeof(MeshInstanceVertex), false}
            });
            vao->AddVertexBuffer(instanceVbo, true);
            mesh._instanceVboLoaded = true;
        }

        std::vector<MeshInstanceVertex> iv (transform.size());
        for (int i = 0; i < iv.size(); i++)
        {
            iv[i].Transform = transform[i].GetMatrix();
            if (repeatUV)
                iv[i].Scale = transform[i].Scale;
            else
                iv[i].Scale = {1.f, 1.f, 1.f};
        }

        if (reallocBuffer)
            vao->GetVertexBuffers().back()->ReallocData(iv.data(), iv.size() * sizeof(MeshInstanceVertex));
        else
            vao->GetVertexBuffers().back()->SetData(iv.data(), iv.size() * sizeof(MeshInstanceVertex));
    }

    Renderer3D::Statistics Renderer3D::GetStats()
    {
        return _stats;
    }
 
    void Renderer3D::ResetStats()
    {
        _stats.DrawCalls = 0;
    }

}
