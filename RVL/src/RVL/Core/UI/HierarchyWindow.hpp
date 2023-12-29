#pragma once
#include <RVL.hpp>
#include "ImGuiWindow.hpp"

namespace Rvl
{
    class HierarchyWindow : public ImGuiWindow
    {
    public:
        HierarchyWindow(const Ref<Scene>& scene, const std::string& name = "Hierarchy");

        Entity GetSelected() const;

        void ImGuiRender() override;
        void SetScene(const Ref<Scene>& scene);

        void SetName(const std::string& name) override;
        std::string GetName() const override;

    private:
        Ref<Scene> _scene;
        Entity _selected;
        bool _skip = false, _openPopup = false;
        std::string _name;

        void Hierarchy(const std::vector<Entity>& entities, int pid);
        void CreateEntityPopup(const std::string& name, Entity parent);
    };
}

