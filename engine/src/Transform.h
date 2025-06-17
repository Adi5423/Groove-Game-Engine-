#pragma once  
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtx/euler_angles.hpp> // Include the correct header for Euler angles  

namespace Groove {  

    struct Transform {  
        glm::vec3 Position{ 0.0f };  
        glm::vec3 Rotation{ 0.0f }; // Euler angles in degrees  
        glm::vec3 Scale{ 1.0f };  

        glm::mat4 GetMatrix() const {  
            glm::mat4 T = glm::translate(glm::mat4(1.0f), Position);  
            glm::mat4 R = glm::eulerAngleYXZ(  
                glm::radians(Rotation.y),  
                glm::radians(Rotation.x),  
                glm::radians(Rotation.z)  
            );  
            glm::mat4 S = glm::scale(glm::mat4(1.0f), Scale);  
            return T * R * S;  
        }  
    };  

}
