#pragma once

#include "ConfigParser.hpp"

namespace Rvl
{
    class EditorApp : public App
    {
    public:
        EditorApp();
        ~EditorApp();

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

        Ref<ConfigParser> _parser;
    };
}
