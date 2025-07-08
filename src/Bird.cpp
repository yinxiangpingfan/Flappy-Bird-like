#include "Bird.h"
#include "game_constants.h"

Bird::Bird() {
    x = 100;
    y = WINDOW_HEIGHT / 2;
    velocity = 0;
}

void Bird::update() {
    velocity += GRAVITY;
    y += velocity;
    
    // Boundary check
    if (y < 0) y = 0;
    if (y > WINDOW_HEIGHT - BIRD_SIZE) y = WINDOW_HEIGHT - BIRD_SIZE;
}

void Bird::jump() {
    velocity = JUMP_FORCE;
}

void Bird::draw() {
    setfillcolor(YELLOW);
    solidcircle((int)x + BIRD_SIZE/2, (int)y + BIRD_SIZE/2, BIRD_SIZE/2);
    
    // Draw eyes
    setfillcolor(BLACK);
    solidcircle((int)x + BIRD_SIZE/2 + 5, (int)y + BIRD_SIZE/2 - 5, 3);
}