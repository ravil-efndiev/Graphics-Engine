#include "UserOrthographicCamera.hpp"

#include <Rendering/Renderer/OrthographicCamera.hpp>

namespace rvl
{
    UserOrthographicCamera::UserOrthographicCamera(const Vector2f &position, int zoom)
        : _position(position), _zoom(zoom)
    {
        _camera = std::make_shared<OrthographicCamera>(glm::vec3(_position.X(), _position.Y(), 1), _zoom);
    }

    UserOrthographicCamera::~UserOrthographicCamera() {}

    Vector2f UserOrthographicCamera::Position() const
    {
        return _position;
    }

    int UserOrthographicCamera::Zoom() const
    {
        return _zoom;
    }

    void UserOrthographicCamera::SetPosition(const Vector2f &position)
    {
        _position = position;
        _camera->SetPosition({_position.X(), _position.Y(), 1});
    }

    void UserOrthographicCamera::SetZoom(int zoom)
    {
        _zoom = zoom;
        _camera->SetZoom(_zoom);
    }
}
