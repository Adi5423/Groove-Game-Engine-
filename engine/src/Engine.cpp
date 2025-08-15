#include "Engine.hpp"
#include "Window.hpp"
#include "TimeStep.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Utils/Logger.hpp"
#include "../Input/Input.hpp"
#include "../Renderer/ImGuiLayer.hpp"
#include "../UI/UIManager.hpp"
#include "../UI/Dockspace.hpp"
#include "../UI/PrimaryWindow.hpp"
#include "../UI/SceneLoad.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static Groove::Window* s_Window = nullptr;
static Groove::ImGuiLayer* s_ImGuiLayer = nullptr;
static Groove::UIManager* s_UIManager = nullptr;

void Engine::Init() {
    Groove::Logger::Init("Groove.log");
    s_Window = new Groove::Window(1280, 720, "Groove Engine");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Groove::Logger::Error("Failed to initialize GLAD!");
        return;
    }

    Groove::Input::Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));
    Groove::Renderer::Init();

    s_ImGuiLayer = new Groove::ImGuiLayer();
    s_ImGuiLayer->Init(static_cast<GLFWwindow*>(s_Window->GetNativeWindow()));

    s_UIManager = new Groove::UIManager();
    s_UIManager->RegisterPanel(std::make_shared<Groove::Dockspace>());
    s_UIManager->RegisterPanel(std::make_shared<Groove::PrimaryWindow>());

    Groove::SceneLoad::Init();
}

void Engine::Run() {
    GLFWwindow* glfwWin = static_cast<GLFWwindow*>(s_Window->GetNativeWindow());
    float lastTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(glfwWin)) {
        float now = (float)glfwGetTime();
        float dt = now - lastTime;
        lastTime = now;

        Groove::SceneLoad::Update(dt);

        s_ImGuiLayer->Begin();
        s_UIManager->RenderPanels();
        s_ImGuiLayer->End();

        s_Window->OnUpdate();
    }
}

void Engine::Shutdown() {
    Groove::SceneLoad::Shutdown();
    s_ImGuiLayer->Shutdown();
    delete s_ImGuiLayer;
    delete s_UIManager;
    Groove::Renderer::Shutdown();
    delete s_Window;
    Groove::Logger::Shutdown();
}
