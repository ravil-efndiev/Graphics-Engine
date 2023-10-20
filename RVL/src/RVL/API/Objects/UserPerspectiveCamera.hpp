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
        static Ref<UserPerspectiveCamera> New(const glm::vec3& position = {0.f, 0.f, 0.f}, float fov = 45.f);

        UserPerspectiveCamera(const glm::vec3& position, float fov);
        ~UserPerspectiveCamera();

        Ref<Camera> GetCamera() const override;

        Property<glm::vec3> Position;

        void Move(Direction direction, float speed, TimeStep dt = Time::DeltaTime());
        void Rotate(float x, float y, float z);

        glm::vec3 GetRotationAngles() const;

        void UpdateControls(ControllerType type, float speed, TimeStep dt = Time::DeltaTime());

    private:
        Ref<PerspectiveCamera> _camera;
    };
}

