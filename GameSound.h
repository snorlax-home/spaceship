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
    bool playSoundFlag;
public:
    GameSound();
    ~GameSound();
    void Init(const char* filePath, float volume, float pitch, float soundPan, bool soundLoop);
    // Setters
    void SetSound(FMOD::Sound* newSound);
    void SetSoundFilePath(const char* filePath);
    void SetVolume(float soundVolume);
    void SetPitch(float soundPitch);
    void SetPan(float soundPan);
    void SetLoop(bool soundLoop);
    void SetPlaySoundFlag(bool playSound);
    // Getters
    FMOD::Sound* GetSound();
    void GetSoundName();
    const char* GetSoundFilePath();
    float GetVolume();
    float GetPitch();
    float GetPan();
    bool GetLoop();
    bool GetPlaySoundFlag();

    void CleanUp();
};
