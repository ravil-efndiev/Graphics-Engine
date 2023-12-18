#include "Animator2D.hpp"
#include "Sprite.hpp"

namespace Rvl
{
    Animator2D::~Animator2D() {}

    void Animator2D::Update() {}

    void Animator2D::AddAnimation(const std::string& name, TimeStep animTimer, float startX, float startY, float endX, float subSpriteWidth, float subSpriteHeight)
    {
        Ref<Animation> animation = NewRef<Animation>(animTimer, startX, startY, endX, subSpriteWidth, subSpriteHeight);
        _animations.emplace(name, animation);
        _currentAnimation = animation.get();
    }

    void Animator2D::Play(const std::string& name)
    {
        if (_animations[name] != nullptr)
        {
            _animations[name]->Play();
            _currentAnimation = _animations[name].get();
        }
        else throw Error(std::string("no animation with name '").append(name).append("' found"), RVL_RUNTIME_ERROR);
    }

    bool Animator2D::IsAnimationDone()
    {
        return _currentAnimation->_done;
    }

    glm::vec4 Animator2D::GetSubTextureData() const
    {
        return _currentAnimation->GetSubTextureData();
    }

    Animator2D::Animation::Animation(TimeStep animTimer, float startX, float startY, float endX, float subSpriteWidth, float subSpriteHeight)
        : _startX(startX), _startY(startY), _endX(endX), _animTimer(animTimer),
          _subSpriteWidth(subSpriteWidth), _subSpriteHeight(subSpriteHeight)
    {
        _currentX = _startX;
        _subTextureData = {startX, startY, subSpriteWidth, subSpriteHeight};
    }

    void Animator2D::Animation::Play()
    {
        _done = false;
        _timer += 100.f * Time::DeltaTime();
        if (_timer >= _animTimer)
        {
            _timer = 0;

            if (_currentX < _endX)
            {
                _currentX += 1.f;
            }
            else
            {
                _currentX = _startX;
                _done = true;
            }
            _subTextureData = {_currentX, _startY, _subSpriteWidth, _subSpriteHeight};
        }
    }
    
    glm::vec4 Animator2D::Animation::GetSubTextureData() const
    {
        return _subTextureData;
    }
}
