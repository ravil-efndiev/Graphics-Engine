#include "Game.hpp"

using namespace Rvl;

Game::Game(uint32 winWidth, uint32 winHeight, const std::string& name) : App(winWidth, winHeight, name) {}
Game::~Game() {}

void Game::Start()
{
    SetClearColor({0.1f, 0.1f, 0.1f});
    _currentState = NewPtr<MainState>();
    _currentState->Start();
}

void Game::Update()
{
    _currentState->Update();
}

void Game::Tick()
{
    _currentState->Tick();
}
