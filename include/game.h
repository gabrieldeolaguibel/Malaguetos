/*
 * Description: Game class header.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"

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

    enum Direction { UP, DOWN, LEFT, RIGHT };
    Direction direction; 

    int initWindow();
    int initBackground();
    int initPlayer();
    void processInput();
    void update();
    void render();
};
