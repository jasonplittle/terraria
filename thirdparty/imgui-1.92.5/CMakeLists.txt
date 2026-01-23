cmake_minimum_required(VERSION 3.16)
project(imgui)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ImGui source files
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_impl_glfw.cpp
)

# Create the static library
add_library(imgui STATIC ${IMGUI_SOURCES})

# Link glfw dependency
target_link_libraries(imgui 
    PUBLIC 
        glfw
)

# Set public include directories
target_include_directories(imgui 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)
