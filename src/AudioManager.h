#pragma once
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include "resource.h"
#pragma comment(lib, "winmm.lib")

class AudioManager {
public:
    AudioManager();
    ~AudioManager();
    
    // Play background music (loop)
    void playBackgroundMusic();
    
    // Stop background music
    void stopBackgroundMusic();
    
    // Play sound effect (one-time)
    void playCoinSound();
    
    // Load and play audio from resource
    void playResourceSound(int resourceId, bool loop = false);
    
    // Set volume (0-100)
    void setVolume(int volume);
    
private:
    bool backgroundMusicPlaying;
    std::string currentBackgroundMusic;
    int currentVolume;
};