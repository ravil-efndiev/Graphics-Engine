#include "UserOrthographicCamera.hpp"

#include <Rendering/Renderer/OrthographicCamera.hpp>

#include <API/Math/Math.hpp>
#include <API/Input.hpp>

namespace Rvl
{
    Ref<UserOrthographicCamera> UserOrthographicCamera::New(const glm::vec2& position, f32 zoom)
    {
        return NewRef<UserOrthographicCamera>(position, zoom);
    }

    UserOrthographicCamera::UserOrthographicCamera(const glm::vec2& position, f32 zoom)
    {
        _camera = NewRef<OrthographicCamera>(glm::vec3(position, 0.f), zoom);
    }

    UserOrthographicCamera::~UserOrthographicCamera() {}

    f32 UserOrthographicCamera::GetZoom() const
    {
        return _camera->GetZoom();
    }

    void UserOrthographicCamera::SetZoom(f32 zoom)
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

    void UserOrthographicCamera::SetRotationZ(f32 rotation)
    {
        _camera->SetRotationZ(rotation);
    }

    f32 UserOrthographicCamera::GetRotationZ() const
    {
        return _camera->GetRotationZ();
    }

    void UserOrthographicCamera::Follow(Transform* transform, Axis axis, bool smooth, f32 smoothSpeed, f32 deadZone, TimeStep deltaTime)
    {
        f32 x = _camera->GetPosition().x, y = _camera->GetPosition().y;

        if (static_cast<bool>(axis & Axis::Horizontal))
            x = smooth ? Math::Lerp(_camera->GetPosition().x, transform->Position.x, smoothSpeed * deltaTime, deadZone) : transform->Position.x;
        
        if (static_cast<bool>(axis & Axis::Vertical))
            y = smooth ? Math::Lerp(_camera->GetPosition().y, transform->Position.y, smoothSpeed * deltaTime, deadZone) : transform->Position.y;

        glm::vec3 pos = glm::vec3(x, y, 0.f);

        _camera->SetPosition(pos);
    }
 
    Ref<Camera> UserOrthographicCamera::GetCamera() const
    {
        return _camera;
    }
}
