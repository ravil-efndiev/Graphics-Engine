#ifndef SB_GAME_HPP
#define SB_GAME_HPP

#include <RVL.hpp>

namespace rvl
{
    class MapEditorApp : public RvlApp
    {
    public:
        MapEditorApp();
        ~MapEditorApp();

    private:
        void Start() override;
        void Update() override;

        // UI Methods 
        void DockspaceAndMenu();
        void ProjectWindow();
        void ProjectOpenWindow();
        void SetDefaults();
        
    private:
        std::string _prjfileText;

        std::vector<std::vector<std::string>> _projectLineTokens;
    };
}

#endif
