#ifndef RVL_ANIMATIONCOMPONENT_HPP
#define RVL_ANIMATIONCOMPONENT_HPP

#include "Entity.hpp"
#include <API/Time.hpp>
#include "Component.hpp"

namespace Rvl
{
    class AnimationComponent : public Component
    {
    public:
        AnimationComponent() = default;
        AnimationComponent(const AnimationComponent&) = default;
        AnimationComponent(Entity* entity);
        ~AnimationComponent();

        void Update() override;

        void AddAnimation(const std::string& name, TimeStep animTimer, float startX, float startY, float endX, float endY, float subSpriteWidth, float subSpriteHeight);
        void Play(const std::string& name);

        bool IsAnimationDone();

    private:
        class Animation
        {
        public:
            Animation(Entity* sprite, TimeStep animTimer, float startX, float startY, float endX, float endY, float subSpriteWidth, float subSpriteHeight);

            void Play();

            bool _done = false;
        private:
            Entity* _sprite;
            TimeStep _timer, _animTimer;
            float _startX, _startY, _endX, _endY;
            float _subSpriteWidth, _subSpriteHeight;
            float _currentX;

        };

        Entity* _sprite;
        std::unordered_map<std::string, Ref<Animation>> _animations;
        Animation* _currentAnimation;
    };
}

#endif
