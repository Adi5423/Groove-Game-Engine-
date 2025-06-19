#include "Renderer.h"
#include "Shader.h"
#include "../Utils/Logger.h"
#include <glad/glad.h>
#include <Transform.h>
#include <Camera.h>

// Cube: 8 vertices, 36 indices (12 triangles)
static float cubeVerts[] = {
    // positions          
    -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f, -0.5f, 0.5f,-0.5f,
    -0.5f,-0.5f, 0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
};
static unsigned int cubeIndices[] = {
    0,1,2, 2,3,0,  // back face
    4,5,6, 6,7,4,  // front face
    4,5,1, 1,0,4,  // bottom
    6,7,3, 3,2,6,  // top
    4,0,3, 3,7,4,  // left
    1,5,6, 6,2,1   // right
};

// Inline GLSL sources (replace existing ones)
static const char* vertexSrc = R"(
#version 450 core

layout(location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    // Transform into clip space
    gl_Position = u_Proj * u_View * u_Model * vec4(aPos, 1.0);
}
)";

static const char* fragmentSrc = R"(
#version 450 core

out vec4 FragColor;

void main()
{
    // Simple solid color
    FragColor = vec4(0.9, 0.3, 0.4, 1.0);
}
)";


namespace Groove {

    unsigned int Renderer::s_VAO = 0;
    unsigned int Renderer::s_VBO = 0;
    Shader* Renderer::s_Shader = nullptr;


    void Renderer::Init() {
        Logger::Info("Renderer initializing...");
        glEnable(GL_DEPTH_TEST);


        // Create and bind VAO
        // In Init(): generated VAO/VBO/IBO instead of just VBO
        unsigned int IBO;
        glGenVertexArrays(1, &s_VAO);
        glBindVertexArray(s_VAO);

        glGenBuffers(1, &s_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // Enable vertex attribute 0 (position)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // Create shader
        s_Shader = new Shader(vertexSrc, fragmentSrc);
        s_Shader->Bind();

        Logger::Info("Renderer initialized.");
    }

    void Renderer::DrawCube(const Transform& t, const Camera& cam) {
        s_Shader->Bind();
        // set uniforms
        s_Shader->SetUniformMat4f("u_Model", t.GetMatrix());
        s_Shader->SetUniformMat4f("u_View", cam.GetViewMatrix());
        s_Shader->SetUniformMat4f("u_Proj", cam.GetProjectionMatrix());
        glBindVertexArray(s_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::SetCameraPerspective(Camera& cam, float aspect) {
        cam.SetPerspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
    }

    void Renderer::Shutdown() {
        delete s_Shader;
        glDeleteVertexArrays(1, &s_VAO);
        glDeleteBuffers(1, &s_VBO);
        Logger::Info("Renderer shutdown.");
    }


}
