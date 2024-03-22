#pragma once
#include <Rendering/Renderer/PerspectiveCamera.hpp>
#include "UserCamera.hpp"
#include <API/Property.hpp>
#include <API/Time.hpp>

namespace Rvl
{
    enum class Direction
    {
        Forward, ForwardHorizontal, Back, BackHorizontal, Left, Right
    };

    enum class ControllerType
    {
        Free, InPlane
    };

    class UserPerspectiveCamera : public UserCamera
    {
    public:
        static Ref<UserPerspectiveCamera> New(const glm::vec3& position = {0.f, 0.f, 0.f}, f32 fov = 45.f);

        UserPerspectiveCamera(const glm::vec3& position, f32 fov);
        ~UserPerspectiveCamera();

        Ref<Camera> GetCamera() const override;

        Property<glm::vec3> Position;

        void Move(Direction direction, f32 speed, TimeStep dt = Time::DeltaTime());
        void Rotate(f32 x, f32 y, f32 z);

        glm::vec3 GetRotationAngles() const;

        void UpdateControls(ControllerType type, f32 speed, TimeStep dt = Time::DeltaTime());
        void UpdateCursorRotation(f32 speed);

    private:
        glm::vec2 _rotation {0.f};
        Ref<PerspectiveCamera> _camera;
    };
}

