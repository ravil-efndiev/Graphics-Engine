#ifndef SB_MAINSCENE_HPP
#define SB_MAINSCENE_HPP

#include <RVL.hpp>

#include <Rendering/OpenGL/GLTexture.hpp>

namespace name
{
    class MainScene : public rvl::RvlScene
    {
    public:
        MainScene();
        ~MainScene();

        void Start() override;
        void Update() override;
        void Render() override;

    private:
        rvl::Ref<rvl::Rectangle> _rect;
        rvl::Ref<rvl::Sprite> _sprite;
        rvl::Ref<rvl::Sprite> _sprite1;

        float _smoothSpeed = 10.f;

        void RenderImGui();
    };
}

#endif
