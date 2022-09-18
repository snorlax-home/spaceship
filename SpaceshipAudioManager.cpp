#include "SpaceshipAudioManager.h"

SpaceshipAudioManager::SpaceshipAudioManager()
{
}

SpaceshipAudioManager::~SpaceshipAudioManager()
{
}

void SpaceshipAudioManager::InitializeAudio()
{
	AudioManager::InitializeAudio();
}

void SpaceshipAudioManager::LoadSounds()
{
	ResultCheck(GetAudioSystem()->createSound("Assets/Audio/point-get.ogg", FMOD_DEFAULT, 0, &pointSound), "Error creating point sound");
	ResultCheck(pointSound->setMode(FMOD_LOOP_OFF), "Error setting point sound mode");

	ResultCheck(GetAudioSystem()->createSound("Assets/Audio/bounce.mp3", FMOD_DEFAULT, 0, &bounceSound), "Error creating bounce sound");
	ResultCheck(bounceSound->setMode(FMOD_LOOP_OFF), "Error setting bounce sound mode");
}

void SpaceshipAudioManager::playPointSound()
{
	ResultCheck(GetAudioSystem()->playSound(pointSound, 0, false, GetChannelAddress()), "Error playing point sound");
}

void SpaceshipAudioManager::playBounceSound()
{
	ResultCheck(GetAudioSystem()->playSound(bounceSound, 0, false, GetChannelAddress()), "Error playing bounce sound");
}

void SpaceshipAudioManager::UpdateSound()
{
	AudioManager::UpdateSound();
}