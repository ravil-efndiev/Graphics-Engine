#pragma once

#include "API/ECS/Entity.hpp"
#include "API/ECS/General/TransformComponent.hpp"
#include <Core/Core.hpp>
#include <API/Math/Math.hpp>
#include <API/Time.hpp>
#include <Rendering/Renderer/OrthographicCamera.hpp>
#include "UserCamera.hpp"

namespace Rvl
{
    class UserOrthographicCamera : public UserCamera
    {
    public:
        static Ref<UserOrthographicCamera> New(const glm::vec2& position = {0.f, 0.f}, float zoom = 1.f);

        UserOrthographicCamera(const glm::vec2& position, float zoom);
        ~UserOrthographicCamera();

        float GetZoom() const;
        void SetZoom(float zoom);

        void SetPosition(const glm::vec2& position);
        glm::vec2 GetPosition() const;

        void SetRotationZ(float rotation);
        float GetRotationZ() const;

        void Follow(TransformComponent* transform, Axis axis = Axis::Horizontal | Axis::Vertical, bool smooth = true, float smoothSpeed = 10.f, float deadZone = 0.05f, TimeStep deltaTime = Time::DeltaTime());

        Ref<Camera> GetCamera() const override;

    private:
        Ref<OrthographicCamera> _camera;
    };
}

