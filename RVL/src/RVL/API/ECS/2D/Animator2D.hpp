#pragma once

#include <Entity.hpp>
#include <API/Time.hpp>

namespace Rvl
{
    class Animator2D
    {
    public:
        Animator2D() = default;
        Animator2D(const Animator2D&) = default;
        ~Animator2D();

        void Update();

        void AddAnimation(const std::string& name, TimeStep animTimer, float startX, float startY, float endX, float subSpriteWidth, float subSpriteHeight);
        void Play(const std::string& name);

        bool IsAnimationDone();

        glm::vec4 GetSubTextureData() const;

    private:
        struct Animation
        {
            Animation(TimeStep animTimer, float startX, float startY, float endX, float subSpriteWidth, float subSpriteHeight);

            void Play();
            glm::vec4 GetSubTextureData() const;

            bool _done = false;

            TimeStep _timer, _animTimer;
            float _startX, _startY, _endX;
            float _subSpriteWidth, _subSpriteHeight;
            float _currentX;

            glm::vec4 _subTextureData;
        };

        std::unordered_map<std::string, Ref<Animation>> _animations;
        Animation* _currentAnimation;
    };
}

