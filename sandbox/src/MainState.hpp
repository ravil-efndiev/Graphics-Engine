#pragma once
#include <RVL.hpp>
#include <Rendering/OpenGL/GLVertexArray.hpp>
#include <Rendering/OpenGL/GLBuffer.hpp>
#include <Rendering/OpenGL/GLShaderProgram.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

using namespace Rvl;
class MainState : public Rvl::State
{
public:
    MainState();
    ~MainState();

    void Start() override;
    void Update() override;
    void Tick() override;
    void Render() override;

private:
    float _smoothSpeed = 10.f;

    void RenderImGui();

    Entity _test;
    Entity _tileMap;

    SpriteComponent* _sc;
    TransformComponent* _tc;

    glm::vec4 _tintColor { 1.f, 1.f, 1.f, 1.f };

    glm::vec2 _camRotation {0.f};

    Ref<GLVertexArray> _vao;
    Ref<GLVertexBuffer> _vbo;
    Ref<GLShaderProgram> _shader;

    bool _lock = false;
};

