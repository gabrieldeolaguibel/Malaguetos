#include <gtest/gtest.h>
#include "game.h"

TEST(Run_test, run) {
    Game game;
    EXPECT_EQ(game.run(), 0);
}

TEST(Position_test, innit_snake_position) {
    Game game;
    EXPECT_EQ(game.getSnakePosition(0).x, 400.0f);
    EXPECT_EQ(game.getSnakePosition(0).y, 300.0f);
}

TEST(Size_Test, increaseSize) {
    Game game;
    game.growSnake(1);
    EXPECT_EQ(game.getSnakeSize(), 2);
}

TEST(Size_Test, decreaseSize) {
    Game game;
    game.growSnake(1);
    game.shrinkSnake(1);
    EXPECT_EQ(game.getSnakeSize(), 1);
}