#pragma once
#include <graphics.h>
#include "Bird.h"

class Coin {
public:
    float x, y;
    bool collected;

    Coin(float coinX, float coinY);

    void draw();
    bool checkCollision(Bird& bird);
    bool isOffScreen() const;
};