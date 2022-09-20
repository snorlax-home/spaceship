#include "GameSound.h"

GameSound::GameSound()
{
    sound = nullptr;
    soundFilePath = nullptr;
    volume = 0.0f;
    pitch = 0.0f;
    pan = 0.0f;
    loop = false;
}

GameSound::~GameSound()
{
    // TODO: wat to do here?
}

void GameSound::Init(const char* filePath, float soundVolume,float soundPitch, float soundPan, bool soundLoop)
{
    this->soundFilePath = filePath;
    this->volume = soundVolume;
    this->pitch = soundPitch;
    this->pan = soundPan;
    this->loop = soundLoop;
}

// Setters
// Set the file path for the sound file
void GameSound::SetSoundFilePath(const char* filePath)
{
    this->soundFilePath = filePath;
}

// Set the volume of the sound
void GameSound::SetVolume(float soundVolume)
{
    this->volume = soundVolume;
}

// Set the pitch of the sound
void GameSound::SetPitch(float soundPitch)
{
    this->pitch = soundPitch;
}

// Set the pan of the sound
void GameSound::SetPan(float soundPan)
{
    this->pan = soundPan;
}

// Set the loop of the sound
void GameSound::SetLoop(bool soundLoop)
{
    this->loop = soundLoop;
}

// Getters
// Get the sound pointer
FMOD::Sound* GameSound::GetSound()
{
    return sound;
}

// Get the file path for the sound file
const char* GameSound::GetSoundFilePath()
{
    return soundFilePath;
}

// Get the pitch of the sound
float GameSound::GetPitch()
{
    return pitch;
}

// Get the volume of the sound
float GameSound::GetVolume()
{
    return volume;
}

// Get the pan of the sound
float GameSound::GetPan()
{
    return pan;
}

// Get the loop of the sound
bool GameSound::GetLoop()
{
    return loop;
}
