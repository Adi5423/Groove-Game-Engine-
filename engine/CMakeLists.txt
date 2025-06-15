add_library(Engine STATIC
    src/Engine.cpp
    Utils/Logger.cpp
)

target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(Engine
    PUBLIC
        glfw
        glad::glad
)
