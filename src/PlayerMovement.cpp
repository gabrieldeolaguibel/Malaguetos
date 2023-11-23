#include "../include/PlayerMovement.h"

sf::Vector2f PlayerMovement::updatePosition(const sf::Vector2f& currentPosition) {
    return sf::Vector2f(currentPosition.x + 1.0f, currentPosition.y);
}
