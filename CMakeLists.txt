cmake_minimum_required(VERSION 3.21)
project(Groove)

# toolchain is picked up via CMakePresets.json; do NOT hard‑code here

add_subdirectory(engine)
add_subdirectory(sandbox)