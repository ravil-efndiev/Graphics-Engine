#ifndef SB_MAINSCENE_HPP
#define SB_MAINSCENE_HPP

#include "Player.hpp"

#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

using namespace rvl;
namespace sb
{
    class MainScene : public rvl::RvlState
    {
    public:
        MainScene();
        ~MainScene();

        void Start() override;
        void Update() override;
        void Tick() override;
        void Render() override;

    private:
        Ref<Sprite> _sprite;
        Ref<Sprite> _sprite1;
        Ref<Sprite> _subtextureEx;

        Ref<Player> _player;

        Ptr<TileMap> _map;

        float _smoothSpeed = 10.f;

        void RenderImGui();
    };
}

#endif
