add_library(Engine STATIC
    src/Engine.cpp
    src/Window.cpp
    src/TimeStep.h        # header only, optional to list
    Utils/Logger.cpp
    Input/Input.cpp
    Renderer/Renderer.cpp
    Renderer/Shader.cpp
 "Renderer/ImGuiLayer.cpp")


target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Input
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(Engine
    PUBLIC
        glfw
        glad::glad
        glm::glm
        imgui::imgui
)
