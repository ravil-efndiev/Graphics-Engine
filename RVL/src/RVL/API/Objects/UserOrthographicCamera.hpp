#ifndef RVL_USERORTHOGRAPHICCAMERA_HPP
#define RVL_USERORTHOGRAPHICCAMERA_HPP

#include <Core/Core.hpp>
#include <Rendering/Renderer/OrthographicCamera.hpp>

namespace rvl
{
    class UserOrthographicCamera
    {
    public:
        static Ref<UserOrthographicCamera> Create(const glm::vec2& position = {0.f, 0.f}, float zoom = 1.f);

        UserOrthographicCamera(const glm::vec2& position = {0.f, 0.f}, float zoom = 1.f);
        ~UserOrthographicCamera();

        float GetZoom() const;
        void SetZoom(float zoom);

        void SetPosition(const glm::vec2& position);
        glm::vec2 GetPosition() const;

        void SetRotationZ(float rotation);
        float GetRotationZ() const;

        // Debug method: increases or decreases camera zoom whene + or - buttons are pressed
        void UpdateZoomChange();

        // Debug method: moves camera on arrow keys
        void UpdateMovement(float speed);

        Ref<OrthographicCamera> GetCamera();

    private:
        Ref<OrthographicCamera> _camera;
    };
}

#endif
