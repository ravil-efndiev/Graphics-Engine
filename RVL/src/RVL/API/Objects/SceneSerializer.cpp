#include "SceneSerializer.hpp"
#include <Core/Utils/Files.hpp>

#include "2D/Sprite.hpp"
#include "2D/TileMap.hpp"
#include "3D/DirectionalLight.hpp"
#include "3D/PointLight.hpp"
#include "3D/Model.hpp"
#include "3D/Material.hpp"
#include "General/Identifier.hpp"
#include "General/Transform.hpp"

#include "Rendering/Renderer/ShaderLibrary.hpp"

namespace Rvl
{
    SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
    {
        _scene = scene;
    }

    void SceneSerializer::Serialize(const std::string& path)
    {
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Scene" << YAML::Value << "Name";
        emitter << YAML::Key << "Entities" <<  YAML::Value << YAML::BeginSeq;

        for (Entity entity : _scene->_entities)
        {
            for (auto entity2 : _scene->_entities)
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

            SerializeEntity(emitter, entity);
        }

        emitter << YAML::EndSeq << YAML::EndMap;

        Utils::SaveTextToFile(path.c_str(), emitter.c_str());
    }

    void SceneSerializer::Deserialize(const std::string& path)
    {
        std::ifstream stream (path);
        std::stringstream strStream;
        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());

        if (!data["Scene"]) return;

        auto sceneName = data["Scene"].as<std::string>();
        auto entities = data["Entities"];

        if (!entities) return;

