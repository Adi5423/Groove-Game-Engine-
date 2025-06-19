#include "Input.h"
#include <GLFW/glfw3.h>
#include <utility>

namespace Groove {
    static double s_LastX = 0.0, s_LastY = 0.0;
    static bool   s_FirstMouse = true;
    static GLFWwindow* s_Window = nullptr;

    void Input::Init(GLFWwindow* window) {
        s_Window = window;
        glfwGetCursorPos(s_Window, &s_LastX, &s_LastY);
    }

    bool Input::IsKeyPressed(int key) {
        return glfwGetKey(s_Window, key) == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(int button) {
        return glfwGetMouseButton(s_Window, button) == GLFW_PRESS;
    }

    void Input::GetMousePosition(double& x, double& y) {
        glfwGetCursorPos(s_Window, &x, &y);
    }

    void Input::GetMouseDelta(double& dx, double& dy) {
        double x, y;
        glfwGetCursorPos(s_Window, &x, &y);
        if (s_FirstMouse) {
            s_LastX = x; s_LastY = y;
            s_FirstMouse = false;
        }
        dx = x - s_LastX;
        dy = s_LastY - y;  // y inverted
        s_LastX = x; s_LastY = y;
    }
}
