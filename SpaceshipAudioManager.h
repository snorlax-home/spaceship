#pragma once
#include "fmod.hpp"
#include "AudioManager.h"
class SpaceshipAudioManager : public AudioManager
{
private:
	FMOD::Sound *pointSound, *bounceSound;

public:
	// Constructor and Destructor
	SpaceshipAudioManager();
	~SpaceshipAudioManager();
	// Init and Load
	void InitializeAudio();
	void LoadSounds();
	// Play Sounds 
	void playPointSound();
	void playBounceSound();
	// Other Methods
	void UpdateSound();
};
