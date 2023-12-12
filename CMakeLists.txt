cmake_minimum_required(VERSION 3.25)
project(2D_game_assignment)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML") Mac
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML") # Luca C:\SFML-2.6.1\lib\cmake\SFML

include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0  # Specify the commit, tag, or branch you want to use
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Make Google Test available for use
FetchContent_MakeAvailable(googletest)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

include_directories(include)

configure_file(resources/background.png ${CMAKE_CURRENT_BINARY_DIR}/resources/background.png COPYONLY)
configure_file(resources/pacman.png ${CMAKE_CURRENT_BINARY_DIR}/resources/pacman.png COPYONLY)

# Enable testing
enable_testing()

add_executable(2D_game_assignment
        src/main.cpp
        src/game.cpp
        src/PlayerMovement.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})