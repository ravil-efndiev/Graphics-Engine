#pragma once

#include "MainState.hpp"

class Game : public Rvl::App
{
public:
    Game(uint32 winWidth, uint32 winHeight, const std::string& winName);
    ~Game();

private:
    void Start() override;
    void Update() override;
    void Tick() override;
};

