#ifndef RVL_GLSHADERPROGRAM_HPP
#define RVL_GLSHADERPROGRAM_HPP

#include <Rvlpch.hpp>

namespace rvl
{
    class GLShaderProgram
    {
    public:
        GLShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~GLShaderProgram();

        void BindAttribute(GLuint index, const std::string& name);

        void Link();
        void Use();

    private:
        std::string _vertexShaderSource;
        std::string _fragmentShaderSource;

        GLuint _programId;
        GLuint _vertexShaderId, _fragmentShaderId;

        int _success;
        char _log[512];

        void CreateShaders();
        void Compile(const char* source, GLuint id);

    };
}

#endif
