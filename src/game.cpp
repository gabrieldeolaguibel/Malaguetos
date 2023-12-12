#include "../include/PlayerMovement.h"
#include "../include/game.h"
#include "../include/Position.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

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
    initMovingApple();
    initShrinkingApple(); // Call the new method to initialize the shrinking apple
    initAdditionalShrinkingApple(); // Initialize the additional static red apple

    // Initialize snake with a single segment represented by a square
    snakeBody.push_back(playerPosition);
}

int Game::getSnakeSize() {
    return snakeBody.size();
}

Position Game::getSnakePosition(int index) {
    return snakeBody[index];
}

void Game::setDirection(Direction newDirection) {
    this->direction = newDirection;
}

// Initialize the window to play the game
int Game::initWindow() {
    window.create(sf::VideoMode(SCENE_WIDTH, SCENE_HEIGHT), "Snake Game");
    window.setFramerateLimit(120);
    return 0;
}

// Initialize the background loading it from the corresponding .png file
int Game::initBackground() {
    if (!backgroundTexture.loadFromFile("resources/background.png")) {
        return 1;
    }
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT));
    return 0;
}

// Initialize the snake segment
int Game::initPlayer() {
    player.setRadius(RADIUS / 1.5f); 
    player.setFillColor(sf::Color::Green); // Set the snake segment to green
    player.setPosition(PLAYER_START_X, PLAYER_START_Y);
    return 0;
}

// Initialize the apple
void Game::initApple() {
    srand(time(NULL)); // Seed for random number generation
    apple.setRadius(APPLE_RADIUS);
    apple.setFillColor(sf::Color::Green);
    randomizeApplePosition(); // Set initial position of the apple
}

// Randomize the position of the apple
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

// Initialize the moving apple
void Game::initMovingApple() {
    movingApple.setRadius(APPLE_RADIUS);
    movingApple.setFillColor(sf::Color::Blue); // Different color for distinction
    randomizeMovingApplePosition();
    movingAppleSpeedX = 1.0f; // Set initial speed for the moving apple
    movingAppleSpeedY = 1.0f;
}

// Randomize the position of the moving apple
void Game::randomizeMovingApplePosition() {
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
                break;
            }
        }
    } while (isPositionOnSnake); // Continue trying if the position is on the snake

    // Set moving apple position if it's not colliding with the snake
    movingApple.setPosition(x + APPLE_RADIUS, y + APPLE_RADIUS);
}

// Initialize the additional static red apple
void Game::initAdditionalShrinkingApple() {
    additionalShrinkingApple.setRadius(APPLE_RADIUS);
    additionalShrinkingApple.setFillColor(sf::Color::Red); // Set color to red
    randomizeAdditionalShrinkingApplePosition();
}

// Randomize the position of the additional static red apple
void Game::randomizeAdditionalShrinkingApplePosition() {
    bool isPositionOnSnake;
    float x, y;

    do {
        isPositionOnSnake = false;
        x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (SCENE_WIDTH - APPLE_RADIUS * 2);
        y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (SCENE_HEIGHT - APPLE_RADIUS * 2);

        // Check if the random position is on the snake's body or overlaps with other apples
        for (const auto& segment : snakeBody) {
            if (std::abs(segment.x - (x + APPLE_RADIUS)) < APPLE_RADIUS * 2 &&
                std::abs(segment.y - (y + APPLE_RADIUS)) < APPLE_RADIUS * 2) {
                isPositionOnSnake = true;
                break;
            }
        }

        if (!isPositionOnSnake) {
            // Check for overlap with other apples
            if (checkAppleOverlap(x, y, apple) || checkAppleOverlap(x, y, movingApple) || checkAppleOverlap(x, y, shrinkingApple)) {
                isPositionOnSnake = true;
            }
        }
    } while (isPositionOnSnake);

    additionalShrinkingApple.setPosition(x + APPLE_RADIUS, y + APPLE_RADIUS);
}

// Initialize the shrinking apple (same as the moving apple)
void Game::initShrinkingApple() {
    shrinkingApple.setRadius(APPLE_RADIUS);
    shrinkingApple.setFillColor(sf::Color::Red); // Different color for distinction
    randomizeShrinkingApplePosition();
    shrinkingAppleSpeedX = 1.0f; // Set initial speed for the shrinking apple
    shrinkingAppleSpeedY = 1.0f;
}

// Randomize the position of the shrinking apple (same as the moving apple)
void Game::randomizeShrinkingApplePosition() {
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
                break;
            }
        }

        // Additionally, check if the position overlaps with the regular or moving apple
        if (!isPositionOnSnake) {
            float regularAppleX = apple.getPosition().x;
            float regularAppleY = apple.getPosition().y;
            float movingAppleX = movingApple.getPosition().x;
            float movingAppleY = movingApple.getPosition().y;

            if ((std::abs(x - regularAppleX) < APPLE_RADIUS * 2 && std::abs(y - regularAppleY) < APPLE_RADIUS * 2) ||
                (std::abs(x - movingAppleX) < APPLE_RADIUS * 2 && std::abs(y - movingAppleY) < APPLE_RADIUS * 2)) {
                isPositionOnSnake = true;
            }
        }
    } while (isPositionOnSnake); // Continue trying if the position is on the snake or overlaps with other apples

    // Set shrinking apple position if it's not colliding with the snake or other apples
    shrinkingApple.setPosition(x + APPLE_RADIUS, y + APPLE_RADIUS);
}

