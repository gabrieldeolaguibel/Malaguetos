cmake_minimum_required(VERSION 3.25)
project(2D_game_assignment)

set(CMAKE_CXX_STANDARD 14)

# Include FetchContent module
include(FetchContent)

include_directories(include)

# Fetch Google Test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0  # Specify the commit, tag, or branch you want to use
)
# Make Google Test available for use
FetchContent_MakeAvailable(googletest)

# Include SFML directories
include_directories("C:/SFML-2.6.1/include/")
link_directories("C:/SFML-2.6.1/lib")

configure_file(resources/background.png ${CMAKE_CURRENT_BINARY_DIR}/resources/background.png COPYONLY)
configure_file(resources/arial.ttf ${CMAKE_CURRENT_BINARY_DIR}/resources/arial.ttf COPYONLY)


# Enable testing
enable_testing()

add_executable(2D_game_assignment
        src/main.cpp
        src/game.cpp
        src/PlayerMovement.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Test executable
add_executable(game_tests
        src/googletest.cpp
        src/game.cpp
)

# Link Google Test and SFML to the test executable
target_link_libraries(game_tests gtest_main sfml-graphics sfml-window sfml-system)

# Add the test to be run by CTest
add_test(NAME game_tests COMMAND game_tests)