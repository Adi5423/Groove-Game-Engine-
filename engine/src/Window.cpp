// engine/src/Window.cpp
#include "Window.h"
#include "../Utils/Logger.h"

#include <GLFW/glfw3.h>

namespace Groove {

    Window::Window(int width, int height, const std::string& title)
        : m_Width(width), m_Height(height), m_Title(title) {
        Init(width, height, title);
    }

    Window::~Window() {
        Shutdown();
    }

    void Window::Init(int width, int height, const std::string& title) {
        Logger::Info("Creating window: " + title);

        if (!glfwInit()) {
            Logger::Error("GLFW Initialization Failed!");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            Logger::Error("Failed to create GLFW window!");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1); // Enable VSync
    }

    void Window::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::Shutdown() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        Logger::Info("Window destroyed and GLFW terminated.");
    }

}
