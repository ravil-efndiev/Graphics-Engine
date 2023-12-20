#pragma once
#include "HierarchyWindow.hpp"

namespace Rvl
{
    class InspectorWindow
    {
    public:
        InspectorWindow();

        void SetSelected(Entity entity);
        void ImGuiRedner();

    private:
        void AddComponentMenu();

        Entity _selected;
    };
}

