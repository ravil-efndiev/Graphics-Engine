#pragma once

#include "MainScene.hpp"

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

