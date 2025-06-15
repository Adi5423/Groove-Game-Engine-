#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp> // for future uniform helpers

namespace Groove {

    class Shader {
    public:
        // Construct from GLSL source strings
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // uniform setters (optional, for later)
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        uint32_t CompileShader(uint32_t type, const std::string& source);
        uint32_t CreateShaderProgram(const std::string& vertSrc, const std::string& fragSrc);

    private:
        uint32_t m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    };

}
