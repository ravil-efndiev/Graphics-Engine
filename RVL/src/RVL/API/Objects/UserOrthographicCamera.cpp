#include "UserOrthographicCamera.hpp"

#include <Rendering/Renderer/OrthographicCamera.hpp>

#include <API/Math/Math.hpp>
#include <API/Input.hpp>

namespace rvl
{
    Ref<UserOrthographicCamera> UserOrthographicCamera::Create(const glm::vec2 &position, float zoom)
    {
        return std::make_shared<UserOrthographicCamera>(position, zoom);
    }

    UserOrthographicCamera::UserOrthographicCamera(const glm::vec2& position, float zoom)
    {
        _camera = NewRef<OrthographicCamera>(glm::vec3(position, 0.f), zoom);
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

    void UserOrthographicCamera::Follow(const Ref<Entity>& entity, Axis axis, bool smooth, float smoothSpeed, float deadZone, TimeStep deltaTime)
    {
        float x = _camera->GetPosition().x, y = _camera->GetPosition().y;

        if (static_cast<bool>(axis & Axis::Horizontal))
            x = smooth ? Math::Lerp(_camera->GetPosition().x, entity->transform->Position.x, smoothSpeed * deltaTime, deadZone) : entity->transform->Position.x;
        
        if (static_cast<bool>(axis & Axis::Vertical))
            y = smooth ? Math::Lerp(_camera->GetPosition().y, entity->transform->Position.y, smoothSpeed * deltaTime, deadZone) : entity->transform->Position.y;

        glm::vec3 pos = glm::vec3(x, y, 0.f);

        _camera->SetPosition(pos);
    }
 
    Ref<OrthographicCamera> UserOrthographicCamera::GetCamera()
    {
        return _camera;
    }
}