        for (auto entity : entities)
        {
            DeserializeEntity(entity, Entity(_scene.get(), entt::null));
        }
    }   
    
    void SceneSerializer::SerializeEntity(YAML::Emitter& emitter, Entity entity)
    {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "ID" << YAML::Value << std::to_string((uint32)entity.GetId());
        emitter << YAML::Key << "Children" << YAML::Value << YAML::BeginSeq;
        auto children = entity.GetData().Children;
        for (auto child : children)
            SerializeEntity(emitter, child);
        emitter << YAML::EndSeq;

        if (entity.Has<Identifier>())
        {
            auto& id = entity.Get<Identifier>();

            emitter << YAML::Key << "Identifier" << YAML::Value;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "Name" << YAML::Value << id.Name;
            emitter << YAML::EndMap;
        }

        if (entity.Has<Transform>())
        {
            auto& tf = entity.Get<Transform>();

            emitter << YAML::Key << "Transform" << YAML::Value;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "Position" << YAML::Value << tf.Position;
            emitter << YAML::Key << "Rotation" << YAML::Value << tf.Rotation;
            emitter << YAML::Key << "Scale" << YAML::Value << tf.Scale;
            emitter << YAML::EndMap;
        }

        if (entity.Has<Sprite>())
        {
            auto& sprite = entity.Get<Sprite>();

            emitter << YAML::Key << "Sprite" << YAML::Value;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "Color" << YAML::Value << sprite.Color;
            emitter << YAML::Key << "Texture" << YAML::Value << (sprite.Texture ? sprite.Texture->GetPath() : "");
            emitter << YAML::Key << "Scale" << YAML::Value << sprite.FixedScale;
            emitter << YAML::Key << "UseTexture" << YAML::Value << sprite.UseTexture;
            emitter << YAML::Key << "UseFixedScale" << YAML::Value << sprite.UseFixedScale;
            emitter << YAML::Key << "SubTexture" << YAML::Value << (sprite.Subtexture ? glm::vec4(
                sprite.Subtexture->GetX(),
                sprite.Subtexture->GetY(),
                sprite.Subtexture->GetWidth(),
                sprite.Subtexture->GetHeight()
            ) : glm::vec4());
            emitter << YAML::EndMap;
        }

        if (entity.Has<TileMap>())
        {
            auto& map = entity.Get<TileMap>();

            emitter << YAML::Key << "TileMap" << YAML::Value;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "TileSetPath" << YAML::Value <<  map.Tileset->GetPath();
            emitter << YAML::Key << "TileMapPath" << YAML::Value << map.Path;
            emitter << YAML::Key << "Scale" << YAML::Value << map.Scale;
            emitter << YAML::Key << "ZIndex" << YAML::Value << map.ZIndex;
            emitter << YAML::EndMap;
        }

        if (entity.Has<DirectionalLight>())
        {
            auto& dl = entity.Get<DirectionalLight>();

            emitter << YAML::Key << "DirectionalLight" << YAML::Value;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "Color" << YAML::Value << dl.Color;
            emitter << YAML::Key << "Ambient" << YAML::Value << dl.Ambient;
            emitter << YAML::Key << "Diffuse" << YAML::Value << dl.Diffuse;
            emitter << YAML::Key << "Specular" << YAML::Value << dl.Specular;
            emitter << YAML::Key << "Intensity" << YAML::Value << dl.Intensity;
            emitter << YAML::EndMap;
        }

        if (entity.Has<PointLight>())
        {
            auto& pl = entity.Get<PointLight>();

            emitter << YAML::Key << "PointLight" << YAML::Value;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "Color" << YAML::Value << pl.Color;
            emitter << YAML::Key << "Ambient" << YAML::Value << pl.Ambient;
            emitter << YAML::Key << "Diffuse" << YAML::Value << pl.Diffuse;
            emitter << YAML::Key << "Specular" << YAML::Value << pl.Specular;
            emitter << YAML::Key << "Intensity" << YAML::Value << pl.Intensity;
            emitter << YAML::Key << "Linear" << YAML::Value << pl.Linear;
            emitter << YAML::Key << "Quadratic" << YAML::Value << pl.Quadratic;
            emitter << YAML::EndMap;
        }


        if (entity.Has<Material>())
        {
            auto& mat = entity.Get<Material>();

            emitter << YAML::Key << "Material" << YAML::Value;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "Ambient" << YAML::Value << mat.Ambient;
            emitter << YAML::Key << "Diffuse" << YAML::Value << mat.Diffuse;
            emitter << YAML::Key << "Specular" << YAML::Value << mat.Specular;
            emitter << YAML::Key << "Shininess" << YAML::Value << mat.Shininess;
            emitter << YAML::Key << "UseTextures" << YAML::Value << mat.UseTexture;
            emitter << YAML::Key << "ProcessLightSources" << YAML::Value << mat.ProcessLightSources;
            if (mat.Textures.size() >= 1)
                emitter << YAML::Key << "TexturePath" << YAML::Value << mat.Textures[0].Path;
            if (mat.Textures.size() >= 2)
                emitter << YAML::Key << "SpecularMapPath" << YAML::Value << mat.Textures[1].Path;
            emitter << YAML::EndMap;
        }

        if (entity.Has<Model>())
        {
            auto& model = entity.Get<Model>();

            std::string type;

            if (model.Type == MeshType::Cube) type = "Cube";
            if (model.Type == MeshType::Sphere) type = "Sphere";
            if (model.Type == MeshType::Cylinder) type = "Cylinder";
            if (model.Type == MeshType::Custom) type = "Custom";

            emitter << YAML::Key << "Model" << YAML::Value;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "Path" << YAML::Value << model.Path;
            emitter << YAML::Key << "MeshType" << YAML::Value << type;
            emitter << YAML::EndMap;
        }
        
        emitter << YAML::EndMap;

    }
    
    void SceneSerializer::DeserializeEntity(YAML::Node entity, Entity parent)
    {
        uint32 id = entity["ID"].as<uint32>();
        std::string name;
        auto identifier = entity["Identifier"];
        if (identifier)
            name = identifier["Name"].as<std::string>();

        Entity loadEntity = _scene->NewEntity(name);

        if (parent.GetId() != entt::null)
            parent.AddChild(loadEntity);

        auto transform = entity["Transform"];
        if (transform)
        {
            auto pos = transform["Position"];
            glm::vec3 vecPos = {pos[0].as<float>(), pos[1].as<float>(), pos[2].as<float>()};

            auto rot = transform["Rotation"];
            glm::vec3 vecRot = {rot[0].as<float>(), rot[1].as<float>(), rot[2].as<float>()};

            auto scale = transform["Scale"];
            glm::vec3 vecScale = {scale[0].as<float>(), scale[1].as<float>(), scale[2].as<float>()};

            loadEntity.Get<Transform>() = Transform(vecPos, vecRot, vecScale);
        }

        auto sprite = entity["Sprite"];
        if (sprite)
        {
            auto color = sprite["Color"];
            glm::vec4 vecCol = {color[0].as<float>(), color[1].as<float>(), color[2].as<float>(), color[3].as<float>()};

            auto texture = sprite["Texture"].as<std::string>();
            float scale = sprite["Scale"].as<float>();
            bool useFScale = sprite["UseFixedScale"].as<bool>();
            bool useTex = sprite["UseTexture"].as<bool>();
            auto subTexture = sprite["SubTexture"];
            
            Sprite* sc;
            if (!texture.empty())
                sc = &loadEntity.Add<Sprite>(texture, scale);
            else
                sc = &loadEntity.Add<Sprite>(vecCol);

            sc->Color = vecCol;
            sc->UseTexture = useTex;
            sc->UseFixedScale = useFScale;
            if (sc->Texture)
                sc->SetSubTexture(subTexture[0].as<float>(), subTexture[1].as<float>(), subTexture[2].as<float>(), subTexture[3].as<float>());
        }

        auto tlm = entity["TileMap"];
        if (tlm)
        {
            auto tlmPath = tlm["TileMapPath"].as<std::string>();
            auto tlsPath = tlm["TileSetPath"].as<std::string>();
            auto scale = tlm["Scale"].as<int>();
            auto zIndex = tlm["ZIndex"].as<float>();

            loadEntity.Add<TileMap>(NewRef<TileSet>(tlsPath), tlmPath, scale, zIndex);
        }   

        auto dl = entity["DirectionalLight"];
        if (dl)
        {
            auto col = dl["Color"];
            glm::vec3 vecCol = {col[0].as<float>(), col[1].as<float>(), col[2].as<float>()};

            auto spec = dl["Specular"];
            glm::vec3 vecSpec = {spec[0].as<float>(), spec[1].as<float>(), spec[2].as<float>()};

            auto ambient = dl["Ambient"];
            glm::vec3 vecAmbient = {ambient[0].as<float>(), ambient[1].as<float>(), ambient[2].as<float>()};

            float intensity = dl["Intensity"].as<float>();
            auto& dlc = loadEntity.Add<DirectionalLight>(vecCol, intensity);
            dlc.Specular = vecSpec;
            dlc.Ambient = vecAmbient;
        }

        auto pl = entity["PointLight"];
        if (pl)
        {
            auto col = pl["Color"];
            glm::vec3 vecCol = {col[0].as<float>(), col[1].as<float>(), col[2].as<float>()};

            auto diff = pl["Diffuse"];
            glm::vec3 vecDif = {diff[0].as<float>(), diff[1].as<float>(), diff[2].as<float>()};

            auto spec = pl["Specular"];
            glm::vec3 vecSpec = {spec[0].as<float>(), spec[1].as<float>(), spec[2].as<float>()};

            auto ambient = pl["Ambient"];
            glm::vec3 vecAmbient = {ambient[0].as<float>(), ambient[1].as<float>(), ambient[2].as<float>()};

            float intensity = pl["Intensity"].as<float>();
            float linear = pl["Linear"].as<float>();
            float quad = pl["Quadratic"].as<float>();

            auto& plc = loadEntity.Add<PointLight>(vecCol, linear, quad, intensity);
            plc.Ambient = vecAmbient;
            plc.Specular = vecSpec;
        }

        auto mat = entity["Material"];
        if (mat)
        {
            auto diff = mat["Diffuse"];
            glm::vec3 vecDif = {diff[0].as<float>(), diff[1].as<float>(), diff[2].as<float>()};

            auto spec = mat["Specular"];
            glm::vec3 vecSpec = {spec[0].as<float>(), spec[1].as<float>(), spec[2].as<float>()};

            auto ambient = mat["Ambient"];
            glm::vec3 vecAmbient = {ambient[0].as<float>(), ambient[1].as<float>(), ambient[2].as<float>()};

            float shininess = mat["Shininess"].as<float>();
            bool useTex = mat["UseTextures"].as<bool>();
            bool procLight = mat["ProcessLightSources"].as<bool>();

            std::string texPath, specPath;
            if (mat["TexturePath"])
                texPath = mat["TexturePath"].as<std::string>();

            if (mat["SpecularMapPath"])
                specPath = mat["SpecularMapPath"].as<std::string>();


            std::vector<MaterialTexture> textures;
            if (!texPath.empty())
            {
                textures.push_back({
                    GLTexture::TextureFromFile(texPath), RVL_TEXTURE_DIFFUSE, Utils::SplitStr(texPath, '/').back(), texPath
                });
            }

            if (!specPath.empty() && !texPath.empty())
            {
                textures.push_back({
                    GLTexture::TextureFromFile(specPath), RVL_TEXTURE_SPECULAR, Utils::SplitStr(specPath, '/').back(), specPath
                });
            }

            loadEntity.Add<Material>(StandartShaderLib::Get("Light"), vecAmbient, shininess, textures, vecDif, vecSpec, useTex).ProcessLightSources = procLight;
        }

        auto model = entity["Model"];
        if (model)
        {
            auto path = model["Path"].as<std::string>();
            auto type = model["MeshType"].as<std::string>();

            MeshType mtype;
            if (type == "Cube") mtype = MeshType::Cube;
            if (type == "Sphere") mtype = MeshType::Sphere;
            if (type == "Cylinder") mtype = MeshType::Cylinder;
            if (type == "Custom") mtype = MeshType::Custom;

            if (!path.empty())
                loadEntity.Add<Model>(path).Type = mtype;
            else
                loadEntity.Add<Model>().Type = mtype;
        }

        auto children = entity["Children"];

        for (auto child : children)
        {
            DeserializeEntity(child, loadEntity);
        }
    }
}

