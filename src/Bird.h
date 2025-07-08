#pragma once
#include <graphics.h>

class Bird {
public:
    float x, y;
    float velocity;

    Bird();
    void update();
    void jump();
    void draw();
};