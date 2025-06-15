#include "Renderer.h"
#include "Shader.h"
#include "../Utils/Logger.h"
#include <glad/glad.h>

// Simple triangle vertices
static float s_TriangleVertices[] = {
     0.0f,  0.5f, 0.0f,  // Top
    -0.5f, -0.5f, 0.0f,  // Bottom left
     0.5f, -0.5f, 0.0f   // Bottom right
};

// Inline GLSL sources
static const char* vertexShaderSrc = R"(
#version 450 core
layout(location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

static const char* fragmentShaderSrc = R"(
#version 450 core
out vec4 FragColor;
void main() {
    FragColor = vec4(0.9, 0.3, 0.4, 1.0);
}
)";

namespace Groove {

    unsigned int Renderer::s_VAO = 0;
    unsigned int Renderer::s_VBO = 0;
    Shader* Renderer::s_Shader = nullptr;

    void Renderer::Init() {
        Logger::Info("Renderer initializing...");

        // Create and bind VAO
        glGenVertexArrays(1, &s_VAO);
        glBindVertexArray(s_VAO);

        // Create VBO
        glGenBuffers(1, &s_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(s_TriangleVertices), s_TriangleVertices, GL_STATIC_DRAW);

        // Enable vertex attribute 0 (position)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // Create shader
        s_Shader = new Shader(vertexShaderSrc, fragmentShaderSrc);
        s_Shader->Bind();

        Logger::Info("Renderer initialized.");
    }

    void Renderer::DrawTriangle() {
        s_Shader->Bind();
        glBindVertexArray(s_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Renderer::Shutdown() {
        delete s_Shader;
        glDeleteVertexArrays(1, &s_VAO);
        glDeleteBuffers(1, &s_VBO);
        Logger::Info("Renderer shutdown.");
    }

}
