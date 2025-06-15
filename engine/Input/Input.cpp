#include "Input.h"

namespace Groove {

    GLFWwindow* Input::s_Window = nullptr;

    void Input::Init(GLFWwindow* glfwWindow) {
        s_Window = glfwWindow;
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

}
