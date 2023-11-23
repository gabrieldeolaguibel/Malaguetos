#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include <SFML/Graphics.hpp>

class PlayerMovement {
public:
    static sf::Vector2f updatePosition(const sf::Vector2f& currentPosition);
};

#endif // PLAYER_MOVEMENT_H
