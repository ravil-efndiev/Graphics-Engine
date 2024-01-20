#include "MainState.hpp"
#include <RVL/Core/EntryPoint.hpp>

class Game : public Rvl::App
{
public:
    Game(uint32 winWidth, uint32 winHeight, const std::string& winName) : App(winWidth, winHeight, winName) {}
    ~Game() {}

private:
    void Start() override
    {
        SetClearColor({0.1f, 0.1f, 0.1f});
        _currentState = NewPtr<MainState>();
        _currentState->Start();
    }

    void Update() override
    {
        _currentState->Update();
    }

    void Tick() override
    {
        _currentState->Tick();
    }
};

int main()
{
    Rvl::status_t status = Rvl::InitializeApp<Game>(1200, 800, "Sandbox");
    return status;   
}
