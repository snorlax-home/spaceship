#include "SpaceshipAudioManager.h"

// Constructor and Destructor
SpaceshipAudioManager::SpaceshipAudioManager()
{
}

SpaceshipAudioManager::~SpaceshipAudioManager()
{
}

// Method to initialize the audio system
void SpaceshipAudioManager::InitializeAudio()
{
	// Initialize the audio system
	AudioManager::InitializeAudio();
}

// Method to load sounds
void SpaceshipAudioManager::LoadSounds()
{
	// Create point sound
	ResultCheck(GetAudioSystem()->createSound("Assets/Audio/point-get.ogg", FMOD_DEFAULT, 0, &pointSound), "Error creating point sound");
	// Set the point sound to do not loop
	ResultCheck(pointSound->setMode(FMOD_LOOP_OFF), "Error setting point sound mode");

	// Create bounce sound
	ResultCheck(GetAudioSystem()->createSound("Assets/Audio/bounce.mp3", FMOD_DEFAULT, 0, &bounceSound), "Error creating bounce sound");
	// Set the bounce sound to do not loop
	ResultCheck(bounceSound->setMode(FMOD_LOOP_OFF), "Error setting bounce sound mode");
}

// Method to play point sound
void SpaceshipAudioManager::playPointSound()
{
	// Play the point sound
	ResultCheck(GetAudioSystem()->playSound(pointSound, 0, false, GetChannelAddress()), "Error playing point sound");
}

// Method to play bounce sound
void SpaceshipAudioManager::playBounceSound()
{
	// Play the bounce sound
	ResultCheck(GetAudioSystem()->playSound(bounceSound, 0, false, GetChannelAddress()), "Error playing bounce sound");
}

// Method to update the audio system
void SpaceshipAudioManager::UpdateSound()
{
	// Update the audio system
	AudioManager::UpdateSound();
}