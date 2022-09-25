#include "GameSound.h"

#include <iostream>

GameSound::GameSound()
{
    // Initialize variables to NULL
    sound = nullptr;
    soundFilePath = nullptr;
    volume = 0.0f;
    pitch = 0.0f;
    pan = 0.0f;
    loop = false;
    playSoundFlag = false;
}

GameSound::~GameSound()
{
    delete this;
}

void GameSound::Init(const char* filePath, float soundVolume,float soundPitch, float soundPan, bool soundLoop)
{
    // Assign values to variables
    this->soundFilePath = filePath;
    this->volume = soundVolume;
    this->pitch = soundPitch;
    this->pan = soundPan;
    this->loop = soundLoop;
}

// Setters
// Set the pointer to the sound object
void GameSound::SetSound(FMOD::Sound* newSound)
{
	this->sound = newSound;
}


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

// Set the play sound flag to determine if the sound should be played
void GameSound::SetPlaySoundFlag(bool playSound)
{
    this->playSoundFlag = playSound;
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

// Get the play sound flag to determine if the sound should be played
bool GameSound::GetPlaySoundFlag()
{
    return playSoundFlag;
}

// Clean up GameSound object
void GameSound::CleanUp()
{
    // Release the sound object
    sound->release();

    // Set pointers to NULL
    sound = nullptr;
    soundFilePath = nullptr;
}
