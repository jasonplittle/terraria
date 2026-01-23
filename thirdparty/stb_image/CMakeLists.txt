cmake_minimum_required(VERSION 3.16)

project(stb_image)

add_library(stb_image STATIC stb_image.cpp)

target_include_directories(stb_image
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

add_library(stb_image::stb_image ALIAS stb_image)
