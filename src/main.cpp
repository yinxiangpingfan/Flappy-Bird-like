#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <cmath>

#include "Game.h"
#include "game_constants.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize graphics window
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    setbkcolor(RGB(135, 206, 235));
    
    // Enable message handling for keyboard input
    BeginBatchDraw();
    
    Game game;
    int pipeTimer = 0;
    
    while (true) {
        // Handle input using EasyX message system
        ExMessage msg;
        while (peekmessage(&msg)) {
            if (msg.message == WM_KEYDOWN) {
                if (msg.vkcode == VK_SPACE) { // Spacebar to jump
                    if (!game.gameStarted) {
                        game.gameStarted = true;
                    }
                    if (!game.gameOver) {
                        game.bird.jump();
                    }
                }
                else if (msg.vkcode == 'R') { // R key to restart
                    if (game.gameOver) {
                        game.restart();
                    }
                }
                else if (msg.vkcode == VK_ESCAPE) { // ESC key to exit
                    goto exit_game;
                }
            }
        }
        
        // Alternative input method for compatibility
        if (_kbhit()) {
            char key = _getch();
            
            if (key == ' ') { // Spacebar to jump
                if (!game.gameStarted) {
                    game.gameStarted = true;
                }
                if (!game.gameOver) {
                    game.bird.jump();
                }
            }
            else if (key == 'r' || key == 'R') { // R key to restart
                if (game.gameOver) {
                    game.restart();
                }
            }
            else if (key == 27) { // ESC key to exit
                goto exit_game;
            }
        }
        
        // Update game logic
        game.update();
        
        // Add new pipes
        if (game.gameStarted && !game.gameOver) {
            pipeTimer++;
            if (pipeTimer >= 120) { // Add pipe every 2 seconds
                game.addPipe();
                pipeTimer = 0;
            }
        }
        
        // Draw game
        game.draw();
        
        // Flush drawing buffer
        FlushBatchDraw();
        
        // Control frame rate
        Sleep(16); // Approximately 60FPS
    }
    
exit_game:
    EndBatchDraw();
    closegraph();
    return 0;
}