// Check if the shrinking apple overlaps with another apple
bool Game::checkAppleOverlap(float x, float y, const sf::CircleShape& otherApple) {
    float deltaX = otherApple.getPosition().x - x;
    float deltaY = otherApple.getPosition().y - y;
    return std::sqrt(deltaX * deltaX + deltaY * deltaY) < APPLE_RADIUS * 2;
}

// Process user input
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

// Update the game state
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
            growSnake(3);
        }

        // Update the snake body
        // Move the rest of the body
        for (size_t i = snakeBody.size() - 1; i > 0; --i) {
            snakeBody[i] = snakeBody[i - 1];
        }
        // Update the head position
        snakeBody[0] = playerPosition;

        // Boundary collision detection
        if (playerPosition.x - (RADIUS - 20) < 0 || playerPosition.x + (RADIUS - 20) > SCENE_WIDTH ||
            playerPosition.y - (RADIUS - 20) < 0 || playerPosition.y + (RADIUS - 20) > SCENE_HEIGHT) {
            isGameOver = true; // Game over if the snake hits the boundary
        }

        // Collision detection with the moving apple
        if (checkCollision(snakeHead, movingApple)) {
            randomizeMovingApplePosition();
            growSnake(30); // Increase growth factor for moving apple
        }
        // Collision detection with the shrinking apple
        if (checkCollision(snakeHead, shrinkingApple)) {
            randomizeShrinkingApplePosition();
            shrinkSnake(30); // Shrink the snake by 30 segments
        }
        // Collision detection with the additional static red apple
        if (checkCollision(snakeHead, additionalShrinkingApple)) {
            randomizeAdditionalShrinkingApplePosition();
            shrinkSnake(30); // Shrink the snake by 30 segments
        }
        updateShrinkingApplePosition();
        updateMovingApplePosition(); 
    }
}

// Update the position of the shrinking apple
void Game::updateShrinkingApplePosition() {
    // Move the apple
    shrinkingApple.setPosition(shrinkingApple.getPosition().x + shrinkingAppleSpeedX,
                               shrinkingApple.getPosition().y + shrinkingAppleSpeedY);

    // Boundary collision detection and response
    if (shrinkingApple.getPosition().x < 0 || shrinkingApple.getPosition().x > SCENE_WIDTH) {
        shrinkingAppleSpeedX = -shrinkingAppleSpeedX;
    }
    if (shrinkingApple.getPosition().y < 0 || shrinkingApple.getPosition().y > SCENE_HEIGHT) {
        shrinkingAppleSpeedY = -shrinkingAppleSpeedY;
    }
}

// Update the position of the moving apple
void Game::updateMovingApplePosition() {
    // Move the apple
    movingApple.setPosition(movingApple.getPosition().x + movingAppleSpeedX,
                            movingApple.getPosition().y + movingAppleSpeedY);

    // Boundary collision detection and response
    if (movingApple.getPosition().x < 0 || movingApple.getPosition().x > SCENE_WIDTH) {
        movingAppleSpeedX = -movingAppleSpeedX;
    }
    if (movingApple.getPosition().y < 0 || movingApple.getPosition().y > SCENE_HEIGHT) {
        movingAppleSpeedY = -movingAppleSpeedY;
    }
}

// Check if the snake's head collides with an apple
bool Game::checkCollision(const Position& snakeHead, const sf::CircleShape& apple) {
    float deltaX = apple.getPosition().x - snakeHead.x;
    float deltaY = apple.getPosition().y - snakeHead.y;
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    return distance < (player.getRadius() + apple.getRadius());
}

// Grow the snake by the specified growth factor
void Game::growSnake(int growthFactor) {
    for (int i = 0; i < growthFactor; ++i) {
        snakeBody.push_back(snakeBody.back());
    }
}

// Shrink the snake by the specified shrink factor
void Game::shrinkSnake(int shrinkFactor) {
    for (int i = 0; i < shrinkFactor && !snakeBody.empty(); ++i) {
        snakeBody.pop_back();
    }
    if (snakeBody.empty()) {
        isGameOver = true; // End the game if the snake has no segments left
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
        window.clear(sf::Color::Black);
        window.draw(background);
        // Display a game over message in red font
        sf::Font font;
        font.loadFromFile("resources/arial.ttf");
        sf::Text text("Game Over!", font, 50);
        text.setFillColor(sf::Color::Red);
        text.setPosition(SCENE_WIDTH / 2 - 150, SCENE_HEIGHT / 2 - 50);
        window.draw(text);
    }
    window.draw(movingApple); // Draw the moving apple
    window.draw(shrinkingApple); // Draw the shrinking apple
    window.draw(additionalShrinkingApple); // Draw the additional static red apple
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
