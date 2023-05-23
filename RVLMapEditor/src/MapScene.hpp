#ifndef RVL_MAPSCENE_HPP
#define RVL_MAPSCENE_HPP

#include <RVL.hpp>
#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>
#include <API/Objects/Rectangle.hpp>

namespace rvl
{
    class MapScene : public RvlScene
    {
    public:
        MapScene(const std::string& texturePath);
        MapScene(const Ref<TileSet>& tls);
        ~MapScene();

        void Start() override;
        void Update() override;
        void Render() override;

        void InputsEnabled(bool flag);

    private:
        glm::vec2 _viewportSize {0.f}; 

        Ref<TileSet> _tls;
        Ref<TileMap> _tlm;

        std::string _selectedTile = "";

        float _cameraSpeed = 7.f;
        float _cameraZoom = 10.f;

        int _scale = 1.f;
        float _zIndex = 0.01f;
    
    private:
        void RenderUI();
    };
}

#endif
