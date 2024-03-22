#include <Core/Core.hpp>

namespace Rvl
{
    class GLShaderProgram;
    class ShaderLibrary
    {
    public:
        void Add(const std::string& name, const Ref<GLShaderProgram>& shader);
        Ref<GLShaderProgram> Load(const std::string& name, const std::string& path);
        Ref<GLShaderProgram> Get(const std::string& name);

    private:
        std::unordered_map<std::string, Ref<GLShaderProgram>> _shaders {};
    };

    class StandartShaderLib 
    {
        friend class App;
        public:
            static Ref<GLShaderProgram> Get(const std::string& name);
            
        private:
            static void Init();

            static Ref<ShaderLibrary> _lib;
    };
}

