#pragma once

#include <RVL.hpp>
#include <Rendering/OpenGL/GLShaderProgram.hpp>
#include <Rendering/Renderer/PostProcess.hpp>

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
    void PostRender() override;

private:
    void RenderImGui();

    Entity _model;
    Entity _sprite;

    glm::vec2 _camRotation {0.f};
    glm::vec3 _light { 10.f, 0.f, 3.f };

    Ref<GLShaderProgram> _mShader;
    Ref<PostProcess> _postProcess;

    bool _lock = false;
};

