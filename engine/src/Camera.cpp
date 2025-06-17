#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Groove {

    Camera::Camera(float fovY, float aspect, float nearClip, float farClip) {
        SetPerspective(fovY, aspect, nearClip, farClip);
    }

    void Camera::SetPerspective(float fovY, float aspect, float nearClip, float farClip) {
        m_Projection = glm::perspective(glm::radians(fovY), aspect, nearClip, farClip);
    }

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(m_Position, m_Target, m_Up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return m_Projection;
    }

}

