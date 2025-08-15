#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Groove {

    class Camera {
    public:
        // Constructor
        Camera(float fovY, float aspect, float nearClip, float farClip);

        // Perspective update
        void SetPerspective(float fovY, float aspect, float nearClip, float farClip) {
            m_FovY = fovY;
            m_AspectRatio = aspect;
            m_NearClip = nearClip;
            m_FarClip = farClip;
            m_Projection = glm::perspective(glm::radians(fovY), aspect, nearClip, farClip);
        }

        // New: update only aspect ratio
        void SetAspectRatio(float aspect) {
            m_AspectRatio = aspect;
            m_Projection = glm::perspective(glm::radians(m_FovY), aspect, m_NearClip, m_FarClip);
        }

        void ProcessKeyboard(const glm::vec3& direction, float deltaTime);
        void ProcessMouseMovement(float deltaX, float deltaY, bool constrainPitch = true);

        // Getters
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        float GetPitch() const { return m_Pitch; }
        float GetYaw() const { return m_Yaw; }

        // Camera parameters
        void SetPosition(const glm::vec3& pos) { m_Position = pos; }

    private:
        void UpdateCameraVectors();

        // Euler angles
        float m_Yaw = -90.0f;
        float m_Pitch = 0.0f;

        // Movement options
        float m_MovementSpeed = 5.0f;      // units/sec
        float m_MouseSensitivity = 0.1f;   // degrees/pixel

        // Camera state
        glm::vec3 m_Position;
        glm::vec3 m_Front{ 0.0f, 0.0f, -1.0f };
        glm::vec3 m_Up{ 0.0f, 1.0f,  0.0f };
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp{ 0.0f, 1.0f,  0.0f };

        // Projection parameters
        float m_FovY;
        float m_AspectRatio;
        float m_NearClip;
        float m_FarClip;
        glm::mat4 m_Projection{ 1.0f };
    };

}
