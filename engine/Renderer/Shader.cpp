#include "Shader.h"
#include <glad/glad.h>
#include <iostream>

namespace Groove {

    static int GetUniformLocation(uint32_t program, const std::string& name) {
        int location = glGetUniformLocation(program, name.c_str());
        if (location == -1)
            std::cerr << "[Shader] Warning: uniform '" << name << "' doesn't exist!\n";
        return location;
    }

    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
        m_RendererID = CreateShaderProgram(vertexSrc, fragmentSrc);
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::string message(length, ' ');
            glGetShaderInfoLog(id, length, &length, &message[0]);
            std::cerr << "[Shader] Failed to compile "
                << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                << " shader!\n" << message << "\n";
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    uint32_t Shader::CreateShaderProgram(const std::string& vertSrc, const std::string& fragSrc) {
        uint32_t program = glCreateProgram();
        uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertSrc);
        uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);
        return program;
    }

    void Shader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const {
        glUseProgram(0);
    }

    void Shader::SetUniform1i(const std::string& name, int value) {
        glUniform1i(GetUniformLocation(m_RendererID, name), value);
    }

    void Shader::SetUniform1f(const std::string& name, float value) {
        glUniform1f(GetUniformLocation(m_RendererID, name), value);
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
        glUniformMatrix4fv(GetUniformLocation(m_RendererID, name), 1, GL_FALSE, &matrix[0][0]);
    }

}
