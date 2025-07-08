#pragma once
#include <vector>
#include "Bird.h"
#include "Pipe.h"
#include "AudioManager.h"

class Game {
public:
    Bird bird;
    std::vector<Pipe> pipes;
    int score;
    bool gameOver;
    bool gameStarted;
    AudioManager audioManager;

    Game();
    void addPipe();
    void update();
    void draw();
    void restart();
    void initAudio();
    void playCoinSound();
};