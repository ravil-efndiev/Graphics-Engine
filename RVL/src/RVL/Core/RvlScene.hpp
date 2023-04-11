#ifndef RVL_RVLSCENE_HPP
#define RVL_RVLSCENE_HPP

#include <API/Objects/Rectangle.hpp>
#include <Rvlpch.hpp>

namespace rvl
{
    class PerspectiveCamera;
    class OrthographicCamera;

    class RvlScene
    {
    friend class RvlApp;

    public:
        RvlScene();
        virtual ~RvlScene();

        virtual void Start();
        virtual void Update();
        virtual void Render();
        
        virtual void SetCamera(const std::shared_ptr<OrthographicCamera>& cam);


    protected:
        std::shared_ptr<PerspectiveCamera> _camera3d;
        std::shared_ptr<OrthographicCamera> _camera2d;

    private:
        void MakeScene(); // can be accessed by RvlApp parent but not RvlApp children
    };
}

#endif
