#include "StandartSystems.hpp"

#include "2D/Sprite.hpp"
#include "2D/Movement2D.hpp"
#include "2D/Animator2D.hpp"
#include "2D/TileMap.hpp"
#include "3D/Material.hpp"
#include "3D/DirectionalLight.hpp"
#include "3D/Model.hpp"
#include "3D/PointLight.hpp"
#include "General/Transform.hpp"

#include <Rendering/OpenGL/GLShaderProgram.hpp>
#include <Rendering/Renderer/ModelLoader.hpp>

namespace Rvl
{
    static int pointLightIndex = 0;

    void Sprite2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Sprite>() || entity.Has<Model>())
                continue;

            RVL_ASSERT(entity.Has<Transform>(), "entity with sprite component doesn't have transform component");

            auto sprite = entity.Get<Sprite>();
            if (sprite.UseFixedScale)
            {
                entity.Get<Transform>().Scale = glm::vec3(sprite.ScaleVec2, 0.f);
            }
        }
    }

    void Movement2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Movement2D>())
                continue;

            RVL_ASSERT(entity.Has<Transform>(), "entity with movement component doesn't have transform component");
            auto& movement = entity.Get<Movement2D>();

            movement.Update();
            entity.Get<Transform>().Position += glm::vec3(movement.GetVelocity(), 0.0) * (float)Time::DeltaTime();
        }
    }

    void Animation2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Animator2D>())
                continue;

            RVL_ASSERT(entity.Has<Sprite>(), "entity with animation component doesn't have a sprite component");

            glm::vec4 subtextureData = entity.Get<Animator2D>().GetSubTextureData();
            entity.Get<Sprite>().SetSubTexture(subtextureData.x, subtextureData.y, subtextureData.z, subtextureData.w);
        }
    }

    void TileMapSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<TileMap>())
                continue;

            RVL_ASSERT(entity.Has<Transform>(), "entity with tilemap component doesn't have a transform component");

            auto& map = entity.Get<TileMap>();
            auto& tf = entity.Get<Transform>();
            
            for (Tile& tile : map.MapTiles)
            {
                tile.GetWorldPosition() = tile.GetRelativePosition() + tf.Position;
            }
        }
    }

    void MaterialSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Material>())
                continue;

            auto& material = entity.Get<Material>();

            if (material.ProcessLightSources)
            {
                int index = 0;
                for (auto entity2 : entities)
                {
                    RVL_ASSERT(!(entity2.Has<DirectionalLight>() && entity2.Has<PointLight>()),
                        "Entity has multiple light components interfiering with each other");

                    if (entity2.Has<DirectionalLight>())
                    {
                        RVL_ASSERT(entity2.Has<Transform>(), "Directional light doesn't have transform component");
                        
                        auto light = entity2.Get<DirectionalLight>();
                        auto lightTf = entity2.Get<Transform>();

                        material.SetUniform("u_DirectionalLight.ambient",  light.Ambient);
                        material.SetUniform("u_DirectionalLight.diffuse",  light.Diffuse); 
                        material.SetUniform("u_DirectionalLight.specular", light.Specular); 
                        material.SetUniform("u_DirectionalLight.direction", lightTf.Rotation); 
                    }

                    if (entity2.Has<PointLight>())
                    {
                        RVL_ASSERT(entity2.Has<Transform>(), "Point light doesn't have transform component");

                        auto light = entity2.Get<PointLight>();
                        auto lightTf = entity2.Get<Transform>();

                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].ambient",   light.Ambient);
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].diffuse",   light.Diffuse); 
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].specular",  light.Specular); 
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].position",  lightTf.Position); 
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].constant",  light.Constant);
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].linear",    light.Linear);
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].quadratic", light.Quadratic);	
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].none", 0.f);	
                        index++;
                    }
                }
                material.SetUniform("u_LightsCount", index);
            }
        
        }
    }

    void LightSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (entity.Has<DirectionalLight>())
            {
                auto& dl = entity.Get<DirectionalLight>();

                dl.Diffuse = dl.Color * dl.Intensity;
            }

            if (entity.Has<PointLight>())
            {
                auto& pl = entity.Get<PointLight>();

                pl.Diffuse = pl.Color * pl.Intensity;
            }

        }
    }


    void ModelLoaderSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Model>())
                continue;
            
            auto& model = entity.Get<Model>();
            
            if (model._load) 
            {
                ModelLoader loader (model.Path);
                loader.LoadModel();

                model.Meshes = loader.GetMeshes();
                auto mat = loader.GetMaterial();

                if (!entity.Has<Material>())
                {
                    entity.Add<Material>(
                        mat.Shader,
                        mat.Ambient,
                        mat.Shininess,
                        mat.Textures,
                        mat.Diffuse,
                        mat.Specular,
                        mat.UseTexture
                    );
                }
                else
                {
                    auto& mat2 = entity.Get<Material>();
                    if (mat2.Textures.empty() && mat2.UseTexture)
                        mat2.Textures = mat.Textures;
                }
                model._load = false;
            }
        }
    }
}
