#pragma once

#include "HierarchyWindow.hpp"
#include "InspectorWindow.hpp"

using namespace Rvl;
class EditorState : public Rvl::State
{
public:
    EditorState();
    ~EditorState();

    void Start() override;
    void Update() override;
    void Render() override;

private:
    void RenderImGui();
    void DockspaceAndMenu();

    Entity _model;
    Entity _sprite;
    Entity _directionalLight;

    glm::vec2 _camRotation {0.f};
    glm::vec3 _light { 10.f, 0.f, 3.f };
    glm::vec3 _lightPosition;

    Ref<HierarchyWindow> _hierarchy;
    Ref<InspectorWindow> _inspector;

    bool _lock = false;

    Ref<GLTexture> tex;
};

