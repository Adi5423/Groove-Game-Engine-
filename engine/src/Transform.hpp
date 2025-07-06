// engine/src/Transform.hpp
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Groove {

    /**
     * Simple spatial transform (position, rotation in Euler degrees, scale).
     * Produces a 4×4 model matrix: T * R * S
     */
    struct Transform {
        glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation{ 0.0f, 0.0f, 0.0f }; // Euler angles: (pitch=X, yaw=Y, roll=Z)
        glm::vec3 Scale{ 1.0f, 1.0f, 1.0f };

        glm::mat4 GetMatrix() const {
            // Translation
            glm::mat4 T = glm::translate(glm::mat4(1.0f), Position);
            // Rotation Y (yaw), X (pitch), Z (roll)
            glm::mat4 R =
                glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), { 0,1,0 }) *
                glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), { 1,0,0 }) *
                glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), { 0,0,1 });
            // Scale
            glm::mat4 S = glm::scale(glm::mat4(1.0f), Scale);
            return T * R * S;
        }
    };

} // namespace Groove
