#ifndef RVL_RVLSCENE_HPP
#define RVL_RVLSCENE_HPP

#include <API/Primitives/Rectangle.hpp>
#include <Rvlpch.hpp>

namespace rvl
{
    class PerspectiveCamera;

    class RvlScene
    {
    friend class RvlApp;

    public:
        RvlScene();
        virtual ~RvlScene();

        virtual void Start();
        virtual void Update();
        virtual void Render();
        
        virtual void SetCamera(const std::shared_ptr<PerspectiveCamera>& cam);


    protected:
        std::vector<std::shared_ptr<Entity>> _entities;
        std::shared_ptr<PerspectiveCamera> _camera;

        virtual void AddEntity(const std::shared_ptr<Entity>& entity);

    private:
        void MakeScene(); // can be accessed by RvlApp parent but not RvlApp children
    };
}

#endif
