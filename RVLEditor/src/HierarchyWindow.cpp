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
            auto name = entity.GetComponent<IdentifierComponent>().Name;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
            if (_selected == entity) flags |= ImGuiTreeNodeFlags_Selected;

            bool op = ImGui::TreeNodeEx(name.c_str(), flags);
            if (ImGui::IsItemClicked()) 
                _selected = entity;

            if (op)
                ImGui::TreePop();
        }

        ImGui::End();
    }
}
