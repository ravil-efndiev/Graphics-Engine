#pragma once

#include "API/ECS/Entity.hpp"
#include "API/ECS/General/Transform.hpp"
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
        static Ref<UserOrthographicCamera> New(const glm::vec2& position = {0.f, 0.f}, f32 zoom = 1.f);

        UserOrthographicCamera(const glm::vec2& position, f32 zoom);
        ~UserOrthographicCamera();

        f32 GetZoom() const;
        void SetZoom(f32 zoom);

        void SetPosition(const glm::vec2& position);
        glm::vec2 GetPosition() const;

        void SetRotationZ(f32 rotation);
        f32 GetRotationZ() const;

        void Follow(Transform* transform, Axis axis = Axis::Horizontal | Axis::Vertical, bool smooth = true, f32 smoothSpeed = 10.f, f32 deadZone = 0.05f, TimeStep deltaTime = Time::DeltaTime());

        Ref<Camera> GetCamera() const override;

    private:
        Ref<OrthographicCamera> _camera;
    };
}

