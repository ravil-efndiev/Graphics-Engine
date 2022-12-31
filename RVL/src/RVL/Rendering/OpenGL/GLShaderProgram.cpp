#include "GLShaderProgram.hpp"

#include <Rvlglpch.hpp>
#include "Core/Utils/Files.hpp"

namespace rvl
{
    GLShaderProgram::GLShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        _vertexShaderSource = utils::GetTextFromFile(vertexShaderPath);
        _fragmentShaderSource = utils::GetTextFromFile(fragmentShaderPath);

        CreateShaders();
    }

    GLShaderProgram::~GLShaderProgram()
    {
        glDetachShader(_programId, _vertexShaderId);
        glDetachShader(_programId, _fragmentShaderId);

        glDeleteProgram(_programId);
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

    void GLShaderProgram::Use()
    {
        glUseProgram(_programId);
    }
}
