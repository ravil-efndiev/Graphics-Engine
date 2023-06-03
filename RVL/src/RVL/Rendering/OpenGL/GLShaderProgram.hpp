#ifndef RVL_GLSHADERPROGRAM_HPP
#define RVL_GLSHADERPROGRAM_HPP

#include <Rvlpch.hpp>
#include <Rvlglpch.hpp>

namespace Rvl
{
    class GLShaderProgram
    {
    public:
        GLShaderProgram();
        GLShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~GLShaderProgram();

        void Load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        void LoadSource(const std::string& vertexShaderSoruce, const std::string& fragmentShaderSource);

        void BindAttribute(GLuint index, const std::string& name);
        
        void SetUniformMat4(const std::string &name, const glm::mat4& uniform);
        void SetUniformVec4(const std::string &name, const glm::vec4& uniform);
        void SetUniformInt(const std::string &name, int uniform);
        void SetUniformIntArr(const std::string &name, int* arr, size_t count);

        void Link();

        void Bind();
        void Unbind();

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
