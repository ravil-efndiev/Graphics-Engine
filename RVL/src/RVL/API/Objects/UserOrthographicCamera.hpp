#ifndef RVL_USERORTHOGRAPHICCAMERA_HPP
#define RVL_USERORTHOGRAPHICCAMERA_HPP

#include "Entity.hpp"
#include <Rvlpch.hpp>

namespace rvl
{
    class OrthographicCamera;

    class UserOrthographicCamera
    {
    friend class RvlScene;
    private:
        // must not be changed from a friend class
        int _zoom;

        // must not be changed from a friend class
        Vector2f _position;

        std::function<void()> _onPositionChange;

        std::shared_ptr<OrthographicCamera> _camera;

    public:
        Property<Vector2f> Position;

        UserOrthographicCamera(const Vector2f& position = {0.f, 0.f}, int zoom = 50);
        ~UserOrthographicCamera();

        int Zoom() const;
        void SetZoom(int zoom);
    };
}

#endif
