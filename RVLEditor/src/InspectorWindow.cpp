#include "InspectorWindow.hpp"
#include <nfd.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <Core/Utils/Files.hpp>
#include "GuiElements.hpp"

namespace Rvl
{
    struct InspectorUIData
    {
        bool UseSubTexture = false;

        glm::vec2 SubtexturePos {0.f};
        glm::vec2 SubtextureSize {0.f};

        ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;
    };

    static InspectorUIData UIData;

    InspectorWindow::InspectorWindow() {}

    void InspectorWindow::SetSelected(Entity entity)
    {
        _selected = entity;
    }

    template<class T>
    void DrawComponent(const char* label, Entity selected, const std::function<void(T&)>& drawFunc, bool canBeDeleted = true) 
    {
        if (selected.Has<T>())
        {
            bool componentRemoved = false;
            ImGui::Separator();

            auto& component = selected.Get<T>();

            bool open = ImGui::TreeNodeEx(label, UIData.NodeFlags);

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Remove Component", "", nullptr, canBeDeleted))
                    componentRemoved = true;

                ImGui::EndPopup();
            }

            if (open)
            {
                drawFunc(component);       
                ImGui::TreePop();
            }
            
            ImGui::Dummy({0.f, 20.f});
            if (componentRemoved)
                selected.Remove<T>();
        }
    }

    void InspectorWindow::ImGuiRedner()
    {
        ImGui::Begin("Inspector");

        if (_selected == Entity())
        {
            ImGui::End();
            return;
        }

        DrawComponent<IdentifierComponent>("Identifier", _selected, [](auto& id) 
        {
            ImGui::InputText("Name", &id.Name);

            if (id.Name.empty())
                id.Name = "Entity";
        }, false);

        DrawComponent<TransformComponent>("Transform", _selected, [](auto& transform) 
        {
            DragVec3("Position##transform_position", transform.Position.GetValuePtr());
            DragVec3("Rotation##transform_rotation", transform.Rotation.GetValuePtr());
            DragVec3("Scale##transform_scale", transform.Scale.GetValuePtr());
        });

        DrawComponent<SpriteComponent>("Sprite", _selected, [](auto& sprite) 
        {
            UIData.SubtextureSize = {sprite.Subtexture->GetWidth(), sprite.Subtexture->GetHeight()};
            UIData.SubtexturePos = {sprite.Subtexture->GetX(), sprite.Subtexture->GetY()};

            if (ImGui::BeginCombo("Draw Type", sprite.Drawtype == SpriteComponent::DrawType::Color ? "Color" : "Texture"))
            {
                bool colorSelected = false, texSelected = false;

                if (ImGui::Selectable("Texture", &texSelected))
                    sprite.Drawtype = SpriteComponent::DrawType::Texture;

                if (ImGui::Selectable("Color", &colorSelected))
                {
                    sprite.Drawtype = SpriteComponent::DrawType::Color;
                    sprite.UseFixedScale = false;
                }

                ImGui::EndCombo();
            }

            if (sprite.Drawtype == SpriteComponent::DrawType::Texture)
            {
                auto str = "Texture: " + (Utils::SplitStr(sprite.Texture->GetPath(), '/').back());
                ImGui::Text("%s", str.c_str());
                ImGui::SameLine();

                auto path = OpenFileDialogButton("Select ...##texture_select", "png,jpg");

                if (!path.empty())
                    sprite.LoadTexture(path);
            }

            ImGui::Dummy({0.f, 5.f});

            if (sprite.Drawtype == SpriteComponent::DrawType::Texture)
                ImGui::Checkbox("Use Fixed Scale", &sprite.UseFixedScale);

            if (sprite.Drawtype == SpriteComponent::DrawType::Color)
                sprite.UseFixedScale = false;

            if (sprite.UseFixedScale)
            {
                DragFloat("Fixed Scale", &sprite.Scale);
                sprite.ResetScale();
            }

            ImGui::Dummy({0.f, 10.f});

            ImGui::ColorEdit4("Color##sprite_color", glm::value_ptr(sprite.Color));

            if (sprite.Drawtype == SpriteComponent::DrawType::Texture)
                ImGui::Checkbox("Use Color as Tint", &sprite.UseColorAsTint);

            ImGui::Dummy({0.f, 10.f});
            
            if (sprite.Drawtype == SpriteComponent::DrawType::Texture)
            {
                ImGui::Checkbox("Use custom subtexture", &UIData.UseSubTexture);
                if (UIData.UseSubTexture)
                {
                    DragVec2("Tile size (px)", &UIData.SubtextureSize, {'W', 'H'});
                    DragVec2("Tile coords", &UIData.SubtexturePos);

                    sprite.SetSubTexture(UIData.SubtexturePos.x, UIData.SubtexturePos.y, UIData.SubtextureSize.x, UIData.SubtextureSize.y);
                }
                else if (!(sprite.Subtexture->_x == 0.f && sprite.Subtexture->_y == 0.f &&
                            sprite.Subtexture->_width == sprite.Texture->GetWidth() && sprite.Subtexture->_height == sprite.Texture->GetHeight()))
                    sprite.ResetSubTexture();
            }
        });

        DrawComponent<ModelComponent>("Model", _selected, [](auto& model) 
        {
            auto str = "Model path: " + (Utils::SplitStr(model.Path, '/').back());
            ImGui::Text("%s", str.c_str());
            ImGui::SameLine();

            auto path = OpenFileDialogButton("Select ...##modelpath_select", "obj");
            if (!path.empty() && path != model.Path)
                model.LoadModel(path);
        });

        DrawComponent<PointLightComponent>("Point Light", _selected, [](auto& pl) 
        {
            ImGui::ColorEdit3("Color##pl_diffuse", glm::value_ptr(pl.Color));
            DragFloat("Intensity##pl_intensity", &pl.Intensity);

            ImGui::Dummy({0.f, 5.f});
            ImGui::Text("Advanced settings");
            ImGui::Separator();
            ImGui::ColorEdit3("Ambient##pl_ambient", glm::value_ptr(pl.Ambient));
            ImGui::ColorEdit3("Specular##pl_specular", glm::value_ptr(pl.Specular));

            DragFloat("Linear##pl_linear", &pl.Linear);
            DragFloat("Quadratic##pl_quadratic", &pl.Quadratic);
        });

        DrawComponent<DirectionalLightComponent>("Directional Light", _selected, [](auto& dl) 
        {
            ImGui::ColorEdit3("Color##dl_diffuse", glm::value_ptr(dl.Color));
            DragFloat("Intensity##dl_intensity", &dl.Intensity);

            ImGui::Dummy({0.f, 5.f});
            ImGui::Text("Advanced settings");
            ImGui::Separator();
            ImGui::ColorEdit3("Ambient##dl_ambient", glm::value_ptr(dl.Ambient));
            ImGui::ColorEdit3("Specular##dl_specular", glm::value_ptr(dl.Specular));
        });

        DrawComponent<MaterialComponent>("Material", _selected, [](auto& material) 
        {
            ImGui::ColorEdit3("Ambient##mat_ambient", glm::value_ptr(material.Ambient));
            ImGui::ColorEdit3("Diffuse##mat_diffuse", glm::value_ptr(material.Diffuse));
            ImGui::ColorEdit3("Specular##mat_specular", glm::value_ptr(material.Specular));
            DragFloat("Shininess##mat_shine", &material.Shininess);

            for (auto& texture : material.Textures)
            {
                ImGui::Text("%s", texture.Filename.c_str());
                ImGui::SameLine();
                ImGui::Text("%s", texture.Type.c_str());
                ImGui::SameLine();

                auto path = OpenFileDialogButton("Select ...##modeltexture_select", "png,jpg");
                if (!path.empty())
                {
                    texture =        
                    {
                        GLTexture::TextureFromFile(path),
                        texture.Type, Utils::SplitStr(path, '/').back()
                    };
                }
            }
        });

        if (ImGui::Button("Add Component"))
        {
            ImGui::OpenPopup("Components");
        }

        if (ImGui::BeginPopup("Components"))
        {
            ImGui::Text("Sprite");
            ImGui::SameLine();
            if (ImGui::Button("Add##sadd"))
            {
                if (!_selected.Has<ModelComponent>() && !_selected.Has<SpriteComponent>())
                    _selected.Add<SpriteComponent>("./assets/textures/container.jpg", 1.f);
                ImGui::CloseCurrentPopup();
            }

            ImGui::Text("Point Light");
            ImGui::SameLine();
            if (ImGui::Button("Add##pladd"))
            {
                if (!_selected.Has<PointLightComponent>())
                    _selected.Add<PointLightComponent>(glm::vec3(0.5f, 0.5f, 0.5f), 0.09f, 0.032f);
                ImGui::CloseCurrentPopup();
            }

            ImGui::Text("3D Model");
            ImGui::SameLine();
            if (ImGui::Button("Add##madd"))
            {
                if (!_selected.Has<ModelComponent>())
                {
                    _selected.Add<ModelComponent>("/Users/Belokan/RVL Engine/RVLEditor/assets/textures/backpack.obj");
                    _selected.Add<MaterialComponent>(glm::vec3(0.5f, 0.5f, 0.5f), 32.f);
                }
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }
}
