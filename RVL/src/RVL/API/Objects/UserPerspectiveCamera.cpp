#include "UserPerspectiveCamera.hpp"
#include <API/Time.hpp>
#include <API/Input.hpp>

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

    void UserPerspectiveCamera::Move(Direction direction, float speed, TimeStep dt)
    {
        switch (direction)
        {
            case Direction::Forward:
                _camera->_position += _camera->_forward * speed * (float)dt;
                break;

            case Direction::Back:
                _camera->_position -= _camera->_forward * speed * (float)dt;
                break;

            case Direction::Left:
                _camera->_position += _camera->_right * speed * (float)dt;
                break;   

            case Direction::Right:
                _camera->_position -= _camera->_right * speed * (float)dt;
                break;

            case Direction::ForwardHorizontal:
                _camera->_position += glm::vec3(_camera->_forward.x, 0.f, _camera->_forward.z) * speed * (float)dt;
                break;

            case Direction::BackHorizontal:
                _camera->_position -= glm::vec3(_camera->_forward.x, 0.f, _camera->_forward.z) * speed * (float)dt;
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

    void UserPerspectiveCamera::UpdateControls(ControllerType type, float speed, TimeStep dt)
    {
        if (type == ControllerType::Free) 
        {
            if (Input::IsKeyPressed(Keys::Key_W))
                Move(Direction::Forward, speed);

            if (Input::IsKeyPressed(Keys::Key_S))
                Move(Direction::Back, speed);

            if (Input::IsKeyPressed(Keys::Key_A))
                Move(Direction::Left, speed);
                
            if (Input::IsKeyPressed(Keys::Key_D))
                Move(Direction::Right, speed);
        } 
        else if (type == ControllerType::InPlane) 
        {
            if (Input::IsKeyPressed(Keys::Key_W))
                Move(Direction::ForwardHorizontal, 5.f);

            if (Input::IsKeyPressed(Keys::Key_S))
                Move(Direction::BackHorizontal, 5.f);

            if (Input::IsKeyPressed(Keys::Key_A))
                Move(Direction::Left, 5.f);
                
            if (Input::IsKeyPressed(Keys::Key_D))
                Move(Direction::Right, 5.f);

            if (Input::IsKeyPressed(Keys::Key_Space))
                Position->y += 5.f * dt;

            if (Input::IsKeyPressed(Keys::Key_LeftShift))
                Position->y -= 5.f * dt;

        } 
    }

}
