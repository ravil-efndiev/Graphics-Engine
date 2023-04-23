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
        _rect = std::make_unique<Rectangle>(0.f, 0.f, 2.f, 3.5f, Vector3f(1.f, 1.f, 0.f));
        _sprite = std::make_unique<Sprite>(3.f, 0.f);
        _sprite->LoadTexture("container.jpg");

        _sprite1 = std::make_unique<Sprite>(-3.f, 0.f);
        _sprite1->LoadTexture("floor1.png");

        _sprite2 = std::make_unique<Sprite>(0.f, -3.f);
        _sprite2->LoadTexture("container.jpg");

    }

    void Update() override 
    {
        if (Input::IsKeyPressed(Keys::RVL_KEY_W))
            _rect->Position->Y += 0.1f;

        if (Input::IsKeyPressed(Keys::RVL_KEY_S))
            _rect->Position->Y -= 0.1f;

        if (Input::IsKeyPressed(Keys::RVL_KEY_D))
            _rect->Position->X += 0.1f;

        if (Input::IsKeyPressed(Keys::RVL_KEY_A))
            _rect->Position->X -= 0.1f;

        _camera->Position = _rect->Position();
    }

    void Render() override
    {
        _rect->Draw();
        _sprite->Draw();
        _sprite1->Draw();
        _sprite2->Draw();
    }

private:
    std::unique_ptr<Rectangle> _rect;
    std::unique_ptr<Sprite> _sprite;
    std::unique_ptr<Sprite> _sprite1;
    std::unique_ptr<Sprite> _sprite2;
};

class Game : public RvlApp
{
public:
    Game() : RvlApp(1000, 700, "rvl game") {}
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
