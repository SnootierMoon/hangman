cmake_minimum_required(VERSION 3.16)

project(pictionary)

find_package(SFML 2.5 COMPONENTS system window graphics network REQUIRED)

set(SRCS src/main.cpp)

add_executable(pictionary ${SRCS})
target_link_libraries(pictionary PUBLIC sfml-system sfml-window sfml-graphics sfml-network)

