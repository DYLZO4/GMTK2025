cmake_minimum_required(VERSION 3.10)
project(MyAnchorProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# Gather all .cpp files from src/
file(GLOB SOURCES "src/*.cpp")

# Add main.cpp manually if it's in the root directory
list(APPEND SOURCES ${CMAKE_SOURCE_DIR}/main.cpp)

# Create executable
add_executable(my_program ${SOURCES})

# Include headers from /include
target_include_directories(my_program PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SFML
target_link_libraries(my_program sfml-graphics sfml-window sfml-system)

