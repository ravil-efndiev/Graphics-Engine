#include "UserOrthographicCamera.hpp"

#include <Rendering/Renderer/OrthographicCamera.hpp>

namespace rvl
{
    Ref<UserOrthographicCamera> UserOrthographicCamera::Create(const Vector2f &position, int zoom)
    {
        return std::make_shared<UserOrthographicCamera>(position, zoom);
    }

    UserOrthographicCamera::UserOrthographicCamera(const Vector2f &position, int zoom)
    {
        _position = position;
        _zoom = zoom;

        Position = 
        {
            &_position,
            [this]() -> const Vector2f&
            {
                return _position;
            },
            [this](const Vector2f& value)
            {
                _position = value;
                _camera->SetPosition({_position.X(), _position.Y(), 0.f});
            }
        };

        _camera = std::make_shared<OrthographicCamera>(glm::vec3(_position.X(), _position.Y(), 0), zoom);

        _position.SetOnChangeCallback(
            [this]()
            {
                _camera->SetPosition({_position.X(), _position.Y(), 0.f});
            }
        );

    }

    UserOrthographicCamera::~UserOrthographicCamera() {}

    int UserOrthographicCamera::Zoom() const
    {
        return _zoom;
    }

    void UserOrthographicCamera::SetZoom(int zoom)
    {
        _zoom = zoom;
        _camera->SetZoom(_zoom);
    }
}
