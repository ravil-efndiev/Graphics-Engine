#include <RVL.hpp>

class MainScene : public rvl::RvlScene
{
public:
    MainScene() {}
    ~MainScene() {}

    void Start() override
    {
        _rect = std::make_shared<rvl::Rectangle>(0.f, 0.f, 3.f, 2.f, rvl::Vector3f(1.f, 0.f, 0.f));
        AddEntity(_rect);
    }

    void Update() override {    }

    void Render() override
    {
        _rect->Draw();
    }

private:
    std::shared_ptr<rvl::Rectangle> _rect;
};

class Game : public rvl::RvlApp
{
public:
    Game() : RvlApp(1000, 800, "rvl game") {}
    ~Game() {}

private:
    void Start() override
    {
        _currentScene = std::make_unique<MainScene>();
        _currentScene->Start();
    }
    
    void Update() override
    {
        _currentScene->Update();
    }

    void Render() override
    {
        _currentScene->Render();
    }
};

void rvl::OnInit()
{
    rvl::CurrentApp = new Game();
}
