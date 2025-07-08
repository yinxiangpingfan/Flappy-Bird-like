#include "AudioManager.h"
#include "resource.h"
#include <iostream>
#include <tchar.h>
#include <thread>

AudioManager::AudioManager() : backgroundMusicPlaying(false), currentVolume(50) {
}

AudioManager::~AudioManager() {
    stopBackgroundMusic();
}

void AudioManager::playBackgroundMusic() {
    stopBackgroundMusic();
    playResourceSound(IDR_BG_MUSIC, true);
    backgroundMusicPlaying = true;
}

void AudioManager::stopBackgroundMusic() {
    if (backgroundMusicPlaying) {
        mciSendStringA("stop bgmusic", NULL, 0, NULL);
        mciSendStringA("close bgmusic", NULL, 0, NULL);
        backgroundMusicPlaying = false;
        currentBackgroundMusic.clear();
    }
}

void AudioManager::playCoinSound() {
    playResourceSound(IDR_COIN_SOUND, false);
}

void AudioManager::playResourceSound(int resourceId, bool loop) {
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(resourceId), RT_RCDATA);
    if (hRes) {
        HGLOBAL hData = LoadResource(NULL, hRes);
        if (hData) {
            LPVOID pData = LockResource(hData);
            DWORD dataSize = SizeofResource(NULL, hRes);
            if (pData && dataSize > 0) {
                // Create temporary file to play MP3
                TCHAR tempPath[MAX_PATH];
                TCHAR tempFile[MAX_PATH];
                GetTempPath(MAX_PATH, tempPath);
                GetTempFileName(tempPath, _T("snd"), 0, tempFile);
                
                HANDLE hFile = CreateFile(tempFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
                if (hFile != INVALID_HANDLE_VALUE) {
                    DWORD written;
                    WriteFile(hFile, pData, dataSize, &written, NULL);
                    CloseHandle(hFile);
                    
                    // Use MCI to play MP3 file, generate unique alias for sound effects
                    std::string alias;
                    if (resourceId == IDR_BG_MUSIC) {
                        alias = "bgmusic";
                    } else {
                        // Generate time-based unique alias for sound effects
                        alias = "sfx" + std::to_string(GetTickCount());
                    }
                    
                    char tempFileA[MAX_PATH];
                    WideCharToMultiByte(CP_ACP, 0, tempFile, -1, tempFileA, MAX_PATH, NULL, NULL);
                    std::string openCmd = "open \"" + std::string(tempFileA) + "\" type mpegvideo alias " + alias;
                    
                    if (mciSendStringA(openCmd.c_str(), NULL, 0, NULL) == 0) {
                        std::string playCmd = "play " + alias;
                        if (loop) {
                            playCmd += " repeat";
                        } else {
                            // For non-looping sound effects, auto-close after playback
                            playCmd += " notify";
                        }
                        mciSendStringA(playCmd.c_str(), NULL, 0, NULL);
                        
                        // For sound effects, async close to avoid blocking
                        if (!loop) {
                            std::thread([alias, tempFileA]() {
                                Sleep(2000); // Wait for sound effect to complete
                                mciSendStringA(("close " + alias).c_str(), NULL, 0, NULL);
                                DeleteFileA(tempFileA); // Clean up temporary file
                            }).detach();
                        }
                    }
                }
            }
        }
    }
}

void AudioManager::setVolume(int volume) {
    currentVolume = (volume < 0) ? 0 : (volume > 100) ? 100 : volume;
    
    if (backgroundMusicPlaying) {
        std::string volumeCommand = "setaudio bgmusic volume to " + std::to_string(currentVolume * 10);
        mciSendStringA(volumeCommand.c_str(), NULL, 0, NULL);
    }
}