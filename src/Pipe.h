#pragma once
#include <graphics.h>
#include "Coin.h"

class Pipe {
public:
    int x;
    int topHeight;
    int bottomY;
    int gapSize;
    bool passed;
    Coin coin;

    Pipe(int startX, int currentScore = 0);
    void initCoin();
    void update();
    void draw();
    bool isOffScreen() const;
    bool checkCollision(Bird& bird);
};