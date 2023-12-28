#include "HierarchyWindow.hpp"
#include <Rendering/Renderer/StandartMeshes.hpp>
#include <entt/entt.hpp>

namespace Rvl
{
    static std::vector<Entity> children;
    static int id = 0;

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
        
        Hierarchy(_scene->GetEntities(), 0);

        if (ImGui::Button("+", {30.f, 30.f}))
        {
            ImGui::OpenPopup("NewEntity");
        }
        CreateEntityPopup("NewEntity", Entity(_scene.get(), entt::null));

        ImGui::End();

    }

    void HierarchyWindow::Hierarchy(const std::vector<Entity>& entities, int pid)
    {
        for (auto entity : entities)
        {
            for (auto entity2 : entities)
            {
                auto children = entity2.GetData().Children;
                if (std::find(children.begin(), children.end(), entity) != children.end())
                    _skip = true;
            }

            if (_skip) 
            {
                _skip = false;
                continue;
            }

            bool entityDeleted = false;

            auto name = entity.Has<Identifier>() ? entity.Get<Identifier>().Name : "rofl";

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            if (_selected == entity) flags |= ImGuiTreeNodeFlags_Selected;

            bool op = ImGui::TreeNodeEx(name.c_str(), flags);
            if (ImGui::IsItemClicked()) 
                _selected = entity;

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete Entity"))
                    entityDeleted = true;
                
                if (ImGui::MenuItem("Create Entity"))
                    _openPopup = true;

                ImGui::EndPopup();
            }

            if (_openPopup)
            {
                ImGui::OpenPopup((std::string("NewChild##") + std::to_string(pid)).c_str());
                _openPopup = false;
            }
            
            CreateEntityPopup("NewChild##" + std::to_string(pid), entity);

            if (op)
            {
                if (!entityDeleted)
                    Hierarchy(entity.GetData().Children, pid + 1);
                
                ImGui::TreePop();
            }

            if (entityDeleted)
            {
                _scene->RemoveEntity(entity);
                if (_selected == entity)
                    _selected = {};
            }
        }
    }

    void HierarchyWindow::CreateEntityPopup(const std::string& name, Entity parent)
    {
        if (ImGui::BeginPopup(name.c_str()))
        {
            if (ImGui::Button("Empty object")) 
            {
                Entity entity = _scene->NewEntity();

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);
                
                ImGui::CloseCurrentPopup();
            }

            ImGui::Separator();
            ImGui::Text("2D Objects");

            if (ImGui::Button("Sprite")) 
            {
                Entity entity = _scene->NewEntity();
                entity.Add<Sprite>("assets/textures/container.jpg", 1.f);

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);
                
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Tile Map")) 
            {
                Entity entity = _scene->NewEntity();
                entity.Add<TileMap>();

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);
                
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Particle Emitter")) 
            {
                Entity entity = _scene->NewEntity();
                entity.Add<ParticleEmitter>(1000);

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);
                
                ImGui::CloseCurrentPopup();
            }
            
            
            ImGui::Separator();
            ImGui::Text("3D Meshes");

            if (ImGui::Button("Cube")) 
            {
                Entity entity = _scene->NewEntity();
                
                entity.Add<Model>().Meshes = StandartMeshes::Get("Cube");
                entity.Add<Material>(StandartMeshes::GetMaterial());

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);
                
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Sphere")) 
            {
                Entity entity = _scene->NewEntity();
                
                auto& model = entity.Add<Model>();
                model.Meshes = StandartMeshes::Get("Sphere");
                model.Type = MeshType::Sphere;
                entity.Add<Material>(StandartMeshes::GetMaterial());

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);

                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Cylinder")) 
            {
                Entity entity = _scene->NewEntity();
                
                auto& model = entity.Add<Model>();
                model.Meshes = StandartMeshes::Get("Cylinder");
                model.Type = MeshType::Cylinder;
                entity.Add<Material>(StandartMeshes::GetMaterial());

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);

                ImGui::CloseCurrentPopup();
            }

            ImGui::Separator();
            ImGui::Text("3D Lighting");

            if (ImGui::Button("Point light")) 
            {
                Entity entity = _scene->NewEntity();
                entity.Add<PointLight>(glm::vec3(1.f, 1.f, 1.f), 0.9f, 0.32f);

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);

                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Directional light")) 
            {
                Entity entity = _scene->NewEntity();
                entity.Add<DirectionalLight>(glm::vec3(1.f, 1.f, 1.f));

                if (parent.GetId() != entt::null)
                    parent.AddChild(entity);

                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }   
    }


    void HierarchyWindow::SetScene(const Ref<Scene>& scene)
    {
        _scene = scene;
        _selected = _scene->_entities[0];
    }

}
