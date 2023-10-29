#pragma once
#include <RVL.hpp>

namespace Rvl
{
    class HierarchyWindow
    {
    public:
        HierarchyWindow(Scene& scene);

        Entity GetSelected() const;

        void ImGuiRender();

    private:
        Scene& _scene;
        Entity _selected;
    };
}

