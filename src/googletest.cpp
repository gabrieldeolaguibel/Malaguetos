#include <gtest/gtest.h>
#include "game.h"

TEST(RunTest, Run) {
    Game game;
    EXPECT_EQ(game.run(), 0);
}

TEST(PositionTest, InitSnakePosition) {
    Game game;
    EXPECT_EQ(game.getSnakePosition(0).x, 400.0f);
    EXPECT_EQ(game.getSnakePosition(0).y, 300.0f);
}

TEST(SizeTest, ChangeSize) {
    Game game;
    game.growSnake(1);
    EXPECT_EQ(game.getSnakeSize(), 2);

    game.shrinkSnake(1);
    EXPECT_EQ(game.getSnakeSize(), 1);
}


TEST(GameTest, CollisionDetection) {
    // Create an instance of the Game class
    Game game;

    // Scenario 1: Test collision between snake head and apple (expected collision)
    Position snakeHead(100, 100); // Set snake head position
    sf::CircleShape apple;
    apple.setPosition(120, 120); // Set apple position
    apple.setRadius(20); // Set apple radius

    // Expect a collision between snake head and apple
    EXPECT_TRUE(game.checkCollision(snakeHead, apple));

    // Scenario 2: Test collision between snake head and apple (expected no collision)
    apple.setPosition(250, 250); // Set a position far from the snake head

    // Expect no collision between snake head and apple
    EXPECT_FALSE(game.checkCollision(snakeHead, apple));
}

TEST(MovementTest, Direction) {
    Game game;

    // Scenario 1: Test UP direction
    game.setDirection(Game::UP);
    game.update();

    // Expect the snake to move up
    EXPECT_EQ(game.getSnakePosition(0).y, 298.0f);

    // Scenario 2: Test DOWN direction
    game.setDirection(Game::DOWN);
    game.update();

    // Expect the snake to move down
    EXPECT_EQ(game.getSnakePosition(0).y, 300.0f);

    // Scenario 3: Test LEFT direction
    game.setDirection(Game::LEFT);
    game.update();

    // Expect the snake to move left
    EXPECT_EQ(game.getSnakePosition(0).x, 398.0f);

    // Scenario 4: Test RIGHT direction
    game.setDirection(Game::RIGHT);
    game.update();

    // Expect the snake to move right
    EXPECT_EQ(game.getSnakePosition(0).x, 400.0f);
}
