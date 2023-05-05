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
        rvl::Ref<rvl::GLTexture> _texture;
        rvl::Ref<rvl::GLTexture> _texture2;
        rvl::Ref<rvl::Rectangle> _rect;

        rvl::Ref<rvl::Sprite> _sprite;

        float _camSpeed = 15.f;
    };
}

#endif
