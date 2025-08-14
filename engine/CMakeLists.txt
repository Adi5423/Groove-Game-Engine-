add_library(Engine STATIC
    src/Engine.cpp
    src/Window.cpp
    src/TimeStep.hpp
    Utils/Logger.cpp
    Input/Input.cpp
    Renderer/Renderer.cpp
    Renderer/Shader.cpp
    Renderer/ImGuiLayer.cpp
    src/Camera.cpp
    src/Transform.hpp
    src/MousePicker.hpp

    # UI (all editor panels live in Engine, not in imgui lib)
    UI/UIManager.cpp
    UI/Dockspace.cpp
    UI/SceneHierarchyPanel.cpp
    UI/PropertiesPanel.cpp
    UI/StatsPanel.cpp
    UI/ExamplePanel.cpp
)

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Events
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Input
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/UI       # <— add this
)

# Dependencies
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

file(GLOB IMGUI_SRC
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

# Keep imgui clean (no UI/*.cpp here)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC vendor/imgui vendor/imgui/backends)

target_link_libraries(Engine PUBLIC glad glfw imgui)
target_include_directories(Engine PUBLIC vendor/glm)
