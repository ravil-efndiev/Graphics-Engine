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

    void InspectorWindow::ImGuiRedner()
    {
        ImGui::Begin("Inspector");

        if (_selected.Has<IdentifierComponent>())
        {
            ImGui::Separator();

            auto& id = _selected.Get<IdentifierComponent>();

            if (ImGui::TreeNodeEx("Identifier##inspector_identifier", UIData.NodeFlags))
            {
                ImGui::InputText("Name", &id.Name);

                if (id.Name.empty())
                    id.Name = "Entity";

                ImGui::TreePop();
            }
            
            ImGui::Dummy({0.f, 20.f});
        }

        if (_selected.Has<TransformComponent>())
        {
            ImGui::Separator();

            auto& transform = _selected.Get<TransformComponent>();

            if (ImGui::TreeNodeEx("Transform##inspector_transform", UIData.NodeFlags))
            {
                DragVec3("Position##transform_position", transform.Position.GetValuePtr());
                DragVec3("Rotation##transform_rotation", transform.Rotation.GetValuePtr());
                DragVec3("Scale##transform_scale", transform.Scale.GetValuePtr());

                ImGui::TreePop();
            }
            
            ImGui::Dummy({0.f, 20.f});
        }

        if (_selected.Has<SpriteComponent>())
        {
            ImGui::Separator();

            auto& sprite = _selected.Get<SpriteComponent>();

            UIData.SubtextureSize = {sprite.Subtexture->GetWidth(), sprite.Subtexture->GetHeight()};
            UIData.SubtexturePos = {sprite.Subtexture->GetX(), sprite.Subtexture->GetY()};

            if (ImGui::TreeNodeEx("Sprite##inspector_sprite", UIData.NodeFlags))
            {
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

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }

        if (_selected.Has<ModelComponent>())
        {
            ImGui::Separator();

            auto& model = _selected.Get<ModelComponent>();

            if (ImGui::TreeNodeEx("Model##inspector_model", UIData.NodeFlags))
            {
                auto str = "Model path: " + (Utils::SplitStr(model._path, '/').back());
                ImGui::Text("%s", str.c_str());
                ImGui::SameLine();

                auto path = OpenFileDialogButton("Select ...##modelpath_select", "obj");
                if (!path.empty() && path != model._path)
                    model.LoadModel(path);

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }

        if (_selected.Has<PointLightComponent>())
        {
            ImGui::Separator();

            auto& pl = _selected.Get<PointLightComponent>();

            if (ImGui::TreeNodeEx("Point Light##inspector_pl", UIData.NodeFlags))
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

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }   

        if (_selected.Has<DirectionalLightComponent>())
        {
            ImGui::Separator();

            auto& dl = _selected.Get<DirectionalLightComponent>();

            if (ImGui::TreeNodeEx("Directional Light##inspector_dl", UIData.NodeFlags))
            {
                ImGui::ColorEdit3("Color##pl_diffuse", glm::value_ptr(dl.Color));
                DragFloat("Intensity##pl_intensity", &dl.Intensity);

                ImGui::Dummy({0.f, 5.f});
                ImGui::Text("Advanced settings");
                ImGui::Separator();
                ImGui::ColorEdit3("Ambient##pl_ambient", glm::value_ptr(dl.Ambient));
                ImGui::ColorEdit3("Specular##pl_specular", glm::value_ptr(dl.Specular));

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }

        if (_selected.Has<MaterialComponent>())
        {
            ImGui::Separator();

            auto& material = _selected.Get<MaterialComponent>();

            if (ImGui::TreeNodeEx("Material##inspector_mat", UIData.NodeFlags))
            {
                ImGui::ColorEdit3("Ambient##mat_ambient", glm::value_ptr(material.Ambient));
                ImGui::ColorEdit3("Diffuse##mat_diffuse", glm::value_ptr(material.Diffuse));
                ImGui::ColorEdit3("Specular##mat_specular", glm::value_ptr(material.Specular));
                DragFloat("Shininess##mat_shine", &material.Shininess);

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }

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

        }

        ImGui::End();
    }
}
