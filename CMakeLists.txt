cmake_minimum_required(VERSION 3.16)
project(hangman)

set(CLIENT_SOURCES
    src/client/main.cpp
)

set(SERVER_SOURCES
    src/server/main.cpp
)

add_executable(client ${CLIENT_SOURCES})
target_link_libraries(client PRIVATE ncurses)

add_executable(server ${SERVER_SOURCES})
target_link_libraries(server PRIVATE ncurses)
