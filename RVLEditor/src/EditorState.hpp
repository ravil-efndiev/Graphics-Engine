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

    Entity _directionalLight, _tlm;
    TileMap* _tlmc;

    glm::vec2 _camRotation {0.f};

    Ref<HierarchyWindow> _hierarchy;
    Ref<InspectorWindow> _inspector;

    bool _lock = false;

    std::string _scenePath;
};

