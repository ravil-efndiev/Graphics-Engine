#ifndef RVL_ANIMATIONCOMPONENT_HPP
#define RVL_ANIMATIONCOMPONENT_HPP

#include <API/Objects/Sprite.hpp>
#include <API/Time.hpp>
#include "Component.hpp"

namespace Rvl
{
    class AnimationComponent : public Component
    {
    public:
        static Ref<AnimationComponent> Create(const Ref<Sprite>& sprite);

        AnimationComponent(const Ref<Sprite>& sprite);
        ~AnimationComponent();

        void Start() override;
        void Update() override;
        void OnAttach() override;

        void AddAnimation(const std::string& name, TimeStep animTimer, float startX, float startY, float endX, float endY, float subSpriteWidth, float subSpriteHeight);
        void Play(const std::string& name);

        bool IsAnimationDone();

    private:
        class Animation
        {
        public:
            Animation(const Ref<Sprite>& sprite, TimeStep animTimer, float startX, float startY, float endX, float endY, float subSpriteWidth, float subSpriteHeight);

            void Play();

            bool _done = false;
        private:
            Ref<Sprite> _sprite;
            TimeStep _timer, _animTimer;
            float _startX, _startY, _endX, _endY;
            float _subSpriteWidth, _subSpriteHeight;
            float _currentX;

        };

        Ref<Sprite> _sprite;
        std::map<std::string, Ptr<Animation>> _animations;
        Animation* _currentAnimation;
    };
}

#endif
