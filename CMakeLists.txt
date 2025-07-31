cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(MyAnchorProject)

set(CMAKE_CXX_STANDARD 17)

# Automatically collect all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

# Add main.cpp manually if outside src/
set(SOURCES ${SOURCES} main.cpp)

add_executable(my_program ${SOURCES})

target_include_directories(my_program PRIVATE ${CMAKE_SOURCE_DIR}/include)


target_link_libraries(my_program sfml-graphics sfml-window sfml-system)


