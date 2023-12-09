#include "../include/PlayerMovement.h"
#include "../include/game.h"
#include "../include/Position.h"
#include <cstdlib>
#include <ctime>

const float Game::SCENE_WIDTH = 900.0f;
const float Game::SCENE_HEIGHT = 700.0f;
const float Game::PLAYER_START_X = 400.0f;
const float Game::PLAYER_START_Y = 300.0f;
const float Game::RADIUS = 40.0f;
const float Game::APPLE_RADIUS = 20.0f; // Radius for the apple

Game::Game() : playerPosition(PLAYER_START_X, PLAYER_START_Y), direction(RIGHT), speedX(2.0f), speedY(2.0f), isGameOver(false) {
    initWindow();
    initBackground();
    initPlayer(); // This will now initialize a square segment instead of Pac-Man
    initApple();
    // Initialize snake with a single segment represented by a square
    snakeBody.push_back(playerPosition);
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
    player.setRadius(RADIUS / 1.5f); 
    player.setFillColor(sf::Color::Green); // Set the snake segment to green
    player.setPosition(PLAYER_START_X, PLAYER_START_Y);
    // No need to load pacman.png anymore
    return 0;
}

void Game::initApple() {
    srand(time(NULL)); // Seed for random number generation
    apple.setRadius(APPLE_RADIUS);
    apple.setFillColor(sf::Color::Red); // Color the apple red
    randomizeApplePosition(); // Set initial position of the apple
}

void Game::randomizeApplePosition() {
    bool isPositionOnSnake;
    float x, y;

    do {
        isPositionOnSnake = false;
        x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (SCENE_WIDTH - APPLE_RADIUS * 2);
        y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (SCENE_HEIGHT - APPLE_RADIUS * 2);

        // Check if the random position is on the snake's body
        for (const auto& segment : snakeBody) {
            if (std::abs(segment.x - (x + APPLE_RADIUS)) < APPLE_RADIUS * 2 &&
                std::abs(segment.y - (y + APPLE_RADIUS)) < APPLE_RADIUS * 2) {
                isPositionOnSnake = true;
                break; // No need to check other segments if one is overlapping
            }
        }
    } while (isPositionOnSnake); // Continue trying if the position is on the snake

    // Set apple position if it's not colliding with the snake
    apple.setPosition(x + APPLE_RADIUS, y + APPLE_RADIUS);
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
        // Calculate the new position based on the current direction
        switch (direction) {
            case UP:    playerPosition.y -= speedY; break;
            case DOWN:  playerPosition.y += speedY; break;
            case LEFT:  playerPosition.x -= speedX; break;
            case RIGHT: playerPosition.x += speedX; break;
        }

        // Self-collision detection logic
        for (size_t i = 1; i < snakeBody.size(); ++i) {
            if (playerPosition.x == snakeBody[i].x && playerPosition.y == snakeBody[i].y) {
                isGameOver = true; // End game if the snake's head collides with any part of its body
                return; // No need to run the rest of the update if the game is over
            }
        }

        // Collision detection with the apple
        // The snake head is the first element of the snakeBody vector
        Position snakeHead = snakeBody.front();
        float deltaX = apple.getPosition().x - snakeHead.x;
        float deltaY = apple.getPosition().y - snakeHead.y;
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        // If the distance is less than the sum of the radii, we have a collision
        if (distance < (player.getRadius() + apple.getRadius())) {
            randomizeApplePosition();
            growSnake();
        }

        // Update the snake body
        // Move the rest of the body
        for (size_t i = snakeBody.size() - 1; i > 0; --i) {
            snakeBody[i] = snakeBody[i - 1];
        }
        // Update the head position
        snakeBody[0] = playerPosition;

        // Boundary collision detection
        if (playerPosition.x - RADIUS < 0 || playerPosition.x + RADIUS > SCENE_WIDTH ||
            playerPosition.y - RADIUS < 0 || playerPosition.y + RADIUS > SCENE_HEIGHT) {
            isGameOver = true; // Game over if the snake hits the boundary
        }
    }
}



void Game::growSnake() {
    // Define how many segments to add each time the snake eats an apple
    const int growthFactor = 15;
    
    // Add multiple new segments to the snake body at the current tail position
    for (int i = 0; i < growthFactor; ++i) {
        snakeBody.push_back(snakeBody.back());
    }
}

void Game::render() {
    window.clear(sf::Color::White);
    if (!isGameOver) {
        window.draw(background);
        // Render each segment of the snake as a green square
        for (const auto& segment : snakeBody) {
            player.setPosition(segment.x, segment.y);
            window.draw(player); // Draw each segment of the snake
        }
        window.draw(apple); // Render the apple
    } else {
        // Optional: Display a game over message or screen
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
