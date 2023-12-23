#include "HierarchyWindow.hpp"
#include <Rendering/Renderer/StandartMeshes.hpp>

namespace Rvl
{
    HierarchyWindow::HierarchyWindow(const Ref<Scene>& scene)
        : _scene(scene)
    {
        _selected = _scene->_entities[0];
    }

    Entity HierarchyWindow::GetSelected() const
    {
        return _selected;
    }
    
    void HierarchyWindow::ImGuiRender()
    {
        ImGui::Begin("Hierarchy");
        
        for (auto entity : _scene->_entities)
        {
            bool entityDeleted = false;
            auto name = entity.Get<Identifier>().Name;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            if (_selected == entity) flags |= ImGuiTreeNodeFlags_Selected;

            bool op = ImGui::TreeNodeEx(name.c_str(), flags);
            if (ImGui::IsItemClicked()) 
                _selected = entity;

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete Entity"))
                {
                    entityDeleted = true;
                }

                ImGui::EndPopup();
            }

            if (op)
                ImGui::TreePop();

            if (entityDeleted)
            {
                _scene->RemoveEntity(entity);
                if (_selected == entity)
                    _selected = {};
            }

        }

        if (ImGui::Button("+", {30.f, 30.f}))
        {
            ImGui::OpenPopup("New Entity");
        }

        if (ImGui::BeginPopup("New Entity"))
        {
            if (ImGui::Button("Empty object")) 
            {
                _scene->NewEntity();
                ImGui::CloseCurrentPopup();
            }

            ImGui::Separator();
            ImGui::Text("2D Objects");

            if (ImGui::Button("Sprite")) 
            {
                _scene->NewEntity().Add<Sprite>("assets/textures/container.jpg", 1.f);
                ImGui::CloseCurrentPopup();
            }

            ImGui::Separator();
            ImGui::Text("3D Meshes");

            if (ImGui::Button("Cube")) 
            {
                Entity model = _scene->NewEntity();
                
                model.Add<Model>().Meshes = StandartMeshes::Get("Cube");
                model.Add<Material>(StandartMeshes::GetMaterial());

                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Sphere")) 
            {
                Entity model = _scene->NewEntity();
                
                auto& mc = model.Add<Model>();
                mc.Meshes = StandartMeshes::Get("Sphere");
                mc.Type = MeshType::Sphere;
                model.Add<Material>(StandartMeshes::GetMaterial());

                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Cylinder")) 
            {
                Entity model = _scene->NewEntity();
                
                auto& mc = model.Add<Model>();
                mc.Meshes = StandartMeshes::Get("Cylinder");
                mc.Type = MeshType::Cylinder;
                model.Add<Material>(StandartMeshes::GetMaterial());

                ImGui::CloseCurrentPopup();
            }

            ImGui::Separator();
            ImGui::Text("3D Lighting");

            if (ImGui::Button("Point light")) 
            {
                _scene->NewEntity().Add<PointLight>(glm::vec3(1.f, 1.f, 1.f), 0.9f, 0.32f);
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Directional light")) 
            {
                _scene->NewEntity().Add<DirectionalLight>(glm::vec3(1.f, 1.f, 1.f));
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::End();

    }

    void HierarchyWindow::SetScene(const Ref<Scene>& scene)
    {
        _scene = scene;
        _selected = _scene->_entities[0];
    }

}
