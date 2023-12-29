#pragma once
#include "HierarchyWindow.hpp"

namespace Rvl
{
    class InspectorWindow : public ImGuiWindow
    {
    public:
        InspectorWindow(const std::string& name = "Inspector");

        void SetSelected(Entity entity);
        void ImGuiRender() override;

        void SetName(const std::string& name) override;
        std::string GetName() const override;

    private:
        void AddComponentMenu();

    private:
        std::string _name;
        Entity _selected;
    };
}

