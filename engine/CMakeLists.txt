add_library(Engine STATIC
    src/Engine.cpp
    src/Window.cpp
    src/TimeStep.h
    Utils/Logger.cpp
    Input/Input.cpp
    Renderer/Renderer.cpp
    Renderer/Shader.cpp
    Renderer/ImGuiLayer.cpp
    src/Camera.cpp 
    src/Transform.hpp
    src/MousePicker.hpp
)

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Input
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer
)

# Dependencies
add_subdirectory(vendor/glad) # <-- Use CMakeLists.txt inside glad
add_subdirectory(vendor/glfw)

file(GLOB IMGUI_SRC
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC vendor/imgui vendor/imgui/backends)



# Link everything
target_link_libraries(Engine
    PUBLIC
        glad
        glfw
        imgui
)
target_include_directories(Engine PUBLIC vendor/glm)
