#pragma once

#include "MainState.hpp"

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

