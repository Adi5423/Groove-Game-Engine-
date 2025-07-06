// engine/src/Window.h
#pragma once
#include <string>
#include <GLFW/glfw3.h> // Ensure GLFW is included

struct GLFWwindow;

namespace Groove {

    class Window {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void OnUpdate();

        int GetWidth()  const { return m_Width; }
        int GetHeight() const { return m_Height; }

        void* GetNativeWindow() const { return m_Window; }

        // Added method to retrieve cursor position
        void GetNativeCursorPos(double& x, double& y) const {
            glfwGetCursorPos(m_Window, &x, &y);
        }

    private:
        void Init(int width, int height, const std::string& title);
        void Shutdown();

        GLFWwindow* m_Window;
        std::string m_Title;
        int m_Width, m_Height;
    };

} // namespace Groove
