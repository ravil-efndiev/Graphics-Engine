#ifndef SB_MAINSCENE_HPP
#define SB_MAINSCENE_HPP

#include "Player.hpp"

#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

namespace name
{
    class MainScene : public rvl::RvlScene
    {
    public:
        MainScene();
        ~MainScene();

        void Start() override;
        void Update() override;
        void Tick() override;
        void Render() override;

    private:
        rvl::Ref<rvl::Sprite> _sprite;
        rvl::Ref<rvl::Sprite> _sprite1;

        rvl::Ref<rvl::Sprite> _subtextureEx;

        rvl::Ref<Player> _player;

        float _smoothSpeed = 10.f;

        void RenderImGui();
    };
}

#endif
