#pragma once

#include <GLFW/glfw3.h> // for GLFWwindow

struct ImGuiContext; // forward

namespace Groove {

    class ImGuiLayer {
    public:
        void Init(GLFWwindow* window);
        void Begin();
        void End();
        void Shutdown();

    private:
        GLFWwindow* m_Window = nullptr;
    };

}
