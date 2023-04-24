#include <RVL.hpp>

using namespace rvl;

class MainScene : public RvlScene
{
public:
    MainScene() {}
    ~MainScene() {}

    void Start() override
    {
        _camera = Camera::Create();
        _rect = Rectangle::Create(0.f, 0.f, 2.f, 3.5f, Vector3f(1.f, 1.f, 0.f));
        _sprite = Sprite::Create(3.f, 0.f);
        _sprite->LoadTexture("container.jpg");

        _sprite1 = Sprite::Create(-3.f, 0.f);
        _sprite1->LoadTexture("a.jpg");

        _sprite2 = Sprite::Create(0.f, -3.f);
        _sprite2->LoadTexture("container.jpg");

    }

    void Update() override 
    {
        if (Input::IsKeyPressed(Keys::RVL_KEY_W))
            _rect->Position->Y += 7.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_S))
            _rect->Position->Y -= 7.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_D))
            _rect->Position->X += 7.f * Time::DeltaTime();

        if (Input::IsKeyPressed(Keys::RVL_KEY_A))
            _rect->Position->X -= 7.f * Time::DeltaTime();

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
    Ref<Rectangle> _rect;
    Ref<Sprite> _sprite;
    Ref<Sprite> _sprite1;
    Ref<Sprite> _sprite2;
};

class Game : public RvlApp
{
public:
    Game() : RvlApp(1000, 700, "rvl game") {}
    ~Game() {}

private:
    void Start() override
    {
        _currentScene = CreateRef<MainScene>();
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
