#include "UserPerspectiveCamera.hpp"
#include <API/Time.hpp>

namespace Rvl
{
    Ref<UserPerspectiveCamera> UserPerspectiveCamera::New(const glm::vec3& position, float fov)
    {
        return NewRef<UserPerspectiveCamera>(position, fov);
    }

    UserPerspectiveCamera::UserPerspectiveCamera(const glm::vec3& position, float fov)
    {
        _camera = NewRef<PerspectiveCamera>(position, fov);

        Position = Property<glm::vec3>
        (
            &_camera->_position,
            GET { return _camera->GetPosition(); },
            SET { _camera->SetPosition(value); }
        );
    }

    UserPerspectiveCamera::~UserPerspectiveCamera() {}
    
    Ref<Camera> UserPerspectiveCamera::GetCamera() const
    {
        return _camera;
    }

    void UserPerspectiveCamera::Move(Direction direction, float speed)
    {
        switch (direction)
        {
            case Direction::Forward:
                _camera->_position += _camera->_forward * speed * (float)Time::DeltaTime();
                break;

            case Direction::Back:
                _camera->_position -= _camera->_forward * speed * (float)Time::DeltaTime();
                break;

            case Direction::Left:
                _camera->_position += _camera->_right * speed * (float)Time::DeltaTime();
                break;   

            case Direction::Right:
                _camera->_position -= _camera->_right * speed * (float)Time::DeltaTime();
                break;

            case Direction::ForwardHorizontal:
                _camera->_position += glm::vec3(_camera->_forward.x, 0.f, _camera->_forward.z) * speed * (float)Time::DeltaTime();
                break;

            case Direction::BackHorizontal:
                _camera->_position -= glm::vec3(_camera->_forward.x, 0.f, _camera->_forward.z) * speed * (float)Time::DeltaTime();
                break;
        }
    }

    void UserPerspectiveCamera::Rotate(float x, float y, float z)
    {
        _camera->Rotate(x, y, z);
        _camera->ResetRotation();
    }

    glm::vec3 UserPerspectiveCamera::GetRotationAngles() const
    {
        return _camera->_vecRotation;
    }

}
