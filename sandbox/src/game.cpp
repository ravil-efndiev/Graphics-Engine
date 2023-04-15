#include <RVL.hpp>

using namespace rvl;

class MainScene : public RvlScene
{
public:
    MainScene() {}
    ~MainScene() {}

    void Start() override
    {
        _camera = std::make_unique<Camera>();
        _rect = std::make_unique<Rectangle>(0.f, 0.f, 2.f, 4.f, Vector3f(1.f, 1.f, 0.f));
        _sprite = std::make_unique<Sprite>();
        _sprite->LoadTexture("container.jpg");
    }

    void Update() override {    }

    void Render() override
    {
        _sprite->Draw();
        _rect->Draw();
    }

private:
    std::unique_ptr<Rectangle> _rect;
    std::unique_ptr<Sprite> _sprite;
};

class Game : public RvlApp
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
    CurrentApp = new Game();
}
