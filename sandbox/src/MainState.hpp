#pragma once

#include <RVL.hpp>

using namespace Rvl;
class MainState : public Rvl::State
{
public:
    MainState();
    ~MainState();

    void Start() override;
    void Update() override;
    void Render() override;

private:
    void RenderImGui();

    Entity _model;
    Entity _sprite;

    Entity _directionalLight;
    Entity _pointLight;

    glm::vec2 _camRotation {0.f};
    glm::vec3 _light { 10.f, 0.f, 3.f };
    glm::vec3 _lightPosition;

    TransformComponent* _dlTf;
    TransformComponent* _sTf;
    MaterialComponent* _mat;

    bool _lock = false;
};

