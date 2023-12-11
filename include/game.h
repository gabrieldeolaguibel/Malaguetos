/*
 * Description: Game class header.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"
#include <vector>

class Game {
public:
    Game();
    int run();
    void growSnake(int growthFactor); // Modified to accept growth factor
    bool checkCollision(const Position& snakeHead, const sf::CircleShape& apple);
    void shrinkSnake(int shrinkFactor); // Method to shrink the snake
    void initAdditionalShrinkingApple();
    bool checkAppleOverlap(float x, float y, const sf::CircleShape& otherApple);

private:
    sf::RenderWindow window;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Texture playerTexture;
    sf::CircleShape player;

    Position playerPosition; // New member for player position
    float speedX; // Speed in X direction
    float speedY; // Speed in Y direction
    
    static const float SCENE_WIDTH;
    static const float SCENE_HEIGHT;
    static const float PLAYER_START_X;
    static const float PLAYER_START_Y;
    static const float RADIUS;
    static const float APPLE_RADIUS; // Radius for the apple

    // for player direction control using arrow keys
    enum Direction { UP, DOWN, LEFT, RIGHT };
    Direction direction; 

    // for game over
    bool isGameOver;

    // for apple generation
    sf::CircleShape apple;
    std::vector<Position> snakeBody; // represents snake body

    sf::CircleShape shrinkingApple; // The shrinking apple
    float shrinkingAppleSpeedX;     // Speed of the shrinking apple in the X direction
    float shrinkingAppleSpeedY;     // Speed of the shrinking apple in the Y direction

    sf::CircleShape movingApple; // The moving apple
    float movingAppleSpeedX;     // Speed of the moving apple in the X direction
    float movingAppleSpeedY;     // Speed of the moving apple in the Y direction

    sf::CircleShape additionalShrinkingApple; // The additional static red apple

    void randomizeAdditionalShrinkingApplePosition(); // Method to randomize the position of the additional static red apple
    void initShrinkingApple();                 // Initialize the shrinking apple
    void updateShrinkingApplePosition();       // Update the position of the shrinking apple
    void randomizeShrinkingApplePosition();    // Randomize the starting position of the shrinking apple
    void initMovingApple();                 // Initialize the moving apple
    void updateMovingApplePosition();       // Update the position of the moving apple
    void randomizeMovingApplePosition();    // Randomize the starting position of the moving apple
    int initWindow();
    int initBackground();
    int initPlayer();
    void initApple(); // Declare the initApple method
    void randomizeApplePosition(); // Declare the randomizeApplePosition method
    void processInput();
    void update();
    void render();
};
