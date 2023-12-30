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
        RenderApi::DrawIndicies(vertexArray);
        shader.Unbind();
    }

    void Renderer3D::SubmitVa(const Ref<GLVertexArray>& vertexArray, const Ref<GLShaderProgram>& shader)
    {
        shader->Bind();
        shader->SetUniformMat4("u_Projview", _projview);
        RenderApi::DrawIndicies(vertexArray);
        shader->Unbind();
    }   

    void Renderer3D::SubmitMesh(const Mesh& mesh, const Material& material, const Transform& transform)
    {
        int diffuseNr = 1;
        int specularNr = 1;

        auto textures = material.Textures;
        auto shader = material.Shader;

        shader->Bind();
        shader->SetUniformMat4("u_Projview", _projview);
        shader->SetUniformMat4("u_Transform", transform.GetMatrix());
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
                
            else if (name == RVL_TEXTURE_DIFFUSE)
                number = std::to_string(specularNr++);

            shader->SetUniformInt(name + number, i);
            
            GLTexture::BindTextureUnit(textures[i].Id, i);
        }

        RenderApi::DrawIndicies(mesh.GetVao());
        GLTexture::BindTextureUnit(0, 0);
        shader->Unbind();
    }

    void Renderer3D::SubmitMeshInstanced(Mesh& mesh, const Material& material, std::vector<glm::mat4>& transform, bool reallocBuffer)
    {
        auto vao = mesh.GetVao();
        if (!mesh._instanceVboLoaded)
        {
            Ref<GLVertexBuffer> instanceVbo = NewRef<GLVertexBuffer>(transform);
            instanceVbo->SetLayout({
                LayoutElement{ElementType::Mat4, 0, 4 * sizeof(glm::vec4), false}
            });
            vao->AddVertexBuffer(instanceVbo, true);
            mesh._instanceVboLoaded = true;
        }

        if (reallocBuffer)
            vao->GetVertexBuffers().back()->ReallocData(transform.data(), transform.size() * sizeof(glm::mat4));
        else
            vao->GetVertexBuffers().back()->SetData(transform.data(), transform.size() * sizeof(glm::mat4));

        int diffuseNr = 1;
        int specularNr = 1;

        auto textures = material.Textures;
        auto shader = material.Shader;

        shader->Bind();
        shader->SetUniformMat4("u_Projview", _projview);
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
                
            else if (name == RVL_TEXTURE_DIFFUSE)
                number = std::to_string(specularNr++);

            shader->SetUniformInt(name + number, i);
            
            GLTexture::BindTextureUnit(textures[i].Id, i);
        }

        RenderApi::DrawIndiciesInstanced(vao, transform.size());
        GLTexture::BindTextureUnit(0, 0);
        _stats.DrawCalls++;
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
