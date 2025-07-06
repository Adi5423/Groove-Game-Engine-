#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "../Utils/Logger.h" 

namespace Groove {

    static int GetUniformLocation(uint32_t program, const std::string& name) {
        int loc = glGetUniformLocation(program, name.c_str());
        if (loc == -1)
            std::cerr << "[Shader] Warning: uniform '" << name << "' not found!\n";
        return loc;
    }

    Shader::Shader(const std::string& vertSrc, const std::string& fragSrc) {
        m_RendererID = CreateShaderProgram(vertSrc, fragSrc);
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::string errorMessage = "Shader Compilation Failed:\n" + std::string(infoLog);
            Logger::Error(errorMessage);
        }
        return id;
    }

    uint32_t Shader::CreateShaderProgram(const std::string& vs, const std::string& fs) {
        uint32_t program = glCreateProgram();
        uint32_t v = CompileShader(GL_VERTEX_SHADER, vs);
        uint32_t f = CompileShader(GL_FRAGMENT_SHADER, fs);

        glAttachShader(program, v);
        glAttachShader(program, f);
        glLinkProgram(program);

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            std::string msg(length, ' ');
            glGetProgramInfoLog(program, length, &length, &msg[0]);
            std::cerr << "[Shader] Link error: " << msg << "\n";
        }

        glDeleteShader(v);
        glDeleteShader(f);
        return program;
    }

    void Shader::Bind() const { glUseProgram(m_RendererID); }
    void Shader::Unbind() const { glUseProgram(0); }

    void Shader::SetUniform1i(const std::string& name, int value) {
        glUniform1i(GetUniformLocation(m_RendererID, name), value);
    }

    void Shader::SetUniform1f(const std::string& name, float value) {
        glUniform1f(GetUniformLocation(m_RendererID, name), value);
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
        glUniformMatrix4fv(GetUniformLocation(m_RendererID, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
