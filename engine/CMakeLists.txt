add_library(Engine STATIC
    src/Engine.cpp
    src/Window.cpp                 
    Utils/Logger.cpp
    Input/Input.cpp Input/Input.h
    src/Window.h                   # <-- Header (optional)
    Renderer/Renderer.cpp Renderer/Renderer.h
    Renderer/Shader.cpp Renderer/Shader.h
)


target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/Input
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderer
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(Engine
    PUBLIC
        glfw
        glad::glad
        glm::glm
)
