#include "SpaceshipLevelAudioManager.h"

SpaceshipLevelAudioManager::SpaceshipLevelAudioManager()
{
}

SpaceshipLevelAudioManager::~SpaceshipLevelAudioManager()
{
}

void SpaceshipLevelAudioManager::InitializeAudio()
{
    AudioManager::InitializeAudio();
}

void SpaceshipLevelAudioManager::LoadSounds()
{
    ResultCheck(GetAudioSystem()->createStream("Assets/Audio/space-theme.wav", FMOD_DEFAULT, 0, &backgroundMusic), "Error creating background music stream");
    ResultCheck(backgroundMusic->setMode(FMOD_LOOP_NORMAL), "Error setting background music mode");
}

void SpaceshipLevelAudioManager::PlayBackgroundMusic()
{
    ResultCheck(GetAudioSystem()->playSound(backgroundMusic, 0, false, GetChannelAddress()), "Error playing background music");

    ResultCheck(GetChannel()->setVolume(0.5), "Error setting volume");
    ResultCheck(GetChannel()->setPitch(0.5), "Error setting pitch");
}

void SpaceshipLevelAudioManager::UpdateSound(int point)
{
    ResultCheck(GetChannel()->setPitch(0.5 + (point * 0.25)), "Error setting pitch");
    AudioManager::UpdateSound();
}