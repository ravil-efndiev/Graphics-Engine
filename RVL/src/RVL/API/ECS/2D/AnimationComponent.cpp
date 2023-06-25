#include "AnimationComponent.hpp"
#include "SpriteComponent.hpp"

namespace Rvl
{
    AnimationComponent::~AnimationComponent() {}

    void AnimationComponent::Update() {}

    void AnimationComponent::AddAnimation(const std::string& name, TimeStep animTimer, float startX, float startY, float endX, float subSpriteWidth, float subSpriteHeight)
    {
        Ref<Animation> animation = NewRef<Animation>(animTimer, startX, startY, endX, subSpriteWidth, subSpriteHeight);
        _animations.emplace(name, animation);
        _currentAnimation = animation.get();
    }

    void AnimationComponent::Play(const std::string& name)
    {
        if (_animations[name] != nullptr)
        {
            _animations[name]->Play();
            _currentAnimation = _animations[name].get();
        }
        else throw Error(std::string("no animation with name '").append(name).append("' found"), RVL_RUNTIME_ERROR);
    }

    bool AnimationComponent::IsAnimationDone()
    {
        return _currentAnimation->_done;
    }

    glm::vec4 AnimationComponent::GetSubTextureData() const
    {
        return _currentAnimation->GetSubTextureData();
    }

    AnimationComponent::Animation::Animation(TimeStep animTimer, float startX, float startY, float endX, float subSpriteWidth, float subSpriteHeight)
        : _startX(startX), _startY(startY), _endX(endX), _animTimer(animTimer),
          _subSpriteWidth(subSpriteWidth), _subSpriteHeight(subSpriteHeight)
    {
        _currentX = _startX;
        _subTextureData = {startX, startY, subSpriteWidth, subSpriteHeight};
    }

    void AnimationComponent::Animation::Play()
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
    
    glm::vec4 AnimationComponent::Animation::GetSubTextureData() const
    {
        return _subTextureData;
    }
}
