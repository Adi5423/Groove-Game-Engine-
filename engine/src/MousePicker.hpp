#pragma once

#include <glm/glm.hpp>
#include "Camera.h"
#include "Window.h"

namespace Groove {

    /**
     * Generates a world-space ray from the camera through the current mouse position.
     * @param cam        Your camera (for view/proj matrices and position).
     * @param window     Your Window wrapper (to read mouse coords and viewport size).
     * @return           A pair (origin, direction) in world space.
     */
    static std::pair<glm::vec3, glm::vec3> CastRayFromMouse(Camera& cam, Window& window) {
        // 1) Get normalized device coords
        double mx, my;
        window.GetNativeCursorPos(mx, my);
        int w = window.GetWidth(), h = window.GetHeight();
        float x = (2.0f * (float)mx) / w - 1.0f;
        float y = 1.0f - (2.0f * (float)my) / h;
        glm::vec4 ray_nds = { x, y, -1.0f, 1.0f };

        // 2) Clip → eye coords
        glm::mat4 invProj = glm::inverse(cam.GetProjectionMatrix());
        glm::vec4 ray_eye = invProj * ray_nds;
        ray_eye.z = -1.0f; ray_eye.w = 0.0f;

        // 3) Eye → world
        glm::mat4 invView = glm::inverse(cam.GetViewMatrix());
        glm::vec4 ray_wor4 = invView * ray_eye;
        glm::vec3 ray_wor = glm::normalize(glm::vec3(ray_wor4));

        // 4) Ray origin = camera pos (extract from invView)
        glm::vec3 origin = glm::vec3(glm::inverse(cam.GetViewMatrix())[3]);

        return { origin, ray_wor };
    }

} // namespace Groove
