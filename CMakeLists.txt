cmake_minimum_required(VERSION 3.16)
project(draw-plus-plus)

set(DPP_SRCS
    src/client.cpp  
    src/main.cpp  
    src/main.hpp  
    src/sdl.cpp 
    src/server.cpp
)

add_library(sdl INTERFACE)
target_link_libraries(sdl INTERFACE SDL2 SDL2_net SDL2_gfx)

add_executable(main ${DPP_SRCS})
target_link_libraries(main PRIVATE sdl)
