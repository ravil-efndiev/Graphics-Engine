#ifndef SB_MAINSCENE_HPP
#define SB_MAINSCENE_HPP

#include <RVL.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/SubTexture.hpp>

using namespace Rvl;
namespace sb
{
    class MainScene : public Rvl::State
    {
    public:
        MainScene();
        ~MainScene();

        void Start() override;
        void Update() override;
        void Tick() override;
        void Render() override;

    private:
        float _smoothSpeed = 10.f;

        void RenderImGui();

        Entity _test;
        Entity _tileMap;

        MovementComponent* _mc;
        SpriteComponent* _sc;
        TransformComponent* _tc;

        glm::vec4 _tintColor { 1.f, 1.f, 1.f, 1.f };
    };
}

#endif
