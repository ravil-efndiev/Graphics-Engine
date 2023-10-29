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
        if (_selected.HasComponent<IdentifierComponent>())
        {
            ImGui::Separator();

            auto& id = _selected.GetComponent<IdentifierComponent>();
            std::string oldName = id.Name;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::TreeNodeEx("Identifier##inspector_identifier", flags))
            {
                ImGui::InputText("Name", &id.Name);

                if (id.Name.empty())
                    id.Name = oldName;

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }

        if (_selected.HasComponent<TransformComponent>())
        {
            ImGui::Separator();

            auto& transform = _selected.GetComponent<TransformComponent>();

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::TreeNodeEx("Transform##inspector_transform", flags))
            {
                DragVec3("Position##transform_position", transform.Position.GetValuePtr());
                DragVec3("Rotation##transform_rotation", transform.Rotation.GetValuePtr());
                DragVec3("Scale##transform_scale", transform.Scale.GetValuePtr());

                ImGui::TreePop();
            }
            
            ImGui::Dummy({0.f, 20.f});
        }

        if (_selected.HasComponent<SpriteComponent>())
        {
            ImGui::Separator();

            auto& sprite = _selected.GetComponent<SpriteComponent>();

            UIData.SubtextureSize = {sprite._subTexture->GetWidth(), sprite._subTexture->GetHeight()};
            UIData.SubtexturePos = {sprite._subTexture->GetX(), sprite._subTexture->GetY()};

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::TreeNodeEx("Sprite##inspector_sprite", flags))
            {
                if (ImGui::BeginCombo("Draw Type", sprite.GetDrawType() == SpriteComponent::DrawType::Color ? "Color" : "Texture"))
                {
                    bool colorSelected = false, texSelected = false;

                    if (ImGui::Selectable("Texture", &texSelected))
                        sprite._drawType = SpriteComponent::DrawType::Texture;

                    if (ImGui::Selectable("Color", &colorSelected))
                    {
                        sprite._drawType = SpriteComponent::DrawType::Color;
                        sprite._fixedScale = false;
                    }

                    ImGui::EndCombo();
                }

                if (sprite.GetDrawType() == SpriteComponent::DrawType::Texture)
                {
                    auto str = "Texture: " + (Utils::SplitStr(sprite._texture->GetPath(), '/').back());
                    ImGui::Text("%s", str.c_str());
                    ImGui::SameLine();

                    auto path = OpenFileDialogButton("Select ...##texture_select", "png,jpg");

                    if (!path.empty())
                        sprite.LoadTexture(path);
                }

                ImGui::Dummy({0.f, 5.f});

                if (sprite.GetDrawType() == SpriteComponent::DrawType::Texture)
                    ImGui::Checkbox("Use Fixed Scale", &sprite._fixedScale);

                if (sprite.GetDrawType() == SpriteComponent::DrawType::Color)
                    sprite._fixedScale = false;

                if (sprite._fixedScale)
                {
                    DragFloat("Fixed Scale", &sprite._scale);
                    sprite.ResetScale();
                }

                ImGui::Dummy({0.f, 10.f});

                ImGui::ColorEdit4("Color##sprite_color", glm::value_ptr(sprite._color));

                if (sprite.GetDrawType() == SpriteComponent::DrawType::Texture)
                    ImGui::Checkbox("Use Color as Tint", &sprite._useColorAsTint);

                ImGui::Dummy({0.f, 10.f});
                
                if (sprite.GetDrawType() == SpriteComponent::DrawType::Texture)
                {
                    ImGui::Checkbox("Use custom subtexture", &UIData.UseSubTexture);
                    if (UIData.UseSubTexture)
                    {
                        DragVec2("Tile size (px)", &UIData.SubtextureSize, {'W', 'H'});
                        DragVec2("Tile coords", &UIData.SubtexturePos);

                        sprite.SetSubTexture(UIData.SubtexturePos.x, UIData.SubtexturePos.y, UIData.SubtextureSize.x, UIData.SubtextureSize.y);
                    }
                    else if (!(sprite._subTexture->_x == 0.f && sprite._subTexture->_y == 0.f &&
                             sprite._subTexture->_width == sprite._texture->GetWidth() && sprite._subTexture->_height == sprite._texture->GetHeight()))
                        sprite.ResetSubTexture();
                }

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }

        if (_selected.HasComponent<ModelComponent>())
        {
            ImGui::Separator();

            auto& model = _selected.GetComponent<ModelComponent>();

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::TreeNodeEx("Point Light##inspector_pl", flags))
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

        if (_selected.HasComponent<PointLightComponent>())
        {
            ImGui::Separator();

            auto& pl = _selected.GetComponent<PointLightComponent>();

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::TreeNodeEx("Point Light##inspector_pl", flags))
            {
                DragVec3("Ambient##pl_ambient", &pl.Ambient, {'R', 'G', 'B'});
                DragVec3("Diffuse##pl_diffuse", &pl.Diffuse, {'R', 'G', 'B'});
                DragVec3("Specular##pl_specular", &pl.Specular, {'R', 'G', 'B'});
                DragFloat("Linear##pl_linear", &pl.Linear);
                DragFloat("Quadratic##pl_quadratic", &pl.Quadratic);

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }   

        if (_selected.HasComponent<DirectionalLightComponent>())
        {
            ImGui::Separator();

            auto& dl = _selected.GetComponent<DirectionalLightComponent>();

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::TreeNodeEx("Directional Light##inspector_dl", flags))
            {
                DragVec3("Ambient##dl_ambient", &dl.Ambient, {'R', 'G', 'B'});
                DragVec3("Diffuse##dl_diffuse", &dl.Diffuse, {'R', 'G', 'B'});
                DragVec3("Specular##dl_specular", &dl.Specular, {'R', 'G', 'B'});

                ImGui::TreePop();
            }

            ImGui::Dummy({0.f, 20.f});
        }

        ImGui::End();
    }
}
