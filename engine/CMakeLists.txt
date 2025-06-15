add_library(Engine STATIC
    src/Engine.cpp
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Find and link GLFW and GLAD via vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)


target_link_libraries(Engine PUBLIC glfw glad::glad)
