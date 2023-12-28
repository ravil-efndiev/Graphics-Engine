#include "InspectorWindow.hpp"
#include <nfd.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <Core/Utils/Files.hpp>
#include "GuiElements.hpp"
#include <Rendering/Renderer/StandartMeshes.hpp>

namespace Rvl
{
    struct InspectorUIData
    {
        bool UseSubTexture = true;
        bool PSPreview = true;

        int32 EmitTimes = 1;

        glm::vec2 SubtexturePos {0.f};
        glm::vec2 SubtextureSize {0.f};

        std::string TlmPath, TlsPath;
        bool TlmLoadFlag = true;

        ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;
    };

    static InspectorUIData UIData;
    static Entity PrevSelected;

    InspectorWindow::InspectorWindow() {}

    void InspectorWindow::SetSelected(Entity entity)
    {
        _selected = entity;
        if (_selected != PrevSelected)
        {
            UIData.TlmLoadFlag = true;
            UIData.TlmPath.clear();
            UIData.TlsPath.clear();
        }
        PrevSelected = _selected;
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

        DrawComponent<Identifier>("Identifier", _selected, [&](auto& id) 
        {
            ImGui::InputText("Name", &id.Name);

            if (id.Name.empty())
                id.Name = "Entity";

            ImGui::Text("Entity id: %d", (uint32)_selected.GetId());
        }, false);

        DrawComponent<Transform>("Transform", _selected, [](auto& transform) 
        {
            DragVec3("Position##transform_position", &transform.Position);
            DragVec3("Rotation##transform_rotation", &transform.Rotation);
            DragVec3("Scale##transform_scale", &transform.Scale);
        });

        DrawComponent<Sprite>("Sprite", _selected, [](auto& sprite) 
        {
            if (sprite.Subtexture)
            {
                UIData.SubtextureSize = {sprite.Subtexture->GetWidth(), sprite.Subtexture->GetHeight()};
                UIData.SubtexturePos = {sprite.Subtexture->GetX(), sprite.Subtexture->GetY()};
            }

            auto str = sprite.Texture ? "Texture: " + (Utils::SplitStr(sprite.Texture->GetPath(), '/').back())
                : "Texture: none";
            ImGui::Text("%s", str.c_str());
            ImGui::SameLine();

            auto path = OpenFileDialogButton("Select ...##texture_select", "png,jpg");
            if (!path.empty()) sprite.LoadTexture(path);

            ImGui::Checkbox("Use Texture", &sprite.UseTexture);

            if (sprite.UseTexture && sprite.Texture)
                ImGui::Checkbox("Use Fixed Scale", &sprite.UseFixedScale);

            if (!sprite.UseTexture)
                sprite.UseFixedScale = false;

            if (sprite.UseFixedScale)
                DragFloat("Fixed Scale", &sprite.FixedScale);

            ImGui::ColorEdit4("Color##sprite_color", glm::value_ptr(sprite.Color));

            if (sprite.UseTexture && sprite.Texture)
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

        DrawComponent<TileMap>("Tile Map", _selected, [](auto& tlm) 
        {
            if (UIData.TlmLoadFlag)
            {
                if (!tlm.Path.empty()) UIData.TlmPath = tlm.Path;
                if (tlm.Tileset) UIData.TlsPath = tlm.Tileset->GetPath();
                UIData.TlmLoadFlag = false;
            }

            ImGui::Text("Tile Map path: %s", UIData.TlmPath.empty() ? "none" : Utils::SplitStr(UIData.TlmPath, '/').back().c_str());
            ImGui::SameLine();
            auto tp = OpenFileDialogButton("Select##tlm", "rtlm", "./assets");
            if (!tp.empty()) UIData.TlmPath = tp;

            ImGui::Text("Tile Set path: %s", UIData.TlsPath.empty() ? "none" : Utils::SplitStr(UIData.TlsPath, '/').back().c_str());
            ImGui::SameLine();
            auto sp = OpenFileDialogButton("Select##tls", "rtls", "./assets");
            if (!sp.empty()) UIData.TlsPath = sp;

            if (ImGui::Button("Load##tlmload"))
            {
                if (UIData.TlmPath.empty() || UIData.TlsPath.empty())
                    return;
                
                tlm.Load(NewRef<TileSet>(UIData.TlsPath), UIData.TlmPath, tlm.Scale, 0.f);
                UIData.TlmLoadFlag = true;
            }
        });

        DrawComponent<Model>("Model", _selected, [](auto& model) 
        {
            std::string preview;
            if (model.Type == MeshType::Cube) preview = "Cube";
            if (model.Type == MeshType::Sphere) preview = "Sphere";
            if (model.Type == MeshType::Cylinder) preview = "Cylinder";
            if (model.Type == MeshType::Custom) preview = "Custom";

            if (ImGui::BeginCombo("Mesh Type", preview.c_str()))
            {
                bool cube = false, sphere = false, cyl = false, custom = false;

                if (ImGui::Selectable("Cube", &cube))
                {
                    if (!model.Meshes.empty() && model.Type == MeshType::Custom)
                        model.MeshesSaved = model.Meshes;

                    model.Type = MeshType::Cube;
                    model.Meshes = StandartMeshes::Get("Cube");
                }

                if (ImGui::Selectable("Sphere", &sphere))
                {
                    if (!model.Meshes.empty() && model.Type == MeshType::Custom)
                        model.MeshesSaved = model.Meshes;

                    model.Type = MeshType::Sphere;
                    model.Meshes = StandartMeshes::Get("Sphere");
                }

                if (ImGui::Selectable("Cylinder", &cyl))
                {
                    if (!model.Meshes.empty() && model.Type == MeshType::Custom)
                        model.MeshesSaved = model.Meshes;
                    
                    model.Type = MeshType::Cylinder;
                    model.Meshes = StandartMeshes::Get("Cylinder");
                }

                if (ImGui::Selectable("Custom", &custom))
                {
                    if (!model.MeshesSaved.empty())
                    {                    
                        model.Type = MeshType::Custom;
                        model.Meshes = model.MeshesSaved;
                    }
                    else
                    {
                        model.Type = MeshType::Cube;
                        model.Meshes = StandartMeshes::Get("Cube");
                    }
                }

                ImGui::EndCombo();
            }

            ImGui::Text("Model path: %s", Utils::SplitStr(model.Path, '/').back().c_str());
            ImGui::SameLine();

            auto path = OpenFileDialogButton("Select ...##modelpath_select", "obj");
            if (!path.empty() && path != model.Path)
                model.LoadModel(path);
        });

        DrawComponent<PointLight>("Point Light", _selected, [](auto& pl) 
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

        DrawComponent<DirectionalLight>("Directional Light", _selected, [](auto& dl) 
        {
            ImGui::ColorEdit3("Color##dl_diffuse", glm::value_ptr(dl.Color));
            DragFloat("Intensity##dl_intensity", &dl.Intensity);

            ImGui::Dummy({0.f, 5.f});
            ImGui::Text("Advanced settings");
            ImGui::Separator();
            ImGui::ColorEdit3("Ambient##dl_ambient", glm::value_ptr(dl.Ambient));
            ImGui::ColorEdit3("Specular##dl_specular", glm::value_ptr(dl.Specular));
        });

        DrawComponent<Material>("Material", _selected, [](auto& material) 
        {
            ImGui::ColorEdit3("Ambient##mat_ambient", glm::value_ptr(material.Ambient));
            ImGui::ColorEdit3("Diffuse##mat_diffuse", glm::value_ptr(material.Diffuse));
            ImGui::ColorEdit3("Specular##mat_specular", glm::value_ptr(material.Specular));
            DragFloat("Shininess##mat_shine", &material.Shininess);

            ImGui::Checkbox("Use texture##mat_tex", &material.UseTexture);

            int sz = material.Textures.size();
            ImGui::Text("%s", sz <= 0 ? "none" : material.Textures[0].Filename.c_str());
            ImGui::SameLine();
            ImGui::Text("%s", "texture");
            ImGui::SameLine();

            auto path1 = OpenFileDialogButton("Select ...##mattex2", "png,jpg");
            if (!path1.empty() && sz <= 1)
                material.Textures.push_back({GLTexture::TextureFromFile(path1), RVL_TEXTURE_DIFFUSE, Utils::SplitStr(path1, '/').back(), path1});
            if (!path1.empty() && sz > 1)
                material.Textures[1] = {GLTexture::TextureFromFile(path1), RVL_TEXTURE_DIFFUSE, Utils::SplitStr(path1, '/').back(), path1};

            ImGui::Text("%s", sz <= 1 ? "none" : material.Textures[1].Filename.c_str());
            ImGui::SameLine();
            ImGui::Text("%s", "specular map");
            ImGui::SameLine();

            auto path2 = OpenFileDialogButton("Select ...##mattex3", "png,jpg");
            if (!path2.empty() && sz <= 1)
                material.Textures.push_back({GLTexture::TextureFromFile(path2), RVL_TEXTURE_SPECULAR, Utils::SplitStr(path2, '/').back(), path2});
            if (!path2.empty() && sz > 1)
                material.Textures[1] = {GLTexture::TextureFromFile(path2), RVL_TEXTURE_SPECULAR, Utils::SplitStr(path2, '/').back(), path2};
        });

        DrawComponent<ParticleEmitter>("Particle Emitter", _selected, [](auto& emitter) 
        {   
            ImGui::Checkbox("Preview", &UIData.PSPreview);
            ImGui::ColorEdit4("Start Color", glm::value_ptr(emitter.Properties.ColorStart));
            ImGui::ColorEdit4("End Color", glm::value_ptr(emitter.Properties.ColorEnd));
            DragVec3("Position", &emitter.Properties.Position);
            DragFloat("Start Size", &emitter.Properties.SizeStart);
            DragFloat("End Size", &emitter.Properties.SizeEnd);
            DragFloat("Size Variation", &emitter.Properties.SizeVariation);
            DragFloat("RotationRate", &emitter.Properties.RotationRate);
            DragVec3("Velocity", &emitter.Properties.Velocity);
            DragVec3("Velocity Variation", &emitter.Properties.VelocityVariation);
            DragFloat("Life Time", &emitter.Properties.LifeTime);
            
            if (UIData.PSPreview)
            {
                DragInt("Emit times: ", &UIData.EmitTimes);
                emitter.Emit(UIData.EmitTimes);
            }
        });

        AddComponentMenu();

        ImGui::End();
    }

    void InspectorWindow::AddComponentMenu()
    {
        if (ImGui::Button("Add Component"))
        {
            ImGui::OpenPopup("Components");
        }

        if (ImGui::BeginPopup("Components"))
        {
            ImGui::Text("2D Objects");
            ImGui::Separator();
            if (ImGui::Button("Sprite##sadd"))
            {
                if (!_selected.Has<Model>() && !_selected.Has<Sprite>())
                    _selected.Add<Sprite>(glm::vec4(1, 1, 1, 1));
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Tile Map##tlmadd"))
            {
                if (!_selected.Has<TileMap>())
                    _selected.Add<TileMap>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Particle Emitter##peadd"))
            {
                if (!_selected.Has<ParticleEmitter>())
                    _selected.Add<ParticleEmitter>(1000);
                ImGui::CloseCurrentPopup();
            }

            ImGui::Text("3D Objects");
            ImGui::Separator();
            if (ImGui::Button("Point Light##pladd"))
            {
                if (!_selected.Has<PointLight>())
                    _selected.Add<PointLight>(glm::vec3(0.5f, 0.5f, 0.5f), 0.09f, 0.032f);
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Directional Light##dladd"))
            {
                if (!_selected.Has<DirectionalLight>())
                    _selected.Add<DirectionalLight>(glm::vec3(0.5f, 0.5f, 0.5f));
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("3D Mesh##madd"))
            {
                if (!_selected.Has<Model>())
                {
                    auto& model = _selected.Add<Model>();
                    model.Meshes = StandartMeshes::Get("Cube");
                    if (!_selected.Has<Material>())
                        _selected.Add<Material>(StandartMeshes::GetMaterial());
                }
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
}
