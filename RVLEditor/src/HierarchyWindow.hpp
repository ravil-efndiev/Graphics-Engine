#pragma once
#include <RVL.hpp>

namespace Rvl
{
    class HierarchyWindow
    {
    public:
        HierarchyWindow(const Ref<Scene>& scene);

        Entity GetSelected() const;

        void ImGuiRender();
        void SetScene(const Ref<Scene>& scene);


    private:
        Ref<Scene> _scene;
        Entity _selected;
        bool _skip = false, _openPopup = false;

        void Hierarchy(const std::vector<Entity>& entities, int pid);
        void CreateEntityPopup(const std::string& name, Entity parent);
    };
}

