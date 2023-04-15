#include "Sprite.hpp"
#include <Rvlglpch.hpp>

#include <stb_image.h>

#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLBuffer.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"

#include "Rendering/Renderer/Renderer.hpp"

namespace rvl
{
    Sprite::Sprite()
    {
        _position = {0.f, 0.f};
    }

    Sprite::Sprite(const Vector2f& position)
    {
        _position = position;
    }

    Sprite::Sprite(float x, float y)
    {
        _position = {x, y};
    }   

    Sprite::~Sprite() {}

    void Sprite::LoadTexture(const std::string &filename)
    {
        _texture = std::make_unique<GLTexture>(filename);
        GenerateMesh();
    }

    void Sprite::Draw()
    {
        _texture->Bind();
        Renderer::SubmitGeometry(*_vao, *_shaderProgram, {{"Texture", 0}});
        _texture->Unbind();
    }

    void Sprite::GenerateMesh()
    {
        _vao = std::make_shared<GLVertexArray>();
        _positionVbo = std::make_shared<GLVertexBuffer>(std::vector<glm::vec3>(
            {
                {-1  + _position.X(), -1 + _position.Y(), 0.0f},
                {1 + _position.X(), -1 + _position.Y(), 0.0f},
                {1 + _position.X(), 1 + _position.Y(), 0.0f},
                {-1  + _position.X(), 1 + _position.Y(), 0.0f},
            }
        ));

        glm::vec3 glmColor = glm::vec3(1.f, 1.f, 1.f);

        _colorVbo = std::make_shared<GLVertexBuffer>(std::vector<glm::vec3>(
            {glmColor, glmColor, glmColor, glmColor}
        ));

        _textureCoordsVbo = std::make_shared<GLVertexBuffer>(std::vector<glm::vec2>(
            {
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f}
            }
        ));

        _indicies = std::make_shared<GLIndexBuffer>(std::vector<uint32_t>({0, 1, 2, 2, 3, 0}));

        _vao->AddVertexBuffer(_positionVbo);
        _vao->AddVertexBuffer(_colorVbo);
        _vao->AddVertexBuffer(_textureCoordsVbo);
        _vao->AddIndexBuffer(_indicies);

        _shaderProgram = std::make_unique<GLShaderProgram>("../RVL/res/shaders/textured.vert", "../RVL/res/shaders/textured.frag");
        _shaderProgram->BindAttribute(0, "position");
        _shaderProgram->BindAttribute(1, "color");
        _shaderProgram->BindAttribute(2, "coords");
        _shaderProgram->Link();
    }
}
