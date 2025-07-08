#include "Game.h"
#include "game_constants.h"
#include <ctime>
#include <cstdlib>
#include <tchar.h>
#include <algorithm>

Game::Game() {
    score = 0;
    gameOver = false;
    gameStarted = false;
    srand((unsigned int)time(NULL));
    initAudio();
}

void Game::addPipe() {
    pipes.push_back(Pipe(WINDOW_WIDTH, score));
}

void Game::update() {
    if (!gameStarted || gameOver) return;
    
    bird.update();
    
    // Update pipes and check collisions
    for (auto& pipe : pipes) {
        pipe.update();
        
        // Check pipe collision
        if (pipe.checkCollision(bird)) {
            gameOver = true;
        }
        
        // Check coin collision
        if (pipe.coin.checkCollision(bird)) {
            pipe.coin.collected = true;
            score++;
            playCoinSound();
        }
    }
    
    // Remove off-screen pipes
    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), 
        [](const Pipe& p) { return p.isOffScreen(); }), pipes.end());
    
    // Check if bird hits ground or ceiling
    if (bird.y <= 0 || bird.y >= WINDOW_HEIGHT - BIRD_SIZE) {
        gameOver = true;
    }
}

void Game::draw() {
    // Clear screen
    setbkcolor(RGB(135, 206, 235)); // Sky blue background
    cleardevice();
    
    // Draw cloud decorations
    setfillcolor(WHITE);
    for (int i = 0; i < 5; i++) {
        solidcircle(100 + i * 150, 80, 20);
        solidcircle(120 + i * 150, 70, 25);
        solidcircle(140 + i * 150, 80, 20);
    }
    
    // Draw pipes
    for (auto& pipe : pipes) {
        pipe.draw();
    }
    
    // Draw bird
    bird.draw();
    
    // Draw score and difficulty info
    settextcolor(WHITE);
    settextstyle(30, 0, _T("Arial"));
    TCHAR scoreText[50];
    _stprintf_s(scoreText, _T("Score: %d"), score);
    outtextxy(20, 20, scoreText);
    
    // Show difficulty level
    if (gameStarted && !gameOver && score > 0) {
        settextstyle(20, 0, _T("Arial"));
        int difficultyLevel = min(score / 3 + 1, 15);  // Max level 15
        TCHAR difficultyText[50];
        _stprintf_s(difficultyText, _T("Level: %d"), difficultyLevel);
        outtextxy(20, 60, difficultyText);
    }
    
    // Game start prompt
    if (!gameStarted) {
        settextcolor(BLACK);
        settextstyle(40, 0, _T("Arial"));
        outtextxy(WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT/2 - 100, _T("Flappy Bird"));
        settextstyle(20, 0, _T("Arial"));
        outtextxy(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 50, _T("Press SPACE to start"));
        outtextxy(WINDOW_WIDTH/2 - 120, WINDOW_HEIGHT/2 - 20, _T("Press SPACE to jump"));
        outtextxy(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 10, _T("Collect coins to score!"));
    }
    
    // Game over screen
    if (gameOver) {
        settextcolor(RED);
        settextstyle(50, 0, _T("Arial"));
        outtextxy(WINDOW_WIDTH/2 - 120, WINDOW_HEIGHT/2 - 50, _T("Game Over!"));
        settextstyle(20, 0, _T("Arial"));
        outtextxy(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2, _T("Press R to restart"));
        outtextxy(WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2 + 30, _T("Press ESC to exit"));
    }
}

void Game::restart() {
    bird = Bird();
    pipes.clear();
    score = 0;
    gameOver = false;
    gameStarted = false;
}

void Game::initAudio() {
    audioManager.playBackgroundMusic();
    audioManager.setVolume(30);
}

void Game::playCoinSound() {
    audioManager.playCoinSound();
}