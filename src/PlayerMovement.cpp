#include "../include/PlayerMovement.h"
#include "../include/Position.h"

Position PlayerMovement::updatePosition(const Position& currentPosition, float speedX, float speedY) {
    Position newPosition;
    newPosition.x = currentPosition.x + speedX;
    newPosition.y = currentPosition.y + speedY;
    return newPosition;
}
