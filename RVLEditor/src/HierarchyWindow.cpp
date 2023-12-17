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
            ImGui::OpenPopup("New Entity");
        }

        if (ImGui::BeginPopup("New Entity"))
        {
            if (ImGui::Button("Empty object")) 
            {
                _scene.NewEntity();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Sprite")) 
            {
                _scene.NewEntity().Add<SpriteComponent>("assets/textures/container.jpg", 1.f);
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("3D Model")) 
            {
                Entity model = _scene.NewEntity();
                model.Add<ModelComponent>("/Users/Belokan/RVL Engine/RVLEditor/assets/textures/backpack.obj");
                model.Add<MaterialComponent>(glm::vec3(0.5f, 0.5f, 0.5f), 32.f);
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Point light")) 
            {
                _scene.NewEntity().Add<PointLightComponent>(glm::vec3(1.f, 1.f, 1.f), 0.9f, 0.32f);
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::End();
    }
}
