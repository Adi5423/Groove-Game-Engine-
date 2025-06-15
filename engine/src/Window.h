// engine/src/Window.h
#pragma once

#include <string>

struct GLFWwindow;

namespace Groove {

    class Window {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void OnUpdate(); // Poll events + swap buffers

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

        void* GetNativeWindow() const { return m_Window; }

    private:
        void Init(int width, int height, const std::string& title);
        void Shutdown();

    private:
        GLFWwindow* m_Window;
        std::string m_Title;
        int m_Width, m_Height;
    };

}
