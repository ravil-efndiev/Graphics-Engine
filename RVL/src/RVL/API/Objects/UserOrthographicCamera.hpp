#ifndef RVL_USERORTHOGRAPHICCAMERA_HPP
#define RVL_USERORTHOGRAPHICCAMERA_HPP

#include <API/Math/math.hpp>
#include <Rvlpch.hpp>

namespace rvl
{
    class OrthographicCamera;

    class UserOrthographicCamera
    {
    friend class RvlScene;

    public:
        UserOrthographicCamera(const Vector2f& position = {0.f, 0.f}, int zoom = 100);
        ~UserOrthographicCamera();

        Vector2f Position() const;
        int Zoom() const;

        void SetPosition(const Vector2f& position);
        void SetZoom(int zoom);

    private:
        // must not be changed from a friend class
        Vector2f _position;

        // must not be changed from a friend class
        int _zoom;

        std::shared_ptr<OrthographicCamera> _camera;
    };
}

#endif
