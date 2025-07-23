// engine/src/Window.hpp
#pragma once
#include <string>
#include <functional>
#include <GLFW/glfw3.h>    // for GLFWwindow

namespace Groove {

    class Event; // forward

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(int width, int height, const std::string& title);
        ~Window();

        void OnUpdate();

        int  GetWidth()  const { return m_Width; }
        int  GetHeight() const { return m_Height; }
        void* GetNativeWindow() const { return m_Window; }

        // ← Add these:
        void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }
        void GetCursorPos(double& x, double& y) const { glfwGetCursorPos(m_Window, &x, &y); }

    private:
        void Init(int width, int height, const std::string& title);
        void Shutdown();

        GLFWwindow* m_Window = nullptr;
        std::string        m_Title;
        int                m_Width, m_Height;

        EventCallbackFn    m_EventCallback;   // ← store the callback
    };

}
