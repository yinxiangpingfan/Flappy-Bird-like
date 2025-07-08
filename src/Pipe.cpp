#include "Pipe.h"
#include "game_constants.h"
#define NOMINMAX
#include <algorithm>
#include <cstdlib>

using namespace std;

Pipe::Pipe(int startX, int currentScore) : 
    x(startX),
    passed(false),
    coin(0,0) // Initialized to a temporary value
{
    // Difficulty increases with score - gap gets smaller
    int difficultyReduction = (currentScore * 3 < 40) ? currentScore * 3 : 40;  // Max reduction of 40 pixels
    int adjustedGapMin = (PIPE_GAP_MIN - difficultyReduction > 120) ? PIPE_GAP_MIN - difficultyReduction : 120;  // Minimum safe gap
    int adjustedGapMax = (PIPE_GAP_MAX - difficultyReduction > adjustedGapMin + 20) ? PIPE_GAP_MAX - difficultyReduction : adjustedGapMin + 20;
    
    // Random gap size between adjusted min and max
    gapSize = adjustedGapMin + rand() % (adjustedGapMax - adjustedGapMin + 1);
    
    // Random top pipe height, ensuring reasonable gap placement
    int minTopHeight = 80;  // Minimum top pipe height
    int maxTopHeight = WINDOW_HEIGHT - gapSize - 80;  // Maximum top pipe height
    topHeight = minTopHeight + rand() % (maxTopHeight - minTopHeight + 1);
    bottomY = topHeight + gapSize;
    
    // Initialize coin in a separate method for clarity
    initCoin();
}

void Pipe::initCoin() {
    float coinX = (float)(x + PIPE_WIDTH / 2);
    float coinY = (float)(topHeight + gapSize / 2);
    coin = Coin(coinX, coinY);
}

void Pipe::update() {
    x -= PIPE_SPEED;
    coin.x -= PIPE_SPEED;
}

void Pipe::draw() {
    // Top pipe
    setfillcolor(GREEN);
    solidrectangle(x, 0, x + PIPE_WIDTH, topHeight);
    
    // Bottom pipe
    solidrectangle(x, bottomY, x + PIPE_WIDTH, WINDOW_HEIGHT);
    
    // Pipe border
    setlinecolor(RGB(0, 100, 0)); // Dark green
    setlinestyle(PS_SOLID, 2);
    rectangle(x, 0, x + PIPE_WIDTH, topHeight);
    rectangle(x, bottomY, x + PIPE_WIDTH, WINDOW_HEIGHT);
    
    // Draw coin
    coin.draw();
}

bool Pipe::isOffScreen() const {
    return x + PIPE_WIDTH < 0;
}

bool Pipe::checkCollision(Bird& bird) {
    // Check bird collision with pipe
    if (bird.x + BIRD_SIZE > x && bird.x < x + PIPE_WIDTH) {
        if (bird.y < topHeight || bird.y + BIRD_SIZE > bottomY) {
            return true;
        }
    }
    return false;
}