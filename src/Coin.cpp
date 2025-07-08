#include "Coin.h"
#include "game_constants.h"
#include <cmath>

Coin::Coin(float coinX, float coinY) {
    x = coinX;
    y = coinY;
    collected = false;
}


void Coin::draw() {
    if (!collected) {
        // Draw coin with enhanced visibility
        // Main coin body
        setfillcolor(RGB(255, 215, 0)); // Gold color
        solidcircle((int)x, (int)y, COIN_SIZE / 2);
        
        // Add shine effect
        setfillcolor(RGB(255, 255, 200)); // Brighter light gold
        solidcircle((int)x - 2, (int)y - 2, COIN_SIZE / 3);
        
        // Draw thick border for better visibility
        setlinecolor(RGB(184, 134, 11)); // Dark gold border
        setlinestyle(PS_SOLID, 3);
        circle((int)x, (int)y, COIN_SIZE / 2);
        
        // Add inner circle for coin detail
        setlinecolor(RGB(255, 223, 0)); // Bright gold
        setlinestyle(PS_SOLID, 1);
        circle((int)x, (int)y, COIN_SIZE / 3);
    }
}

bool Coin::checkCollision(Bird& bird) {
    if (collected) return false;
    
    float dx = bird.x + BIRD_SIZE/2 - x;
    float dy = bird.y + BIRD_SIZE/2 - y;
    float distance = sqrt(dx*dx + dy*dy);
    
    return distance < (BIRD_SIZE/2 + COIN_SIZE/2);
}

bool Coin::isOffScreen() const {
    return x + COIN_SIZE < 0;
}