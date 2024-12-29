cmake_minimum_required(VERSION 3.16)

# Project Name
project(LANC_ToneGenerator)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Raylib
find_package(raylib REQUIRED)

# Include Raylib directories
include_directories(${RAYLIB_INCLUDE_DIRS})

# Add the executable
add_executable(LANC_ToneGenerator main.cpp
    wavegenerator.h wavegenerator.cpp
    command.h command.cpp)

# Link Raylib library explicitly
target_link_libraries(LANC_ToneGenerator PRIVATE ${RAYLIB_LIBRARIES} raylib)

# Additional configurations (optional)
if (UNIX AND NOT APPLE)
    target_link_libraries(LANC_ToneGenerator PRIVATE m) # Link math library on Linux
endif()
