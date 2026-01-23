cmake_minimum_required(VERSION 3.16)
project(terraria)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty/glfw-3.4)
add_subdirectory(thirdparty/glew-2.1.0/build/cmake)
add_subdirectory(thirdparty/imgui-1.92.5)
add_subdirectory(thirdparty/stb_image)

add_executable("${CMAKE_PROJECT_NAME}" 
    ${CMAKE_SOURCE_DIR}/src/Application.cpp
    ${CMAKE_SOURCE_DIR}/src/platform/Input.cpp

    ${CMAKE_SOURCE_DIR}/src/renderer/Renderer.cpp 
    ${CMAKE_SOURCE_DIR}/src/renderer/IndexBuffer.cpp 
    ${CMAKE_SOURCE_DIR}/src/renderer/VertexBuffer.cpp 
    ${CMAKE_SOURCE_DIR}/src/renderer/VertexArray.cpp
    ${CMAKE_SOURCE_DIR}/src/renderer/VertexBufferLayout.cpp
    ${CMAKE_SOURCE_DIR}/src/renderer/ErrorUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/renderer/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/renderer/Texture.cpp
    ${CMAKE_SOURCE_DIR}/src/renderer/Rectangle.cpp
)

target_link_libraries("${CMAKE_PROJECT_NAME}" 
    PRIVATE 
        glfw
        glew_s
        imgui
        stb_image
)

target_include_directories("${CMAKE_PROJECT_NAME}" 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include/game
        ${CMAKE_SOURCE_DIR}/src/include/platform
        ${CMAKE_SOURCE_DIR}/src/renderer/include
        ${CMAKE_SOURCE_DIR}/thirdparty/glfw-3.4/include 
        ${CMAKE_SOURCE_DIR}/thirdparty/glew-2.1.0/include
        ${CMAKE_SOURCE_DIR}/thirdparty/stb_image
        ${CMAKE_SOURCE_DIR}/thirdparty/glm-1.0.3
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.92.5
)

if(WIN32)
    target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE opengl32)
endif()
