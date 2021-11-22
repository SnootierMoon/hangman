cmake_minimum_required(VERSION 3.16)
project(draw-plus-plus)

set(DPP_SOURCES
    src/main.cpp
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(main ${DPP_SOURCES})
target_link_libraries(main PRIVATE SDL2::Main SDL2::GFX SDL2::Net SDL2::TTF)
