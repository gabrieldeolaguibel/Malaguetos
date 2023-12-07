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

    void growSnake(); // Declare the growSnake method

    int initWindow();
    int initBackground();
    int initPlayer();
    void initApple(); // Declare the initApple method
    void randomizeApplePosition(); // Declare the randomizeApplePosition method
    void processInput();
    void update();
    void render();
};
