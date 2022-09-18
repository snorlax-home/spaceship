#include "SpaceshipLevelAudioManager.h"

// Constructor and Destructor
SpaceshipLevelAudioManager::SpaceshipLevelAudioManager()
{
}

SpaceshipLevelAudioManager::~SpaceshipLevelAudioManager()
{
}

// Method to initialize the audio system
void SpaceshipLevelAudioManager::InitializeAudio()
{
    // Initialize the audio system
    AudioManager::InitializeAudio();
}

// Method to load sounds
void SpaceshipLevelAudioManager::LoadSounds()
{
    // Create background music
    ResultCheck(GetAudioSystem()->createStream("Assets/Audio/space-theme.wav", FMOD_DEFAULT, 0, &backgroundMusic), "Error creating background music stream");
    // Set the background music to loop
    ResultCheck(backgroundMusic->setMode(FMOD_LOOP_NORMAL), "Error setting background music mode");
}

// Method to play background music
void SpaceshipLevelAudioManager::PlayBackgroundMusic()
{
    // Play the background music
    ResultCheck(GetAudioSystem()->playSound(backgroundMusic, 0, false, GetChannelAddress()), "Error playing background music");

    // Set the volume of the background music
    ResultCheck(GetChannel()->setVolume(0.5), "Error setting volume");
    // Set the pitch of the background music
    ResultCheck(GetChannel()->setPitch(0.5), "Error setting pitch");
}

// Method to update the audio system and pitch of the background music
void SpaceshipLevelAudioManager::UpdateSound(int point)
{
    // Increase the pitch of the background music based on the point
    ResultCheck(GetChannel()->setPitch(0.5 + (point * 0.25)), "Error setting pitch");
    // Update the audio system
    AudioManager::UpdateSound();
}