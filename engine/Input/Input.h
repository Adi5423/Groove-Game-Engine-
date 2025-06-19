#pragma once

#include <GLFW/glfw3.h>

namespace Groove {
    class Input {
    public:
        static void Init(GLFWwindow* window);

        static bool IsKeyPressed(int key);
        static bool IsMouseButtonPressed(int button);

        static void  GetMousePosition(double& x, double& y);
        static void  GetMouseDelta(double& dx, double& dy);  // NEW
    };
}
