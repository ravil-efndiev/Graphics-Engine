#include "GLShaderProgram.hpp"

#include "Core/Utils/Files.hpp"

namespace rvl
{
    GLShaderProgram::GLShaderProgram() {}

    GLShaderProgram::GLShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        Load(vertexShaderPath, fragmentShaderPath);
    }

    GLShaderProgram::~GLShaderProgram()
    {
        glDetachShader(_programId, _vertexShaderId);
        glDetachShader(_programId, _fragmentShaderId);

        glDeleteProgram(_programId);
    }

    void GLShaderProgram::Load(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        if (_vertexShaderId != 0 && _fragmentShaderId != 0)
        {
            glDeleteShader(_vertexShaderId);
            glDeleteShader(_fragmentShaderId);
        }

        _vertexShaderSource = utils::GetTextFromFile(vertexShaderPath);
        _fragmentShaderSource = utils::GetTextFromFile(fragmentShaderPath);

        CreateShaders();
    }

    void GLShaderProgram::LoadSource(const std::string &vertexShaderSoruce, const std::string &fragmentShaderSource)
    {
        if (_vertexShaderId != 0 && _fragmentShaderId != 0)
        {
            glDeleteShader(_vertexShaderId);
            glDeleteShader(_fragmentShaderId);
        }

        _vertexShaderSource = vertexShaderSoruce;
        _fragmentShaderSource = fragmentShaderSource;

        CreateShaders();
    }

    void GLShaderProgram::CreateShaders()
    {
        _programId = glCreateProgram();

        _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        Compile(_vertexShaderSource.c_str(), _vertexShaderId);
        Compile(_fragmentShaderSource.c_str(), _fragmentShaderId);
    }

    void GLShaderProgram::Compile(const char* source, GLuint id)
    {
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        glGetShaderiv(id, GL_COMPILE_STATUS, &_success);
        if (!_success)
        {
            glGetShaderInfoLog(id, 512, nullptr, _log);
            glDeleteShader(id);
            throw Error(std::string("failed to compile shader, more info:\n").append(_log), RVL_INTERNAL_ERROR);
        }   
    }

    void GLShaderProgram::Link()
    {
        glAttachShader(_programId, _vertexShaderId);
        glAttachShader(_programId, _fragmentShaderId);

        glLinkProgram(_programId);

        glGetProgramiv(_programId, GL_LINK_STATUS, &_success);
        if (!_success)
        {
            glGetProgramInfoLog(_programId, 512, nullptr, _log);

            glDeleteShader(_vertexShaderId);
            glDeleteShader(_fragmentShaderId);

            throw Error(std::string("failed to link shader program, more info:\n").append(_log), RVL_INTERNAL_ERROR);
        }

        glValidateProgram(_programId);

        glDeleteShader(_vertexShaderId);
        glDeleteShader(_fragmentShaderId);

    }

    void GLShaderProgram::BindAttribute(GLuint index, const std::string& name)
    {
        glBindAttribLocation(_programId, index, name.c_str());
    }

    void GLShaderProgram::SetUniform(const std::string &name, const glm::mat4 &uniform)
    {
        GLint position = glGetUniformLocation(_programId, name.c_str());
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(uniform));
    }

    void GLShaderProgram::SetUniform(const std::string &name, int uniform)
    {
        GLint position = glGetUniformLocation(_programId, name.c_str());
        glUniform1i(position, uniform);
    }

    void GLShaderProgram::Bind()
    {
        glUseProgram(_programId);
    }

    void GLShaderProgram::Unbind()
    {   
        glUseProgram(0);
    }
}
