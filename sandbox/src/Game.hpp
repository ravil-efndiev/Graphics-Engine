#ifndef SB_GAME_HPP
#define SB_GAME_HPP

#include "MainScene.hpp"

namespace name
{
    class Game : public rvl::RvlApp
    {
    public:
        Game();
        ~Game();

    private:
        void Start() override;
        void Update() override;
        void Render() override;

    };
}

#endif
