// engine/src/Window.cpp
#include "Window.hpp"
#include "../Utils/Logger.hpp"

// pull in all the concrete event types
#include "Event.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"
#include "ApplicationEvent.hpp"

#include <GLFW/glfw3.h>

namespace Groove {

    Window::Window(int width, int height, const std::string& title)
        : m_Width(width), m_Height(height), m_Title(title)
    {
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
        glfwSwapInterval(1);
        glfwSetWindowUserPointer(m_Window, this);

        // -- Key events --
        glfwSetKeyCallback(m_Window, [](GLFWwindow* wnd, int key, int sc, int action, int mods) {
            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(wnd));
            if (!win->m_EventCallback) return;
            if (action == GLFW_PRESS) {
                KeyPressedEvent e(key, 0);
                win->m_EventCallback(e);
            }
            else if (action == GLFW_RELEASE) {
                KeyReleasedEvent e(key);
                win->m_EventCallback(e);
            }
            else if (action == GLFW_REPEAT) {
                KeyPressedEvent e(key, 1);
                win->m_EventCallback(e);
            }
            });

        // -- Mouse button events --
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* wnd, int button, int action, int mods) {
            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(wnd));
            if (!win->m_EventCallback) return;
            if (action == GLFW_PRESS) {
                MouseButtonPressedEvent e(button);
                win->m_EventCallback(e);
            }
            else {
                MouseButtonReleasedEvent e(button);
                win->m_EventCallback(e);
            }
            });

        // -- Mouse moved --
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* wnd, double x, double y) {
            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(wnd));
            if (!win->m_EventCallback) return;
            MouseMovedEvent e((float)x, (float)y);
            win->m_EventCallback(e);
            });

        // -- Window resize --
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* wnd, int w, int h) {
            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(wnd));
            if (!win->m_EventCallback) return;
            WindowResizeEvent e(w, h);
            win->m_EventCallback(e);
            });

        // -- Window close --
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* wnd) {
            auto* win = static_cast<Window*>(glfwGetWindowUserPointer(wnd));
            if (!win->m_EventCallback) return;
            WindowCloseEvent e;
            win->m_EventCallback(e);
            });
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

} // namespace Groove
