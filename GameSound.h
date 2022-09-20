#pragma once
#include <fmod.hpp>

class GameSound
{
private:
    FMOD::Sound* sound;
    const char* soundFilePath;
    float volume;
    float pitch;
    float pan;
    bool loop;
public:
    GameSound();
    ~GameSound();
    void Init(const char* filePath, float volume, float pitch, float soundPan, bool soundLoop);
    // Setters
    void SetSoundFilePath(const char* filePath);
    void SetVolume(float soundVolume);
    void SetPitch(float soundPitch);
    void SetPan(float soundPan);
    void SetLoop(bool soundLoop);
    // Getters
    FMOD::Sound* GetSound();
    const char* GetSoundFilePath();
    float GetVolume();
    float GetPitch();
    float GetPan();
    bool GetLoop();
};
