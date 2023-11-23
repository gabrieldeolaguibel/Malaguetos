/*
 * Description: Game class to deal with initialization and controller of 2D my game application.
 */
#include "../include/PlayerMovement.h"
#include "../include/game.h"
#include "../include/Position.h"


const float Game::SCENE_WIDTH = 900.0f;
const float Game::SCENE_HEIGHT = 700.0f;
const float Game::PLAYER_START_X = 400.0f;
const float Game::PLAYER_START_Y = 300.0f;
const float Game::RADIUS = 40.0f;

Game::Game() : playerPosition(PLAYER_START_X, PLAYER_START_Y), speedX(2.0f), speedY(2.0f) {
    initWindow();
    initBackground();
    initPlayer();
}
/**
 * Window initializer.
 */
int Game::initWindow() {
    window.create(sf::VideoMode(SCENE_WIDTH, SCENE_HEIGHT), "PacMan Malaguetos");
    window.setFramerateLimit(120);
    return 0;
}
/**
 * Background initializer.
 */
int Game::initBackground() {
    if (!backgroundTexture.loadFromFile("resources/background.png")) {
        return 1;
    }
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT));
    return 0;
}

/**
 * Player (e.g. PacMan) initializer
 * @return 0 if successfully initialized, 1 otherwise
 */
int Game::initPlayer() {
    player.setRadius(RADIUS);
    player.setOrigin(RADIUS, RADIUS);
    player.setPosition(PLAYER_START_X, PLAYER_START_Y);
    if (!playerTexture.loadFromFile("resources/pacman.png")) {
        return 1;
    }
    player.setTexture(&playerTexture);
    return 0;
}

/**
 * Dealing with events on window.
 */
void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}

/**
 * Function to update the position of the player
 */
void Game::update() {
    // Calculate new position
    Position newPosition = PlayerMovement::updatePosition(playerPosition, speedX, speedY);

    // Boundary checking
    if (newPosition.x - RADIUS < 0) {
        newPosition.x = RADIUS; // Left boundary
    } else if (newPosition.x + RADIUS > SCENE_WIDTH) {
        newPosition.x = SCENE_WIDTH - RADIUS; // Right boundary
    }

    if (newPosition.y - RADIUS < 0) {
        newPosition.y = RADIUS; // Top boundary
    } else if (newPosition.y + RADIUS > SCENE_HEIGHT) {
        newPosition.y = SCENE_HEIGHT - RADIUS; // Bottom boundary
    }

    // Update the player's position
    playerPosition = newPosition;
    player.setPosition(playerPosition.x, playerPosition.y);
}


/**
 * Render elements in the window
 */
void Game::render() {
    window.clear(sf::Color::White);
    window.draw(background);
    window.draw(player);
    window.display();
}
/**
 * Main function to deal with events, update the player and render the updated scene on the window.
 */
int Game::run() {
    while (window.isOpen()) {
        processInput();
        update();
        render();
    }
    return 0;
}