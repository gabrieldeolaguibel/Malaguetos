cmake_minimum_required(VERSION 3.25)
project(2D_game_assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

configure_file(resources/background.png ${CMAKE_CURRENT_BINARY_DIR}/resources/background.png COPYONLY)
configure_file(resources/pacman.png ${CMAKE_CURRENT_BINARY_DIR}/resources/pacman.png COPYONLY)

add_executable(2D_game_assignment
        src/main.cpp
        src/game.cpp
        src/game.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)