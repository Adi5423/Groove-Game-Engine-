add_library(Engine STATIC
    src/Engine.cpp
    src/Window.cpp                 # <-- Add this
    Utils/Logger.cpp
    Input/Input.cpp Input/Input.h
    src/Window.h                   # <-- Header (optional)
)


target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/Input
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(Engine
    PUBLIC
        glfw
        glad::glad
)
