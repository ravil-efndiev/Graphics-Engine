#include "Renderer3D.hpp"

#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"

namespace Rvl
{
    glm::mat4 Renderer3D::_projview;

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
        RenderCommand::DrawIndicies(vertexArray);
        shader.Unbind();
    }

    void Renderer3D::SubmitVa(const Ref<GLVertexArray>& vertexArray, const Ref<GLShaderProgram>& shader)
    {
        shader->Bind();
        shader->SetUniformMat4("u_Projview", _projview);
        RenderCommand::DrawIndicies(vertexArray);
        shader->Unbind();
    }   

    void Renderer3D::SubmitMesh(const Mesh& mesh, const MaterialComponent& material, const Transform& transform)
    {
        int diffuseNr = 1;
        int specularNr = 1;

        auto textures = material.Textures;
        auto shader = material.Shader;

        shader->Bind();
        shader->SetUniformMat4("u_Projview", _projview);
        shader->SetUniformMat4("u_Transform", transform.GetMatrix());
        
        for (int i = 0; i < textures.size(); i++)
        {
            GLTexture::ActivateTexture(i);
            std::string number;
            std::string name = textures[i].Type;

            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
                
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);

            shader->SetUniformInt(name + number, i);
            
            GLTexture::BindTextureUnit(textures[i].Id, i);
        }
        GLTexture::ActivateTexture(0);

        RenderCommand::DrawIndicies(mesh.GetVao());
        shader->Unbind();
    }

}
