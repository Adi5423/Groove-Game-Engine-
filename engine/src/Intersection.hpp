#pragma once

#include <glm/glm.hpp>

namespace Groove {

    // Function to check if a ray intersects an Axis-Aligned Bounding Box (AABB)
    inline bool RayIntersectsAABB(const glm::vec3& origin, const glm::vec3& dir, const glm::vec3& min, const glm::vec3& max, float& t) {
        float tMin = 0.0f;
        float tMax = FLT_MAX;

        for (int i = 0; i < 3; i++) {
            if (dir[i] != 0.0f) {
                float t1 = (min[i] - origin[i]) / dir[i];
                float t2 = (max[i] - origin[i]) / dir[i];

                if (t1 > t2) std::swap(t1, t2);

                tMin = glm::max(tMin, t1);
                tMax = glm::min(tMax, t2);

                if (tMin > tMax) return false;
            } else if (origin[i] < min[i] || origin[i] > max[i]) {
                return false;
            }
        }

        t = tMin;
        return true;
    }

} // namespace Groove
