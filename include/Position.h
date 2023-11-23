#ifndef POSITION_H
#define POSITION_H

struct Position {
    float x;
    float y;

    // Constructor with default parameters
    Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

#endif // POSITION_H
