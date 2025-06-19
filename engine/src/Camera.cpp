#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Groove {

    // Define the constructor here
    Camera::Camera(float fovY, float aspect, float nearClip, float farClip)
        : m_Position(0.0f, 0.0f, 3.0f) // Default camera position set to (0,0,3)
    {
        m_Projection = glm::perspective(glm::radians(fovY), aspect, nearClip, farClip);
        UpdateCameraVectors();
    }

    void Camera::ProcessKeyboard(const glm::vec3& dir, float deltaTime) {
        float velocity = m_MovementSpeed * deltaTime;
        m_Position += m_Front * dir.z * velocity;
        m_Position += m_Right * dir.x * velocity;
        m_Position += m_Up * dir.y * velocity;
    }

    void Camera::ProcessMouseMovement(float deltaX, float deltaY, bool constrainPitch) {
        deltaX *= m_MouseSensitivity;
        deltaY *= m_MouseSensitivity;
        m_Yaw += deltaX;
        m_Pitch += deltaY;
        if (constrainPitch) {
            if (m_Pitch > 89.0f) m_Pitch = 89.0f;
            if (m_Pitch < -89.0f) m_Pitch = -89.0f;
        }
        UpdateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return m_Projection;
    }

    void Camera::UpdateCameraVectors() {  
        glm::vec3 front{0.0f, 0.0f, 0.0f}; // Initialize the local variable 'front'  
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));  
        front.y = sin(glm::radians(m_Pitch));  
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));  
        m_Front = glm::normalize(front);  
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));  
    }

}
