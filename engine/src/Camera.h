#pragma once
#include <glm/glm.hpp>

namespace Groove {

    class Camera {
    public:
        Camera(float fovY, float aspect, float nearClip, float farClip);

        // Set projection matrix parameters
        void SetPerspective(float fovY, float aspect, float nearClip, float farClip);
        // Compute view matrix from position & orientation
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        // Simple orbit or FPS controls:
        void SetPosition(const glm::vec3& pos) { m_Position = pos; }
        void SetTarget(const glm::vec3& target) { m_Target = target; }

    private:
        glm::vec3 m_Position{ 0.0f, 0.0f, 3.0f };
        glm::vec3 m_Target{ 0.0f, 0.0f, 0.0f };
        glm::vec3 m_Up{ 0.0f, 1.0f, 0.0f };

        glm::mat4 m_Projection{ 1.0f };
    };
}
