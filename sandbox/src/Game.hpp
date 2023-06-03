#ifndef SB_GAME_HPP
#define SB_GAME_HPP

#include "MainScene.hpp"

namespace sb
{
    class Game : public Rvl::App
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
