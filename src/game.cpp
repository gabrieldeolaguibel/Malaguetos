#include "../include/PlayerMovement.h"
#include "../include/game.h"
#include "../include/Position.h"

const float Game::SCENE_WIDTH = 900.0f;
const float Game::SCENE_HEIGHT = 700.0f;
const float Game::PLAYER_START_X = 400.0f;
const float Game::PLAYER_START_Y = 300.0f;
const float Game::RADIUS = 40.0f;

Game::Game() : playerPosition(PLAYER_START_X, PLAYER_START_Y), direction(RIGHT), speedX(2.0f), speedY(2.0f), isGameOver(false) {
    initWindow();
    initBackground();
    initPlayer();
}

int Game::initWindow() {
    window.create(sf::VideoMode(SCENE_WIDTH, SCENE_HEIGHT), "Snake Game");
    window.setFramerateLimit(120);
    return 0;
}

int Game::initBackground() {
    if (!backgroundTexture.loadFromFile("resources/background.png")) {
        return 1;
    }
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT));
    return 0;
}

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

void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (!isGameOver) {
                    switch (event.key.code) {
                        case sf::Keyboard::Up:    direction = UP; break;
                        case sf::Keyboard::Down:  direction = DOWN; break;
                        case sf::Keyboard::Left:  direction = LEFT; break;
                        case sf::Keyboard::Right: direction = RIGHT; break;
                    }
                }
                break;
        }
    }
}

void Game::update() {
    if (!isGameOver) {
        Position newPosition = playerPosition;

        switch (direction) {
            case UP:    newPosition.y -= speedY; break;
            case DOWN:  newPosition.y += speedY; break;
            case LEFT:  newPosition.x -= speedX; break;
            case RIGHT: newPosition.x += speedX; break;
        }

        if (newPosition.x - RADIUS < 0 || newPosition.x + RADIUS > SCENE_WIDTH ||
            newPosition.y - RADIUS < 0 || newPosition.y + RADIUS > SCENE_HEIGHT) {
            isGameOver = true; // Set the game over flag if the player hits the boundary
        } else {
            playerPosition = newPosition;
            player.setPosition(playerPosition.x, playerPosition.y);
        }
    }
}

void Game::render() {
    window.clear(sf::Color::White);
    if (!isGameOver) {
        window.draw(background);
        window.draw(player);
    } else {
        // for later: Display a game over message or screen
    }
    window.display();
}

int Game::run() {
    while (window.isOpen()) {
        processInput();
        update();
        render();
    }
    return 0;
}
