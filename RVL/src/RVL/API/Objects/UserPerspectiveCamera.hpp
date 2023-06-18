#pragma once
#include <Rendering/Renderer/PerspectiveCamera.hpp>
#include "UserCamera.hpp"
#include <API/Property.hpp>

namespace Rvl
{
    enum class Direction
    {
        Forward, ForwardHorizontal, Back, BackHorizontal, Left, Right
    };

    class UserPerspectiveCamera : public UserCamera
    {
    public:
        static Ref<UserPerspectiveCamera> Create(const glm::vec3& position = {0.f, 0.f, 0.f}, float fov = 45.f);

        UserPerspectiveCamera(const glm::vec3& position, float fov);
        ~UserPerspectiveCamera();

        Ref<Camera> GetCamera() const override;

        Property<glm::vec3> Position;

        void Move(Direction direction, float speed);
        void Rotate(float x, float y, float z);

        glm::vec3 GetRotationAngles() const;

    private:
        Ref<PerspectiveCamera> _camera;
    };
}

