#ifndef SB_GAME_HPP
#define SB_GAME_HPP

#include "MainScene.hpp"

namespace sb
{
    class Game : public rvl::RvlApp
    {
    public:
        Game();
        ~Game();

    private:
        void Start() override;
        void Update() override;
        void Tick() override;

    };
}

#endif
