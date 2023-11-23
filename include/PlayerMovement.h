#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "Position.h"

class PlayerMovement {
public:
    static Position updatePosition(const Position& currentPosition, float speedX, float speedY);
};

#endif // PLAYER_MOVEMENT_H

