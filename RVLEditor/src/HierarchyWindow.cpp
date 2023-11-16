#include "HierarchyWindow.hpp"

namespace Rvl
{
    HierarchyWindow::HierarchyWindow(Scene& scene)
        : _scene(scene)
    {
        _selected = _scene._entities[0];
    }

    Entity HierarchyWindow::GetSelected() const
    {
        return _selected;
    }
    
    void HierarchyWindow::ImGuiRender()
    {
        ImGui::Begin("Hierarchy");
        
        for (auto entity : _scene._entities)
        {
            auto name = entity.Get<IdentifierComponent>().Name;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            if (_selected == entity) flags |= ImGuiTreeNodeFlags_Selected;

            bool op = ImGui::TreeNodeEx(name.c_str(), flags);
            if (ImGui::IsItemClicked()) 
                _selected = entity;

            if (op)
                ImGui::TreePop();
        }

        if (ImGui::Button("+", {20.f, 20.f}))
        {
            _scene.NewEntity();
        }

        ImGui::End();
    }
}
