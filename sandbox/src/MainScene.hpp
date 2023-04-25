#ifndef SB_MAINSCENE_HPP
#define SB_MAINSCENE_HPP

#include <RVL.hpp>

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
        rvl::Ref<rvl::Sprite> _sprite1;
        rvl::Ref<rvl::Sprite> _sprite2;
        rvl::Ref<rvl::Sprite> _sprite3;
        rvl::Ref<rvl::Rectangle> _rect;
    };
}

#endif
