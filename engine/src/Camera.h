#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Groove {

    class Camera {
    public:
        // Declare the constructor (no body here)
        Camera(float fovY, float aspect, float nearClip, float farClip);

        // call each frame
        public:  
            // Set perspective projection matrix  
            void SetPerspective(float fovY, float aspect, float nearClip, float farClip) {  
                m_Projection = glm::perspective(fovY, aspect, nearClip, farClip);  
            }
        void ProcessKeyboard(const glm::vec3& direction, float deltaTime);
        void ProcessMouseMovement(float deltaX, float deltaY, bool constrainPitch = true);

        // getters
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        float GetPitch() const { return m_Pitch; }
        float GetYaw() const {
            return m_Yaw;
        }

        // camera parameters
        void   SetPosition(const glm::vec3& pos) { m_Position = pos; }

    private:
        void   UpdateCameraVectors();

        // Euler angles
        float  m_Yaw = -90.0f;
        float  m_Pitch = 0.0f;

        // options
        float  m_MovementSpeed = 5.0f;    // units/sec
        float  m_MouseSensitivity = 0.1f;    // degrees/pixel

        // camera axes
        glm::vec3 m_Position;
        glm::vec3 m_Front{ 0.0f, 0.0f, -1.0f };
        glm::vec3 m_Up{ 0.0f, 1.0f,  0.0f };
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp{ 0.0f, 1.0f,  0.0f };

        glm::mat4 m_Projection{ 1.0f };
    };

}
