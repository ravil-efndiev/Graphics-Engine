#include "AnimationComponent.hpp"

namespace rvl
{
    Ref<AnimationComponent> AnimationComponent::Create(const Ref<Sprite>& sprite)
    {
        return CreateRef<AnimationComponent>(sprite);
    }

    AnimationComponent::AnimationComponent(const Ref<Sprite>& sprite)
    {
        _sprite = sprite;
    }

    AnimationComponent::~AnimationComponent()
    {

    }

    void AnimationComponent::Start()
    {
    }
    
    void AnimationComponent::Update()
    {
    }
    
    void AnimationComponent::OnAttach()
    {
    }

    void AnimationComponent::AddAnimation(const std::string& name, TimeStep animTimer, float startX, float startY, float endX, float endY, float subSpriteWidth, float subSpriteHeight)
    {
        _animations.emplace(
            name, 
            CreatePtr<Animation>(_sprite, animTimer, startX, startY, endX, endY, subSpriteWidth, subSpriteHeight)
        );
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

    AnimationComponent::Animation::Animation(const Ref<Sprite>& sprite, TimeStep animTimer, float startX, float startY, float endX, float endY, float subSpriteWidth, float subSpriteHeight)
        : _sprite(sprite), _startX(startX), _startY(startY), _endX(endX), _endY(endY), _animTimer(animTimer),
          _subSpriteWidth(subSpriteWidth), _subSpriteHeight(subSpriteHeight)
    {
        _currentX = _startX;
        _sprite->SetSubTexture(startX, startY, subSpriteWidth, subSpriteHeight);
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
            _sprite->SetSubTexture(_currentX, _startY, _subSpriteWidth, _subSpriteHeight);
        }
    }
}
