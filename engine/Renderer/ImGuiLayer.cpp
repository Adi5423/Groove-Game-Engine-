#include "ImGuiLayer.h"  
#include "../Utils/Logger.h"  

// ImGui core  
#include <imgui.h>  
// Backend implementations  
#include <imgui_impl_glfw.h>  
#include <imgui_impl_opengl3.h>  

namespace Groove {  

    void ImGuiLayer::Init(GLFWwindow* window) {  
        m_Window = window;  

        IMGUI_CHECKVERSION();  
        ImGui::CreateContext();  
        ImGuiIO& io = ImGui::GetIO();  
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Keyboard controls  
        ImGui::StyleColorsDark();  

        // Initialize Platform/Renderer backends  
        if (!ImGui_ImplGlfw_InitForOpenGL(m_Window, true))  
            Logger::Error("ImGui_ImplGlfw_InitForOpenGL failed!");  
        if (!ImGui_ImplOpenGL3_Init("#version 450"))  
            Logger::Error("ImGui_ImplOpenGL3_Init failed!");  
    }  

    void ImGuiLayer::Begin() {  
        ImGui_ImplOpenGL3_NewFrame();  
        ImGui_ImplGlfw_NewFrame();  
        ImGui::NewFrame();  
    }  

    void ImGuiLayer::End() {  
        ImGui::Render();  
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  
    }  

    void ImGuiLayer::Shutdown() {  
        ImGui_ImplOpenGL3_Shutdown();  
        ImGui_ImplGlfw_Shutdown();  
        ImGui::DestroyContext();  
    }  

}
