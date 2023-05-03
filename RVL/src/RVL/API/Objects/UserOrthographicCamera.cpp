#include "UserOrthographicCamera.hpp"

#include <Rendering/Renderer/OrthographicCamera.hpp>

#include <API/Input.hpp>
#include <API/Time.hpp>

namespace rvl
{
    Ref<UserOrthographicCamera> UserOrthographicCamera::Create(const glm::vec2 &position, float zoom)
    {
        return std::make_shared<UserOrthographicCamera>(position, zoom);
    }

    UserOrthographicCamera::UserOrthographicCamera(const glm::vec2& position, float zoom)
    {
        _camera = CreateRef<OrthographicCamera>(glm::vec3(position, 0.f), zoom);
    }

    UserOrthographicCamera::~UserOrthographicCamera() {}

    float UserOrthographicCamera::GetZoom() const
    {
        return _camera->GetZoom();
    }

    void UserOrthographicCamera::SetZoom(float zoom)
    {
        _camera->SetZoom(zoom);
    }

    void UserOrthographicCamera::SetPosition(const glm::vec2& position)
    {
        _camera->SetPosition(glm::vec3(position.x, position.y, 0.f));
    }
    
    glm::vec2 UserOrthographicCamera::GetPosition() const
    {
        return glm::vec2(_camera->GetPosition().x, _camera->GetPosition().y);
    }

    void UserOrthographicCamera::SetRotationZ(float rotation)
    {
        _camera->SetRotationZ(rotation);
    }

    float UserOrthographicCamera::GetRotationZ() const
    {
        return _camera->GetRotationZ();
    }

    void UserOrthographicCamera::UpdateZoomChange()
    {
        if (Input::IsKeyPressed(Keys::RVL_KEY_EQUAL))
        {
            _camera->SetZoom(_camera->GetZoom() - 0.25f);
        }
        if (Input::IsKeyPressed(Keys::RVL_KEY_MINUS))
        {
            _camera->SetZoom(_camera->GetZoom() + 0.25f);
        }
    }

    void UserOrthographicCamera::UpdateMovement(float speed)
    {
        if (Input::IsKeyPressed(Keys::RVL_KEY_LEFT))
            _camera->SetPosition({_camera->GetPosition().x - speed * Time::DeltaTime(), _camera->GetPosition().y, 0.f});

        if (Input::IsKeyPressed(Keys::RVL_KEY_RIGHT))
            _camera->SetPosition({_camera->GetPosition().x + speed * Time::DeltaTime(), _camera->GetPosition().y, 0.f});

        if (Input::IsKeyPressed(Keys::RVL_KEY_UP))
            _camera->SetPosition({_camera->GetPosition().x, _camera->GetPosition().y + speed * Time::DeltaTime(), 0.f});

        if (Input::IsKeyPressed(Keys::RVL_KEY_DOWN))
            _camera->SetPosition({_camera->GetPosition().x, _camera->GetPosition().y - speed * Time::DeltaTime(), 0.f});
    }


    Ref<OrthographicCamera> UserOrthographicCamera::GetCamera()
    {
        return _camera;
    }
}
