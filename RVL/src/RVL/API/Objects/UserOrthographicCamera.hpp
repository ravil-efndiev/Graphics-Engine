#ifndef RVL_USERORTHOGRAPHICCAMERA_HPP
#define RVL_USERORTHOGRAPHICCAMERA_HPP

#include "Entity.hpp"
#include <Core/Core.hpp>
#include <API/Math/Math.hpp>
#include <API/Time.hpp>
#include <Rendering/Renderer/OrthographicCamera.hpp>

namespace Rvl
{
    class UserOrthographicCamera
    {
    public:
        static Ref<UserOrthographicCamera> Create(const glm::vec2& position = {0.f, 0.f}, float zoom = 1.f);

        UserOrthographicCamera(const glm::vec2& position = {0.f, 0.f}, float zoom = 1.f);
        ~UserOrthographicCamera();

        float GetZoom() const;
        void SetZoom(float zoom);

        void SetPosition(const glm::vec2& position);
        glm::vec2 GetPosition() const;

        void SetRotationZ(float rotation);
        float GetRotationZ() const;

        void Follow(const Ref<Entity>& entity, Axis axis = Axis::Horizontal | Axis::Vertical, bool smooth = true, float smoothSpeed = 10.f, float deadZone = 0.05f, TimeStep deltaTime = Time::DeltaTime());

        Ref<OrthographicCamera> GetCamera();

    private:
        Ref<OrthographicCamera> _camera;
    };
}

#endif
